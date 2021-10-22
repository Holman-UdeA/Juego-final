#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPathItem>
#include <QPixmap>
#include <QKeyEvent>
#include <cmath>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player();
    void SetImagenPlayer();
    void keyPressEvent(QKeyEvent *KeyPress);
    void Set_Vel(float VelX, float VelY, float PosX, float PosY);
    void Actualizar();
    float Get_Height();
signals:
    void CentrarInView();
private:
    QPixmap Jugador, MovJugador;
    int ScaleX = 50, ScaleY = 50;
    float PX, PY, Masa, R, VX, VY, Angulo;
    float AX, AY, G, K, E, V, DT;
};

#endif // PLAYER_H
