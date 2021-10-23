#include "player.h"

Player::Player(int H_Limit, int V_Limit)
{
    Jugador.load(":/Imagenes/game background.png");
    PX = x();
    PY = y();
    VX = 0;
    VY = 0;
    Masa = 50;
    AX = 0;
    AY = 0;
    G = 9.8;
    R = ScaleY;
    K = 0.08;
    E = 0.2; //CRestitucion
    V = 0;
    DT = 0.1;
    AltoEscena = V_Limit;
    AnchoEscena = H_Limit;
}

void Player::SetImagenPlayer()
{
    MovJugador = Jugador.copy(0,0, Jugador.width(), Jugador.height());
    setPixmap(MovJugador.scaled(ScaleX, ScaleY));
}

void Player::keyPressEvent(QKeyEvent *KeyPress)
{
    if(KeyPress->key() == Qt::Key_W){
        if(PY<=ScaleX){
            Set_Vel(VX, 50, PX, PY);
        }
    }
    else if(KeyPress->key() == Qt::Key_A){
        Set_Vel(-30, VY, PX, PY);
    }
    else if(KeyPress->key() == Qt::Key_D){
        Set_Vel(30, VY, PX, PY);
    }

}

void Player::Set_Vel(float VelX, float VelY, float PosX, float PosY)
{
    VX = VelX;
    VY = VelY;
    PX = PosX;
    PY = PosY;
}

void Player::BorderCollision()
{
    if(PX < 0){
        Set_Vel(-1*VX*E, VY, 0, PY);
    }
    if(PX > AnchoEscena-R){
        Set_Vel(-1*VX*E, VY, AnchoEscena-R, PY);
    }
    if(PY < R){
        Set_Vel(VX, -1*E*VY, PX, R);
    }
    if(PY > AltoEscena-R){
        Set_Vel(VX, -1*E*VY, PX, AltoEscena-R);
    }
}

void Player::Actualizar()
{
    V = pow((VX*VX)+(VY*VY),1/2) ;
    Angulo = atan2(VY,VX) ;
    AX = -((K*(V*V)*(R*R))/Masa)*cos(Angulo) ;
    AY = (-((K*(V*V)*(R*R))/Masa)*sin(Angulo)-G) ;
    PX = PX + (VX*DT) + ((AX*(DT*DT))/2) ;
    PY = PY + (VY*DT) + ((AY*(DT*DT)/2)) ;
    VX = VX + AX*DT ;
    VY = VY + AY*DT ;
    setPos(PX, AltoEscena-PY);
    BorderCollision();
    emit CentrarInView();
}

float Player::Get_Height()
{
    return ScaleY;
}
