#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

#define Pi (float)3.14
#define Gravedad 9.8

class BulletEnemy:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BulletEnemy(int PoXP, int PoYP, float Angle, float Vi);
private:
    QTimer *TimerMov;
    float PX, PY, PoX, PoY, VIX, VIY, DT;
    QPixmap Bullets, SpriteBullet;
    void SetSpriteEnemy();
    //float Angle;
private slots:
    void Actualizar();
};

#endif // BULLETENEMY_H
