#include "player.h"

Player::Player(int H_Limit, int V_Limit, int WidthGV)
{
    Jugador.load(":/Imagenes/Robot Walk.png");
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
    AnchoGrpsView = WidthGV;
}

void Player::SetImagenPlayer()
{
    MovJugador = Jugador.copy((97*NumSprite),0, 97, 101);
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
        NumSprite++;
        if(NumSprite > 8){
            NumSprite = 0;
        }
        SetImagenPlayer();
        Set_Vel(-30, VY, PX, PY);
    }
    else if(KeyPress->key() == Qt::Key_D){
        NumSprite++;
        if(NumSprite > 8){
            NumSprite = 0;
        }
        SetImagenPlayer();
        Set_Vel(30, VY, PX, PY);
    }
    else if(KeyPress->key() == Qt::Key_Space){
        Bullet *Proyectil = new Bullet(x()+ScaleX, AnchoGrpsView, AnchoEscena-ScaleX);
        Proyectil->setPos(x()+ScaleX, y()+(ScaleY/3));
        scene()->addItem(Proyectil);
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

void Player::SetLivesPlayer(int Lives)
{
    Vidas = Lives;
}

void Player::SetLivesEnemies(int LivesEnemy)
{
    VidasEnemigos = LivesEnemy;
}

int Player::GetLivesPlayer()
{
    return Vidas;
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

    QList<QGraphicsItem*> Collision_Items = collidingItems();
    for(int i=0, n=Collision_Items.size(); i<n; i++){
        if(typeid (*(Collision_Items[i])) == typeid (BulletEnemy)){
            scene()->removeItem(Collision_Items[i]);
            delete Collision_Items[i];
            if(Vidas > 0){
                Vidas -= 1;
                emit RestarVida();
            }
        }
    }
}

void Player::AgregarEnemigo()
{
    if(x() >= (AnchoGrpsView/2)){
        Enemigos *Enemy = new Enemigos(AnchoGrpsView, AltoEscena, x(), VidasEnemigos);
        scene()->addItem(Enemy);
        connect(Enemy, SIGNAL(IncreaseScore()), this, SIGNAL(AumentarPuntaje()));
    }
    else {
        Enemigos *Enemy = new Enemigos(AnchoGrpsView*2, AltoEscena, x(), VidasEnemigos);
        scene()->addItem(Enemy);
        connect(Enemy, SIGNAL(IncreaseScore()), this, SIGNAL(AumentarPuntaje()));
    }
}

float Player::Get_Height()
{
    return ScaleY;
}
