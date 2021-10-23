#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include "player.h"

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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    fstream *Archivo;
    QGraphicsScene *Escena;
    QPixmap Background;
    QTimer *TimerFP;
    Player *Jugador;
    int AnchoEsc, AltoEsc;
    unsigned long PosUser;
    string Usuario, Password, Users;
    void SetUp_MainWindow();
    void GetUsers();
    void Hide_Login();
    bool CheckAccount(int Opcion);
private slots:
    void on_PButton_Ingresar_clicked();
    void on_PButton_Registrar_clicked();
    void on_PButton_SingleMode_clicked();
    void on_PButton_Multiplayer_clicked();
    void on_RButton_ShowPassword_clicked(bool checked);
public slots:
    void CentrarPlayer();
};
#endif // MAINWINDOW_H
