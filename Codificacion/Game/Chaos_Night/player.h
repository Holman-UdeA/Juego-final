#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPathItem>
#include <QPixmap>
#include <QKeyEvent>
#include <cmath>
#include <QGraphicsScene>
#include "enemigos.h"
#include "bullet.h"

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(int H_Limit, int V_Limit, int WidthGV);
    void SetImagenPlayer();
    void keyPressEvent(QKeyEvent *KeyPress);
    void Set_Vel(float VelX, float VelY, float PosX, float PosY);
    void BorderCollision();
    float Get_Height();
signals:
    void CentrarInView();
private:
    QPixmap Jugador, MovJugador;
    int ScaleX = 50, ScaleY = 50, AltoEscena, AnchoEscena, AnchoGrpsView;
    int Vidas;
    float PX, PY, Masa, R, VX, VY, Angulo;
    float AX, AY, G, K, E, V, DT;
public slots:
    void Actualizar();
    void AgregarEnemigo();
};

#endif // PLAYER_H
