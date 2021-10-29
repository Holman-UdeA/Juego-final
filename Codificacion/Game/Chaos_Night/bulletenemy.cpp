#include "bulletenemy.h"

BulletEnemy::BulletEnemy(int PoXP, int PoYP, float Angle, float Vi)
{
    Bullets.load(":/Imagenes/Enemies Bullet.png");
    SetSpriteEnemy();
    TimerMov = new QTimer;
    DT = 0;
    Angle = Angle*Pi/180;
    VIX = Vi*cos(Angle);
    VIY = Vi*sin(Angle);
    PoX = PoXP;
    PoY = PoYP;
    setPos(PoX, PoY);
    connect(TimerMov, SIGNAL(timeout()), this, SLOT(Actualizar()));
    TimerMov->start(30);
}

void BulletEnemy::SetSpriteEnemy()
{
    SpriteBullet = Bullets.copy(0, 0, 58, 51);
    setPixmap(SpriteBullet.scaled(ScaleX, ScaleY));
}

void BulletEnemy::Actualizar()
{
    PX = PoX - VIX*DT;
    PY = PoY - VIY*DT + (Gravedad/2)*DT*DT;
    DT += 0.1;
    Rotacion -= 2;
    setRotation(Rotacion);
    setPos(PX, PY);
    if(PY > (500+ScaleY)){
        scene()->removeItem(this);
        delete this;
    }
}
