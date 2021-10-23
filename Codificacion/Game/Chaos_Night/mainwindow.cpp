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
    TimerFP = new QTimer;
    Background.load(":/Imagenes/game background.png");
    AnchoEsc = 1000;
    AltoEsc = 500;
    Jugador = new Player(Background.width(), AltoEsc);
    ui->graphicsView->setGeometry(0, 0, AnchoEsc+2, AltoEsc+2);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Escena->setSceneRect(0, 0, Background.width(), AltoEsc);
    setFixedSize(AnchoEsc+2, AltoEsc+27);
    ui->PButton_Ingresar->setGeometry((AnchoEsc/2)-111, AltoEsc/2, 101, 25);
    ui->PButton_Registrar->setGeometry((AnchoEsc/2)+10, AltoEsc/2, 101, 25);
    ui->LabelUser->setGeometry((AnchoEsc/2)-111, (AltoEsc/2)-65, 85, 25);
    ui->Label_Password->setGeometry((AnchoEsc/2)-111, (AltoEsc/2)-35, 85, 25);
    ui->LEdit_User->setGeometry((AnchoEsc/2)-9, (AltoEsc/2)-65, 120, 25);
    ui->LEdit_Password->setGeometry((AnchoEsc/2)-9, (AltoEsc/2)-35, 120, 25);
    ui->RButton_ShowPassword->setGeometry((AnchoEsc/2)+121, (AltoEsc/2)-34, 161, 25);
    ui->LEdit_Password->setEchoMode(QLineEdit::Password);
    ui->PButton_SingleMode->setGeometry((AnchoEsc/2)-111, AltoEsc/2, 101, 25);
    ui->PButton_Multiplayer->setGeometry((AnchoEsc/2)+10, AltoEsc/2, 101, 25);
    ui->Label_GameMode->setGeometry((AnchoEsc/2)-98, (AltoEsc/2)-45, 200, 25);
    ui->Label_GameMode->setText("Seleccione el modo de juego");
    ui->PButton_SingleMode->hide();
    ui->PButton_Multiplayer->hide();
    ui->Label_GameMode->hide();
    Jugador->SetImagenPlayer();
    connect(TimerFP, SIGNAL(timeout()), Jugador, SLOT(Actualizar()));
    GetUsers();
}

void MainWindow::GetUsers()
{
    Archivo->open(TxtPath, fstream::in);
    if(Archivo->is_open()){
        while(!Archivo->eof()){
            Users.push_back(Archivo->get());
        }
        Users.pop_back();
    }
    else{
        Users = "Archivo no encontrado.";
    }
    Archivo->close();
}

void MainWindow::Hide_Login()
{
    ui->LabelUser->hide();
    ui->Label_Password->hide();
    ui->LEdit_User->hide();
    ui->LEdit_Password->hide();
    ui->PButton_Ingresar->hide();
    ui->PButton_Registrar->hide();
    ui->RButton_ShowPassword->hide();
    ui->PButton_SingleMode->show();
    ui->PButton_Multiplayer->show();
    ui->Label_GameMode->show();
}

bool MainWindow::CheckAccount(int Opcion)
{
    int Section = 0;
    bool NextLine = false;
    string UsrTxt, PswrdTxt;
    if(Opcion == 1){
        for(unsigned long i=0; i<Users.length(); i++){
            if(Users[i] == ','){
                if(UsrTxt == Usuario){
                    PosUser = i-UsrTxt.length();
                    return true;
                }
                UsrTxt.clear();
                NextLine = false;
                for(unsigned long j=i; !NextLine; j++){
                    if(j >= Users.length()){
                        return false;
                    }
                    if(Users[j] == '\n'){
                        i = j+1;
                        NextLine = true;
                    }
                }
            }
            UsrTxt.push_back(Users[i]);
        }
        return false;
    }
    else {
        for(unsigned long i=PosUser; !NextLine; i++){
            if(Users[i] == ','){
                Section++;
                i++;
                if(Section > 1){
                    if(PswrdTxt == Password){
                        NextLine = true;
                        return true;
                    }
                    else {
                        NextLine = true;
                        return false;
                    }
                }
            }
            if(Section == 1){
                PswrdTxt.push_back(Users[i]);
            }
        }
        return false;
    }
}

void MainWindow::CentrarPlayer()
{
    ui->graphicsView->centerOn(Jugador);
}


void MainWindow::on_PButton_Ingresar_clicked()
{
    Usuario = ui->LEdit_User->text().toStdString();
    Password = ui->LEdit_Password->text().toStdString();
    if(CheckAccount(1)){
        if(CheckAccount(2)){
            Hide_Login();
        }
        else{
            QMessageBox::warning(this, "Error al iniciar sesion", "Fallo al iniciar sesión, contreseña incorrecta.");
        }
    }
    else {
        QMessageBox::warning(this, "Error de login", "Fallo al iniciar sesión, este usuario no existe.");
    }
}

void MainWindow::on_PButton_Registrar_clicked()
{
    string NewUsr;
    Usuario = ui->LEdit_User->text().toStdString();
    Password = ui->LEdit_Password->text().toStdString();
    if(Password == ""){
        QMessageBox::information(this, "Error de registro", "Fallo al crear cuenta, debe ingresar una contraseña.");
    }
    else{
        if(!CheckAccount(1)){
            NewUsr.append(Usuario + ',');
            NewUsr.append(Password + ',');
            NewUsr.push_back('\n');
            Users.append(NewUsr);
            Hide_Login();
        }
        else {
            QMessageBox::information(this, "Error de registro", "Fallo al crear cuenta, ya existe una cuenta de usuario asociada a ese nombre.");
        }
    }
}

void MainWindow::on_PButton_SingleMode_clicked()
{
    ui->Label_GameMode->hide();
    ui->PButton_SingleMode->hide();
    ui->PButton_Multiplayer->hide();
    ui->graphicsView->setScene(Escena);
    ui->graphicsView->setBackgroundBrush(QPixmap(Background));
    TimerFP->start(6);
    Jugador->Set_Vel(0, 0, 0, 0);
    Escena->addItem(Jugador);
    Jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    Jugador->setFocus();
    QObject::connect(Jugador, SIGNAL(CentrarInView()), this, SLOT(CentrarPlayer()));
}

void MainWindow::on_PButton_Multiplayer_clicked()
{
    ui->Label_GameMode->hide();
    ui->PButton_SingleMode->hide();
    ui->PButton_Multiplayer->hide();
}

void MainWindow::on_RButton_ShowPassword_clicked(bool checked)
{
    if(checked){
            ui->LEdit_Password->setEchoMode(QLineEdit::Normal);
        }
        else{
            ui->LEdit_Password->setEchoMode(QLineEdit::Password);
        }
}
