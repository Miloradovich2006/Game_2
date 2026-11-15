#pragma once
#include <QMainWindow>

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT   // обязательно, иначе сигналы/слоты не заработают

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);

signals:
    // Собственный сигнал — его мы подключим к запуску игры
    void startGameRequested();

private slots:
    // Собственный слот, вызывается по клику на кнопку
    void onStartClicked();
};