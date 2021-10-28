#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include "bullet.h"
#include "bulletenemy.h"

class Enemigos: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigos(int AnchoEsc, int AltoEsc, int PosPlayerX, int Lives);
    void SetImagenEnemigo();
    int GetLivesEnemy();
private:
    QPixmap Enemigo, MovEnemigo;
    QTimer *TimerMov, *TimerLaunch;
    //BulletEnemy *Proyectil;
    int ScaleX = 50, ScaleY = 50;
    int Vidas;
public slots:
    void MoveEnemy();
    void LaunchBullet();
signals:
    void IncreaseScore();
};

#endif // ENEMIGOS_H
