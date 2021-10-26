#include "enemigos.h"

Enemigos::Enemigos(int AnchoEsc, int AltoEsc, int PosPlayerX)
{
    Enemigo.load(":/Imagenes/Enemies Walk.jpg");
    SetImagenEnemigo();
    setPos((PosPlayerX+AnchoEsc/2)+ScaleX/2, AltoEsc-ScaleY);
}

void Enemigos::SetImagenEnemigo()
{
    MovEnemigo = Enemigo.copy(0, 0, 120, 120);
    setPixmap(MovEnemigo.scaled(ScaleX, ScaleY));
}
