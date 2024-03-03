#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMediaPlayer>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool m_isSoundOn;
    std::unique_ptr<QMediaPlayer> m_pShortSound;
    std::unique_ptr<QMediaPlayer> m_pBackgroundSound;
    QImage m_backgroundImage;

    void settingProgramm();//настройка приложения
    void createSignalSlotConnections();//создать связь сигналов и слотов

private slots:
    void soundOn_action_clicked();//нажатие на Звук->Вкл.
    void soundOff_action_clicked();//нажатие на Звук->Выкл.
    void changeImageSlot();//реакция на изменение картинки
    void backgroundMusicStateChangedSlot(QMediaPlayer::State state);//изменение состояния фоновой музыки
    void showInfoMessageSlot();//нажатие "О программе..."

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
