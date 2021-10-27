#include "enemigos.h"

Enemigos::Enemigos(int AnchoEsc, int AltoEsc, int PosPlayerX)
{
    Enemigo.load(":/Imagenes/Enemies Walk.jpg");
    SetImagenEnemigo();
    TimerMov = new QTimer;
    setPos((PosPlayerX+AnchoEsc/2)+ScaleX/2, AltoEsc-ScaleY);
    connect(TimerMov, SIGNAL(timeout()), this, SLOT(MoveEnemy()));
    TimerMov->start(10);
}

void Enemigos::SetImagenEnemigo()
{
    MovEnemigo = Enemigo.copy(0, 0, 120, 120);
    setPixmap(MovEnemigo.scaled(ScaleX, ScaleY));
}

void Enemigos::MoveEnemy()
{
    setPos(x()-1, y());
    if(pos().x()+ScaleX < 0){
        scene()->removeItem(this);
        delete this;
    }
}
