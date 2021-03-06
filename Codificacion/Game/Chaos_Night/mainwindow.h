#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QFont>
#include "player.h"
#include "enemigos.h"

#define TxtPath "../Chaos_Night/Users.txt"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void IncreaseScore();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    fstream *Archivo;
    QGraphicsScene *Escena;
    QPixmap Background, BackgrounMain;
    QTimer *TimerFP, *TimerSpawnE, *TimerIncreaseDif;
    Player *Jugador;
    //Enemigos *Enemigo;
    int AnchoEsc, AltoEsc;
    int VidasPlayer, VidasEnemigos, TiempoAparicionE, Puntaje;
    unsigned long PosUser;
    string Usuario, Password, Users;
    void SetUp_MainWindow();
    void GetUsers();
    void UpdateUsers(string Data, int Opcion);
    void GetData();
    void Hide_Login();
    void StopAll();
    bool CheckAccount(int Opcion);
private slots:
    void on_PButton_Ingresar_clicked();
    void on_PButton_Registrar_clicked();
    void on_PButton_SingleMode_clicked();
    void on_PButton_Multiplayer_clicked();
    void on_RButton_ShowPassword_clicked(bool checked);
    void IncreasDifficulty();
    void UpScore();
    void GameOver();
public slots:
    void CentrarPlayer();
};
#endif // MAINWINDOW_H
