#include "player.h"

Player::Player()
{
    Jugador.load(":/Imagenes/game background.png");
    VX = 0;
    VY = 0;
    Masa = 50;
    AX = 0;
    AY = 0;
    G = 9.8;
    R = 20;
    K = 0.08;
    E = 0.2;
    V = 0;
    DT = 0.1;
}

void Player::SetImagenPlayer()
{
    MovJugador = Jugador.copy(0,0, Jugador.width(), Jugador.height());
    setPixmap(MovJugador.scaled(ScaleX, ScaleY));
}

void Player::keyPressEvent(QKeyEvent *KeyPress)
{
    if(KeyPress->key() == Qt::Key_W){
        setPos(x(), y()-5);
//        Set_Vel(VX, 50, x(), y());
    }
    else if(KeyPress->key() == Qt::Key_A){
        setPos(x()-5, y());
//        Set_Vel(-30, VY, x(), y());
    }
    else if(KeyPress->key() == Qt::Key_S){
        setPos(x(), y()+5);
//        setPos(x(), y()+5);
    }
    else if(KeyPress->key() == Qt::Key_D){
        setPos(x()+5, y());
//        Set_Vel(30, VY, x(), y());
    }
    emit CentrarInView();
}

void Player::Set_Vel(float VelX, float VelY, float PosX, float PosY)
{
    VX = VelX;
    VY = VelY;
    PX = x();
    PY = y();
}

void Player::Actualizar()
{
    V = pow((VX*VY)+(VY*VX),0.5);
    Angulo = atan2(VY, VX);
    AX = -((K*(V*V)*(R*R))/Masa) * cos(Angulo);
    AY = (-((K*(V*V)*(R*R))/Masa)*sin(Angulo)-G);
    PX = PX + (VX*DT) + ((AX*(DT*DT))/2);
    PY = PY + (VY*DT) + ((AY*(DT*DT)/2));
    VX = VX + AX*DT;
    VY = VY + AY*DT;
}

float Player::Get_Height()
{
    return ScaleY;
}
