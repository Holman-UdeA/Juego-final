#include "bullet.h"

Bullet::Bullet(int PosPlayer, int AnchoGrpVw, int AnchoEscena)
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
    WidthEscena = AnchoEscena;
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
    setPos(x()+1, y());
    if((pos().x()+ScaleX > PosXI+(LimitWidth/2)) || (pos().x()+ScaleX > WidthEscena)){
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
