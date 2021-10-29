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
    QTimer *TimerMov, *TimerLaunch, *TimerSprite;
    int ScaleX = 70, ScaleY = 70;
    int Vidas, NumSprite = 0;
public slots:
    void MoveEnemy();
    void LaunchBullet();
    void CambiarSprite();
signals:
    void IncreaseScore();
};

#endif // ENEMIGOS_H
