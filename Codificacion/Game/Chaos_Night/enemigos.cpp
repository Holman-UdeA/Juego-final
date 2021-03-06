#include "enemigos.h"

Enemigos::Enemigos(int AnchoEsc, int AltoEsc, int PosPlayerX, int Lives)
{
    Enemigo.load(":/Imagenes/Enemies Walking.png");
    SetImagenEnemigo();
    TimerMov = new QTimer;
    TimerLaunch = new QTimer;
    TimerSprite = new QTimer;
    setPos((PosPlayerX+AnchoEsc/2)+ScaleX/2, AltoEsc-ScaleY);
    connect(TimerMov, SIGNAL(timeout()), this, SLOT(MoveEnemy()));
    connect(TimerLaunch,SIGNAL(timeout()), this, SLOT(LaunchBullet()));
    connect(TimerSprite, SIGNAL(timeout()), this, SLOT(CambiarSprite()));
    TimerMov->start(10);
    TimerLaunch->start(2000);
    TimerSprite->start(70);
    Vidas = Lives;
}

void Enemigos::SetImagenEnemigo()
{
    MovEnemigo = Enemigo.copy((130*NumSprite), 0, 130, 120);
    setPixmap(MovEnemigo.scaled(ScaleX, ScaleY));
}

int Enemigos::GetLivesEnemy()
{
    return Vidas;
}

void Enemigos::MoveEnemy()
{
    QList<QGraphicsItem*> Collision_Items = collidingItems();
    for(int i=0, j=Collision_Items.size(); i<j; i++){
        if(typeid (*(Collision_Items[i])) == typeid (Bullet)){
            scene()->removeItem(Collision_Items[i]);
            delete Collision_Items[i];
            Vidas--;
            if(Vidas <= 0){
                emit IncreaseScore();
                scene()->removeItem(this);
                delete this;
            }
        }
    }
    setPos(x()-1, y());
    if(pos().x()+ScaleX < 0){
        scene()->removeItem(this);
        delete this;
    }
}

void Enemigos::LaunchBullet()
{
    BulletEnemy *Proyectil1 = new BulletEnemy(x(), y(), 65, 110);
    scene()->addItem(Proyectil1);
    BulletEnemy *Proyectil2 = new BulletEnemy(x(), y(), 40, 55);
    scene()->addItem(Proyectil2);
}

void Enemigos::CambiarSprite()
{
    NumSprite++;
    if(NumSprite > 10){
        NumSprite = 0;
    }
    SetImagenEnemigo();
}
