#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPathItem>
#include <QPixmap>
#include <QKeyEvent>
#include <cmath>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include "bullet.h"
#include "bulletenemy.h"

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(int H_Limit, int V_Limit, int WidthGV);
    void SetImagenPlayer();
    void keyPressEvent(QKeyEvent *KeyPress);
    void Set_Vel(float VelX, float VelY, float PosX, float PosY);
    void BorderCollision();
    void SetLivesPlayer(int Lives);
    void SetLivesEnemies(int LivesEnemy);
    void DisminuiL();
    int GetLivesPlayer();
    float Get_Height();
signals:
    void CentrarInView();
    void RestarVida();
    void AumentarPuntaje();
private:
    QPixmap Jugador, MovJugador;
    int ScaleX = 70, ScaleY = 70, AltoEscena, AnchoEscena, AnchoGrpsView;
    int Vidas, VidasEnemigos, NumSprite = 0;
    float PX, PY, Masa, R, VX, VY, Angulo;
    float AX, AY, G, K, E, V, DT;
public slots:
    void Actualizar();
    void AgregarEnemigo();
};

#endif // PLAYER_H
