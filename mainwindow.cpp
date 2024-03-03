#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settingProgramm();
    this->createSignalSlotConnections();

}

//----------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//----------------------------------------------------------------------------------------------------

//настройка приложения
void MainWindow::settingProgramm()
{
    this->setMinimumSize(200, 250);
    ui->horizontalSlider->setRange(0, 100);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setWindowTitle("Цветной круг");
    this->setWindowIcon(QIcon(":/images/images/aplIco.png"));
    m_isSoundOn = true;

    ui->sound_menu->setIcon(QIcon(":/images/images/notes.ico"));
    ui->soundOn_action->setIcon(QIcon(":/images/images/soundOn.ico"));
    ui->soundOn_action->setText("Вкл.\t\u2713");
    ui->soundOff_action->setIcon(QIcon(":/images/images/soundOff.ico"));
    ui->about_action->setIcon(QIcon(":/images/images/questionmark.ico"));
    ui->exit_action->setIcon(QIcon(":/images/images/cross.ico"));

    m_backgroundImage.load(":/images/images/khogvarts.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(m_backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(palette);

    m_pShortSound = std::make_unique<QMediaPlayer>();
    m_pShortSound->setMedia(QUrl("qrc:/music/music/short.mp3"));

    m_pBackgroundSound = std::make_unique<QMediaPlayer>();
    m_pBackgroundSound->setMedia(QUrl("qrc:/music/music/dendy.mp3"));
    m_pBackgroundSound->setVolume(35);
    m_pBackgroundSound->play();

}

//----------------------------------------------------------------------------------------------------

//создать связь сигналов и слотов
void MainWindow::createSignalSlotConnections()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->circle_widget, SLOT(sliderValueChanged(int)));
    connect(ui->soundOn_action, SIGNAL(triggered(bool)), this, SLOT(soundOn_action_clicked()));
    connect(ui->soundOff_action, SIGNAL(triggered(bool)), this, SLOT(soundOff_action_clicked()));
    connect(ui->circle_widget, SIGNAL(changeImage()), this, SLOT(changeImageSlot()));
    connect(ui->exit_action, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(m_pBackgroundSound.get(), SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(backgroundMusicStateChangedSlot(QMediaPlayer::State)));
    connect(ui->about_action, SIGNAL(triggered(bool)), this, SLOT(showInfoMessageSlot()));
}

//----------------------------------------------------------------------------------------------------

//нажатие на Звук->Вкл.
void MainWindow::soundOn_action_clicked()
{
    if(!m_isSoundOn)
    {
        m_isSoundOn = true;
        ui->soundOn_action->setText("Вкл.\t\u2713");
        ui->soundOff_action->setText("Выкл.");
        m_pBackgroundSound->play();
    }
}

//----------------------------------------------------------------------------------------------------

//нажатие на Звук->Выкл.
void MainWindow::soundOff_action_clicked()
{
    if(m_isSoundOn)
    {
        m_isSoundOn = false;
        ui->soundOn_action->setText("Вкл.");
        ui->soundOff_action->setText("Выкл.\t\u2713");
        m_pBackgroundSound->pause();
    }
}

//----------------------------------------------------------------------------------------------------

//реакция на изменение картинки
void MainWindow::changeImageSlot()
{
    if(m_isSoundOn)
    {
        m_pShortSound->play();
    }
}

//----------------------------------------------------------------------------------------------------

//изменение состояния фоновой музыки
void MainWindow::backgroundMusicStateChangedSlot(QMediaPlayer::State state)
{
    //бесконечное воспроизведение
    if(state == QMediaPlayer::StoppedState)
    {
        m_pBackgroundSound->play();
    }
}

//----------------------------------------------------------------------------------------------------

//нажатие "О программе..."
void MainWindow::showInfoMessageSlot()
{
    QMessageBox::information(this, "О программе \"Цветной круг\"", "Программа является рашением задания 36.1 курса по C++. Нужно отрисовать определенного цвета круг в зависимости от положения ползунка");
}

//-----------------------------------------------------------------------------------------------------


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(m_backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(palette);

    Q_UNUSED(event)
}
