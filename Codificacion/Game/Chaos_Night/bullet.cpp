#include "bullet.h"

Bullet::Bullet(int PosPlayer, int AnchoGrpVw)
{
    Bullets.load(":/Imagenes/Bullets Game.png");
    SetImagenBullet(0);
    TimerMov = new QTimer;
    TimerSprite = new QTimer;
    connect(TimerMov, SIGNAL(timeout()), this, SLOT(Move()));
    connect(TimerSprite, SIGNAL(timeout()), this, SLOT(ChangeSprite()));
    TimerMov->start(5);
    TimerSprite->start(70);
    PosXI = PosPlayer;
    LimitWidth = AnchoGrpVw;
}

void Bullet::SetImagenBullet(int Sprite)
{
    if(Sprite == 0){
        SpriteBullet = Bullets.copy(0, 0, 282, 186);
    }
    else if(Sprite == 1){
        SpriteBullet = Bullets.copy(Sprite*282, 0, 282, 186);
    }
    else if(Sprite == 2){
        SpriteBullet = Bullets.copy(Sprite*282, 0, 282, 186);
    }
    else if(Sprite == 3){
        SpriteBullet = Bullets.copy(Sprite*282, 0, 282, 186);
    }
    setPixmap(SpriteBullet.scaled(ScaleX, ScaleY));
}

void Bullet::Move()
{
//    QList <QGraphicsItem*> Collision_Items = collidingItems();
//    for(int i=0, n=Collision_Items.size(); i<n; i++){
//        if(typeid (*(Collision_Items[i])) == typeid (Enemigos)){
//            scene()->removeItem(Collision_Items[i]);
//            scene()->removeItem(this);
//            delete Collision_Items[i];
//            delete this;
//        }
//    }

    setPos(x()+1, y());
    if(pos().x()+ScaleX > PosXI+(LimitWidth/2)){
        scene()->removeItem(this);
        delete this;
    }
}

void Bullet::ChangeSprite()
{
    if(NumSprite > 3){
        NumSprite = 0;
    }
    SetImagenBullet(NumSprite);
    NumSprite++;
}
