#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

class Enemigos: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigos(int AnchoEsc, int AltoEsc, int PosPlayerX);
    void SetImagenEnemigo();
private:
    QPixmap Enemigo, MovEnemigo;
    QTimer *TimerMov;
    int ScaleX = 50, ScaleY = 50;
    int Vidas;
public slots:
    void MoveEnemy();
};

#endif // ENEMIGOS_H
