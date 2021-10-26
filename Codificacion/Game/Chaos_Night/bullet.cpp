#include "bullet.h"

Bullet::Bullet()
{
    Bullets.load(":/Imagenes/Bullets Game.png");
    SetImagenBullet();
}

void Bullet::SetImagenBullet()
{
    SpriteBullet = Bullets.copy(0, 0, 282, 186);
    setPixmap(SpriteBullet.scaled(ScaleX, ScaleY));
}
