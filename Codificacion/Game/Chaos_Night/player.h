#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPathItem>
#include <QPixmap>
#include <QKeyEvent>

class Player: public QObject, public QGraphicsPixmapItem
{
public:
    Player();
    void SetImagenPlayer();
    void keyPressEvent(QKeyEvent *KeyPress);
private:
    QPixmap Jugador, MovJugador;
    int ScaleX = 50, ScaleY = 50;
};

#endif // PLAYER_H
