#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include "enemigos.h"

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(int PosPlayer, int AnchoGrpVw);
    void SetImagenBullet(int Sprite);
private:
    QTimer *TimerMov, *TimerSprite;
    QPixmap Bullets, SpriteBullet;
    int ScaleX = 45, ScaleY = 27, PosXI, LimitWidth, NumSprite = 0;
public slots:
    void Move();
    void ChangeSprite();
};

#endif // BULLET_H
