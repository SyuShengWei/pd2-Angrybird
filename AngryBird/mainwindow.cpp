#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);

    //original bird pos
    originalPos_X = 5.0f;
    originalPos_Y = 8.0f;

    //mouse hold
    hold  = 0 ;
    //what stattion the bird is;
    birdStep = 0 ;
    //which bird to hold
    whichBird = 0;
    //create bird Timer
    createTimer = new QTimer();
    connect(createTimer,SIGNAL(timeout()),this,SLOT(createBird()));
    //restart?
    explosion = new QGraphicsPixmapItem();
    explosion->setPixmap(QPixmap(":/image/explosion.png"));
    explosion->hide();
    pixmapTimer = new QTimer();
    //set sling slop picture
    slingslot= new QGraphicsPixmapItem();
    slingslot->setPixmap(QPixmap(":/image/slingslot.png"));
    slingslot->setPos(125,355);
    //create score
    score = new Score;
    //create endGame pic0
    endGamePix= new QGraphicsPixmapItem();
    endGamePix->setPos(100,50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{   
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedHeight(600);
    ui->graphicsView->setFixedWidth(800);


    //restartbuttom
    QPushButton *restart =  new QPushButton();
    restart->setGeometry(QRect(QPoint(680,0),QSize(55,55)));
    QPixmap pixmap(":/image/restart.png");
    QIcon ButtonIcon(pixmap);
    restart->setIcon(ButtonIcon);
    restart->setIconSize(pixmap.rect().size());
    scene->addWidget(restart);  
    connect(restart,SIGNAL(clicked(bool)),this,SLOT(restart()));
    //exit buttom
    QPushButton *exit =  new QPushButton();
    exit->setGeometry(QRect(QPoint(740,0),QSize(55,55)));
    QPixmap exitPixmap(":/image/exit.png");
    QIcon exitIcon(exitPixmap);
    exit->setIcon(exitIcon);
    exit->setIconSize(exitPixmap.rect().size());
    scene->addWidget(exit);
    connect(exit,SIGNAL(clicked(bool)),this,SLOT(exitGame()));
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),QSize(800,600));
    //set Explosion ability Picture
    scene->addItem(explosion);
    connect(pixmapTimer,SIGNAL(timeout()),this,SLOT(hidePixmap()));
    //set slingslot pocture
    scene->addItem(slingslot);
    slingslot->show();
    //set endFame Pic
    scene->addItem(endGamePix);

    initialGame();
    checkLeft();

    //set score
    score = new Score();
    score->setBirdLeft(4-whichBird);
    score->setPlainText("Score = " + QString::number(score->getScore()) + "\n" + "Bird Left = " + QString::number(score->getBirdLeft()));
    score->setDefaultTextColor(Qt::red);
    score->setFont(QFont("timer",16));
    scene->addItem(score);
    score->setPos(550,15);

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    mouseEvent = (QMouseEvent *) event ;

    if(event->type() == QEvent::MouseButtonPress && birdLeft != 0 && whichBird != 4)
    {   //birdStep == 0 ,hold the bird
        if(birdStep == 0){
        hold = 1 ;
        mousePress_X =  (mouseEvent->pos().x()-23) /800.0*32.0;
        mousePress_Y = 18.0-((mouseEvent->pos().y()-46) *18 / 600.0);
        birdStep = 1;
        std::cout << birdStep <<std::endl;
        }
        //birdStep == 3 ,not yet use the ability
        else if(birdStep == 3 && birdAbility == 1){
            //dtermine what kind of ability
            birdAbility = birdList[whichBird]->birdAbility();
            //blue ability
            if(birdAbility == 2){
                Bird * avatarBird = new Bird(birdList[whichBird]->getBody().GetPosition().x ,birdList[whichBird]->getBody().GetPosition().y + 2,
                                                    0.27f,&timer,QPixmap(":/image/angrybird_blue.png").scaled(height()/12.0,height()/12.0),world,scene);
                avatarBird->setLinearVelocity(b2Vec2(birdList[whichBird]->getBody().GetLinearVelocity().x ,birdList[whichBird]->getBody().GetLinearVelocity().y + 3));
                avatarBird->getBody().SetGravityScale(1);
                avatarBird->birdAbility();
                itemList.push_back(avatarBird);
            }
            //block ability
            else if (birdAbility == 3){

                float  bird_pos_X = birdList[whichBird]->getBody().GetWorldCenter().x;
                float  bird_pos_Y = birdList[whichBird]->getBody().GetWorldCenter().y;

                foreach(GameItem *item , itemList){
                    if(item->getBody().GetUserData() != birdList[whichBird]->getBody().GetUserData()){
                        float item_pos_X = item->getBody().GetWorldCenter().x;
                        float item_pos_Y = item->getBody().GetWorldCenter().y;
                        float distance =pow((bird_pos_X - item_pos_X),2) + pow((bird_pos_Y - item_pos_Y),2);
                        std::cout<<"explore"<<distance<<std::endl;
                        if(distance <= 100.0){
                            item->getBody().SetLinearVelocity(b2Vec2(10/(item_pos_X - bird_pos_X),10/(item_pos_Y - bird_pos_Y)));
                            item->kill((100-distance)*5);
                        }
                    }
                }
                explosion->setPos((bird_pos_X)*800/32,(1.0f - (bird_pos_Y)/18) * 600);
                explosion->show();
                pixmapTimer->start(500);
                birdList[whichBird]->setHP(0);
            }
            birdStep = 4 ;
        }
    }
    //if hold the bird ,set the bird pos as where the mouse is
    if(event->type() == QEvent::MouseMove && hold >= 1 && birdLeft != 0 && whichBird != 4)
    {
       if(birdStep == 1 || birdStep == 2){
            float pos_X = (mouseEvent->pos().x()-23) /800.0*32.0;
            float pos_Y = 18.0-((mouseEvent->pos().y()-46) *18 / 600.0);

            if( (originalPos_X - pos_X)* (originalPos_X - pos_X) + (originalPos_Y - pos_Y)* (originalPos_Y - pos_Y) <= 25)
                birdList[whichBird]->getBody().SetTransform(b2Vec2(pos_X,pos_Y),0);

            birdStep = 2;
       }

    }

    if(event->type() == QEvent::MouseButtonRelease  && birdLeft != 0 && whichBird != 4)
    {
        if(birdStep == 2){
            hold = 0;

            mouseRelease_X =  (mouseEvent->pos().x()-23) /800.0*32.0;
            mouseRelease_Y = 18.0-((mouseEvent->pos().y()-46) *18 / 600.0);
            float positionNow_X = birdList[whichBird]->getBody().GetPosition().x;
            float positionNow_Y = birdList[whichBird]->getBody().GetPosition().y;

            birdList[whichBird]->getBody().SetLinearVelocity(b2Vec2((positionNow_X- originalPos_X)*-5,(positionNow_Y- originalPos_Y)*-5 ));
            birdList[whichBird]->getBody().SetGravityScale(1);

            if(birdList[whichBird]->getBirdType() == 0){
               birdList[whichBird]->birdAbility();
               createTimer->start(500);
               birdStep = 0 ;
               std::cout << birdStep <<std::endl;
            }
            else{
                birdAbility = 1;
                birdStep = 3;
                std::cout << birdStep <<std::endl;
            }
        }
        else if(birdStep == 4 ){
            createTimer->start(10);
            birdStep = 0 ;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
    //qApp->exit(1);
}

void MainWindow::initialGame()
{
    // Create ground, item 0
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    //create Edge item 1-4
    itemList.push_back( new Edge(16,3,b2Vec2(-16,0),b2Vec2(16,0),world));
    itemList.push_back( new Edge(16,22,b2Vec2(-16,0),b2Vec2(16,0),world));
    itemList.push_back( new Edge(-1,9,b2Vec2(0,-9),b2Vec2(0,9),world));
    itemList.push_back( new Edge(33,9,b2Vec2(0,-9),b2Vec2(0,9),world));
    //create woods item 5-13
    itemList.push_back(new Wood(24.7f,5.0f,0.03*10,0.03*70,&timer,QPixmap(":/image/wood_v.png"),world,scene));
    itemList.push_back(new Wood(26.8f,5.0f,0.03*10,0.03*70,&timer,QPixmap(":/image/wood_v.png"),world,scene));
    itemList.push_back(new Wood(25.7f,7.5f,0.03*70,0.03*10,&timer,QPixmap(":/image/wood_h.png"),world,scene));
    itemList.push_back(new Wood(22.2f,5.0f,0.03*10,0.03*70,&timer,QPixmap(":/image/wood_v.png"),world,scene));
    itemList.push_back(new Wood(24.2f,5.0f,0.03*10,0.03*70,&timer,QPixmap(":/image/wood_v.png"),world,scene));
    itemList.push_back(new Wood(23.1f,7.5f,0.03*70,0.03*10,&timer,QPixmap(":/image/wood_h.png"),world,scene));
    itemList.push_back(new Wood(23.2f,9.0f,0.03*10,0.03*70,&timer,QPixmap(":/image/wood_v.png"),world,scene));
    itemList.push_back(new Wood(25.1f,9.0f,0.03*10,0.03*70,&timer,QPixmap(":/image/wood_v.png"),world,scene));
    itemList.push_back(new Wood(24.1f,10.5f,0.03*70,0.03*10,&timer,QPixmap(":/image/wood_h.png"),world,scene));
    //create pig item 14
    Pig *pig = new Pig(25.0f,5.0f,0.27f,&timer,QPixmap(":/image/pig.png").scaled(height()/9.0,height()/9.0),world,scene);
    itemList.push_back(pig);
    //create first bird item 15
    Bird *bird1 = new Bird(5.0f,8.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdList.push_back(bird1);
    itemList.push_back(bird1);

    BlockBird *bird2 = new BlockBird(100.0f,5.0f,0.27f,&timer,QPixmap(":/image/angrybird-black.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdList.push_back(bird2);
    itemList.push_back(bird2);

    YellowBird *bird3 = new YellowBird(100.0f,5.0f,0.27f,&timer,QPixmap(":/image/angrybird-yellow.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdList.push_back(bird3);
    itemList.push_back(bird3);

    BlueBird *bird4 = new BlueBird(100.0f,4.0f,0.27f,&timer,QPixmap(":/image/angrybird_blue.png").scaled(height()/12.0,height()/12.0),world,scene);
    birdList.push_back(bird4);
    itemList.push_back(bird4);

    scene->update();
}

void MainWindow::destoryTtem()
{
    foreach(GameItem *i ,itemList){
        if (i->getHP() <=0){
            switch(i->getItemType()){
                case  1 :
                    score->increaseScore(1000);
                    pigLeft --;
                break;
                case  2:
                    score->increaseScore(500);
                    birdLeft -- ;
                break;
                case  3:
                    score->increaseScore(200);
                break;
            }
            itemList.removeOne(i);
            delete i ;
            if(pigLeft == 0)
                endGame(1);
            else if(pigLeft > 0 && birdLeft == 0)
                endGame(0);
            //score->increaseScore(100);
           // std::cout<<"score="<<i->getItemType()<<" ="<<score->getScore()<<std::endl;
        }
    }
}

void MainWindow::hit()
{
    for(int i = 5 ; i < itemList.size();i++){
        for (b2ContactEdge* edge = itemList[i]->getBody().GetContactList(); edge; edge = edge->next){
            itemList[i]->kill(edge->other->GetLinearVelocity().Length());
            itemList[i]->ifHit = 1;
        }
    }
}


void MainWindow::tick()
{
    destoryTtem();
    world->Step(1.0/60.0,6,2);
    hit();
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::createBird()
{
    whichBird = whichBird + 1 ;
    if(whichBird <= 3){
        birdList[whichBird]->getBody().SetTransform(b2Vec2(5.0f,8.0f),0);
    }
    else{
        whichBird = 4;
    }
    createTimer->stop();

    score->setBirdLeft(4-whichBird);
    score->setPlainText("Score = " + QString::number(score->getScore()) + "\n" + "Bird Left = " + QString::number(score->getBirdLeft()));
    score->setDefaultTextColor(Qt::red);
    score->setFont(QFont("timer",16));
}

void MainWindow::hidePixmap()
{
    explosion->hide();
}

void MainWindow::restart()
{
    createTimer->stop();
    timer.stop();
    foreach(Bird * bird ,birdList){
        birdList.removeOne(bird);
    }
    foreach(GameItem * item ,itemList){
        itemList.removeOne(item);
        delete item;
    }

    hold        = 0;
    birdStep    = 0;
    birdAbility = 0;
    whichBird   =0;

    score->setScore(0);
    score->setBirdLeft(4-whichBird);
    score->setPlainText("Score = " + QString::number(score->getScore()) + "\n" + "Bird Left = " + QString::number(score->getBirdLeft()));
    score->setDefaultTextColor(Qt::red);
    score->setFont(QFont("timer",16));


    initialGame();
    checkLeft();
    world->Step(1.0/60.0,6,2);
    scene->update();
    timer.start();

    endGamePix->hide();
}

void MainWindow::exitGame()
{
    QCloseEvent * event;
    closeEvent(event);
    //qApp->exit(1);
}

void MainWindow::checkLeft()
{
    birdLeft = 0;
    pigLeft  = 0;
    foreach(GameItem * item ,itemList){
        switch(item->getItemType()){
        case 1:
            pigLeft ++;
            break;
        case 2:
            birdLeft++;
            break;
        }
    }
}

void MainWindow::endGame(int signal)
{
    switch(signal){
        case 0://lose
            endGamePix->setPixmap(QPixmap(":/image/lose.jpg"));
            endGamePix->show();
            break;
        case 1://win
            endGamePix->setPixmap(QPixmap(":/image/win.jpg"));
            endGamePix->show();
            break;
    }
}
