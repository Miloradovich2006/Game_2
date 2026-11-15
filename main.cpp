#include <QApplication>
#include <QObject>

#include "welcomewindow.h"
#include "gamewindow.h"
#include "gamecontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WelcomeWindow welcome;
    GameWindow game;
    GameController controller;

    // Главное окно → запуск игры
    QObject::connect(&welcome, &WelcomeWindow::startGameRequested,
                     &welcome, &QWidget::hide);
    QObject::connect(&welcome, &WelcomeWindow::startGameRequested,
                     &game, &QWidget::show);
    QObject::connect(&welcome, &WelcomeWindow::startGameRequested,
                     &controller, &GameController::startGame);

    // Контроллер → игровое окно (обновление интерфейса)
    QObject::connect(&controller, &GameController::roundStarted,
                     &game, &GameWindow::onRoundStarted);
    QObject::connect(&controller, &GameController::scoreChanged,
                     &game, &GameWindow::onScoreChanged);
    QObject::connect(&controller, &GameController::answerResult,
                     &game, &GameWindow::onAnswerResult);
    QObject::connect(&controller, &GameController::pictureHintShown,
                     &game, &GameWindow::onPictureHintShown);

    // Игровое окно → контроллер (действия игрока)
    QObject::connect(&game, &GameWindow::answerSubmitted,
                     &controller, &GameController::submitAnswer);
    QObject::connect(&game, &GameWindow::pictureHintRequested,
                     &controller, &GameController::requestPictureHint);

    // Пока игра окончилась — просто закроем игровое окно
    // (в следующем коммите добавим окно результата)
    QObject::connect(&controller, &GameController::gameFinished,
                     &game, &QWidget::hide);

    welcome.resize(500, 350);
    game.resize(500, 500);
    welcome.show();

    return app.exec();
}