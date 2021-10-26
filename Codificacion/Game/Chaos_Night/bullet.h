#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();
    void SetImagenBullet();
private:
    QPixmap Bullets, SpriteBullet;
    int ScaleX = 30, ScaleY = 20;
};

#endif // BULLET_H
