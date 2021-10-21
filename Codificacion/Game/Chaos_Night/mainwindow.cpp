#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetUp_MainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetUp_MainWindow()
{
    Archivo = new fstream;
    Escena = new QGraphicsScene;
    AnchoEsc = 1000;
    AltoEsc = 500;
    ui->graphicsView->setGeometry(0, 0, AnchoEsc, AltoEsc);
    Escena->setSceneRect(0, 0, AnchoEsc-2, AltoEsc-2);
    setFixedSize(AnchoEsc+2, AltoEsc+25);
    ui->PButton_Ingresar->setGeometry((AnchoEsc/2)-111, AltoEsc/2, 101, 25);
    ui->PButton_Registrar->setGeometry((AnchoEsc/2)+10, AltoEsc/2, 101, 25);
    ui->LabelUser->setGeometry((AnchoEsc/2)-111, (AltoEsc/2)-65, 85, 25);
    ui->Label_Password->setGeometry((AnchoEsc/2)-111, (AltoEsc/2)-35, 85, 25);
    ui->LEdit_User->setGeometry((AnchoEsc/2)-9, (AltoEsc/2)-65, 120, 25);
    ui->LEdit_Password->setGeometry((AnchoEsc/2)-9, (AltoEsc/2)-35, 120, 25);
}

void MainWindow::GetUsers()
{

}

void MainWindow::Hide_Login()
{

}

bool MainWindow::CheckAccount(int Opcion)
{

}

