#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetUp_MainWindow();
    //Organizar nombre de pestaña y miniatura.
}

void MainWindow::IncreaseScore()
{
    Puntaje += 10;
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
    TimerSpawnE = new QTimer;
    TimerIncreaseDif = new QTimer;
    Background.load(":/Imagenes/game background.png");
    AnchoEsc = 1000;
    AltoEsc = 500;
    Jugador = new Player(Background.width(), AltoEsc, AnchoEsc);
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
    QFont ScoreFont("Arial", 30, QFont::Bold);
    ui->Label_Score->setGeometry(100, 0, 155, 50);
    ui->Label_Score->setFont(ScoreFont);
    ui->Label_Score->setText("Puntaje: ");
    ui->Label_ValueScore->setGeometry(265, 0, 100, 50);
    ui->Label_ValueScore->setFont(ScoreFont);
    ui->Label_Lives->setGeometry(AnchoEsc/2, 0, 120, 50);
    ui->Label_Lives->setFont(ScoreFont);
    ui->Label_Lives->setText("Vidas: ");
    ui->Label_ValueLives->setGeometry(630, 0, 50, 50);
    ui->Label_ValueLives->setFont(ScoreFont);
    ui->PButton_SingleMode->hide();
    ui->PButton_Multiplayer->hide();
    ui->Label_GameMode->hide();
    ui->Label_Score->hide();
    ui->Label_ValueScore->hide();
    ui->Label_Lives->hide();
    ui->Label_ValueLives->hide();
    Jugador->SetImagenPlayer();
    connect(TimerFP, SIGNAL(timeout()), Jugador, SLOT(Actualizar()));
    connect(TimerSpawnE, SIGNAL(timeout()), Jugador, SLOT(AgregarEnemigo()));
    connect(TimerIncreaseDif, SIGNAL(timeout()), this, SLOT(IncreasDifficulty()));
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

void MainWindow::UpdateUsers(string Data, int Opcion)
{
    if(Opcion == 1){        //Guarda Usuario en la base de datos.
        fstream Archivo2 (TxtPath, fstream::out);
        Archivo2 << Data;
        Archivo2.close();
    }
    else {
        string Usr;
        Users.erase(PosUser, Users.find('\n')+1);
        PosUser = Users.length();
        Usr.append(Usuario + ',');
        Usr.append(Password + ',');
        Usr.append(to_string(VidasPlayer) + ',');
        Usr.append(to_string(VidasEnemigos) + ',');
        Usr.append(to_string(TiempoAparicionE) + ',');
        Usr.append(to_string(Puntaje) + '\n');
        Users.append(Usr);
        fstream Archivo2 (TxtPath, fstream::out);
        Archivo2 << Users;
        Archivo2.close();
    }

}

void MainWindow::GetData()
{
    int Section = 0;
    bool Finish = false;
    string Text;
    for(unsigned long i=PosUser; !Finish; i++){
        if(i==PosUser){
            i += (Usuario.length()+Password.length())+2;
        }
        if(Section == 0){
            if(Users[i] == ','){
                VidasPlayer = atoi(Text.c_str());
                i++;
                Text.clear();
                Section++;
            }
            Text.push_back(Users[i]);
        }
        else if(Section == 1){
            if(Users[i] == ','){
                VidasEnemigos = atoi(Text.c_str());
                i++;
                Text.clear();
                Section++;
            }
            Text.push_back(Users[i]);
        }
        else if(Section == 2){
            if(Users[i] == ','){
                TiempoAparicionE = atoi(Text.c_str());
                i++;
                Text.clear();
                Section++;
            }
            Text.push_back(Users[i]);
        }
        else if(Section == 3){
            if(Users[i] == '\n'){
                Puntaje = atoi(Text.c_str());
                Finish = true;
            }
            Text.push_back(Users[i]);
        }
    }
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

void MainWindow::StopAll()
{
    TimerFP->stop();
    TimerSpawnE->stop();
}

bool MainWindow::CheckAccount(int Opcion)
{
    int Section = 0;
    bool NextLine = false;
    string UsrTxt, PswrdTxt;
    if(Opcion == 1){        //Valida Usuario
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
    else {      //Valida contraseña
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
            GetData();
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
            VidasPlayer = 3;
            VidasEnemigos = 3;
            TiempoAparicionE = 4000;
            Puntaje = 0;
            NewUsr.append(Usuario + ',');
            NewUsr.append(Password + ',');
            NewUsr.append(to_string(VidasPlayer) + ',');
            NewUsr.append(to_string(VidasEnemigos) + ',');
            NewUsr.append(to_string(TiempoAparicionE) + ',');
            NewUsr.append(to_string(Puntaje));
            NewUsr.push_back('\n');
            PosUser = Users.length();
            Users.append(NewUsr);
            UpdateUsers(Users, 1);      //Guardar nuevo usuario en el Txt;
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
    ui->Label_Score->show();
    ui->Label_ValueScore->setText(to_string(Puntaje).c_str());
    ui->Label_ValueScore->show();
    ui->Label_Lives->show();
    ui->Label_ValueLives->setText(to_string(VidasPlayer).c_str());
    ui->Label_ValueLives->show();
    ui->graphicsView->setScene(Escena);
    ui->graphicsView->setBackgroundBrush(QPixmap(Background));
    TimerFP->start(6);
    TimerSpawnE->start(TiempoAparicionE); //Tiempo  aumente con la dificultad
    TimerIncreaseDif->start(30000);
    Jugador->SetLivesPlayer(VidasPlayer);
    Jugador->SetLivesEnemies(VidasEnemigos);
    Jugador->Set_Vel(0, 0, 0, 0);
    Escena->addItem(Jugador);
    Jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    Jugador->setFocus();
    QObject::connect(Jugador, SIGNAL(CentrarInView()), this, SLOT(CentrarPlayer()));
    connect(Jugador, SIGNAL(RestarVida()), this, SLOT(GameOver()));
    connect(Jugador, SIGNAL(AumentarPuntaje()), this, SLOT(UpScore()));
}

void MainWindow::on_PButton_Multiplayer_clicked()
{
    ui->Label_GameMode->hide();
    ui->PButton_SingleMode->hide();
    ui->PButton_Multiplayer->hide();
    QMessageBox::information(this, "Error 404", "Lo sentimos, esta modalidad aun se encuentra en etapa de creacion, esperela pronto.");
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

void MainWindow::IncreasDifficulty()
{
    if((VidasEnemigos != 5) || (TiempoAparicionE != 1000)){
        if(VidasEnemigos < 5){
            VidasEnemigos++;
            Jugador->SetLivesEnemies(VidasEnemigos);
        }
        if(TiempoAparicionE > 1000){
            TiempoAparicionE -= 1000;
            TimerSpawnE->stop();
            TimerSpawnE->start(TiempoAparicionE);
        }
        UpdateUsers("", 2);
    }
    else {
        TimerIncreaseDif->stop();
    }
}

void MainWindow::UpScore()
{
    Puntaje += 10;
    ui->Label_ValueScore->setText(to_string(Puntaje).c_str());
    UpdateUsers("", 2);
}

void MainWindow::GameOver()
{
    VidasPlayer = Jugador->GetLivesPlayer();
    ui->Label_ValueLives->setText(to_string(VidasPlayer).c_str());
    UpdateUsers("", 2);
    if(VidasPlayer == 0){
        qDebug() << "Sin Vidas.";
        VidasPlayer = 3;
        UpdateUsers("", 2);
        Escena->clear();
        StopAll();
        QMessageBox::warning(this, "GAME OVER", "Te quedaste sin vidas, has perdido el juego así que este se cerrará.");
        this->close();
    }
}
