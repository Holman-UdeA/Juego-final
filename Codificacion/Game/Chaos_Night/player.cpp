#include "player.h"

Player::Player()
{
    Jugador.load(":/Imagenes/game background.png");
}

void Player::SetImagenPlayer()
{
    MovJugador = Jugador.copy(0,0, Jugador.width(), Jugador.height());
    setPixmap(MovJugador.scaled(ScaleX, ScaleY));
}

void Player::keyPressEvent(QKeyEvent *KeyPress)
{
    if(KeyPress->key() == Qt::Key_W){
        setPos(x(), y()+-5);
    }
    else if(KeyPress->key() == Qt::Key_A){
        setPos(x()-5, y());
    }
    else if(KeyPress->key() == Qt::Key_S){
        setPos(x(), y()+5);
    }
    else if(KeyPress->key() == Qt::Key_D){
        setPos(x()+5, y());
    }
}
