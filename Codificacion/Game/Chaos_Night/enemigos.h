#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Enemigos: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigos(int AnchoEsc, int AltoEsc, int PosPlayerX);
    void SetImagenEnemigo();
private:
    QPixmap Enemigo, MovEnemigo;
    int ScaleX = 50, ScaleY = 50;
public slots:
};

#endif // ENEMIGOS_H
