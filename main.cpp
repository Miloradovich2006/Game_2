#include <QApplication>
#include <QObject>

#include "welcomewindow.h"
#include "gamewindow.h"
#include "gamecontroller.h"
#include "resultwindow.h"
#include "answerswindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WelcomeWindow welcome;
    GameWindow game;
    GameController controller;
    ResultWindow result;
    AnswersWindow answers;

    // 1) Старт игры
    QObject::connect(&welcome, &WelcomeWindow::startGameRequested,
                     &welcome, &QWidget::hide);
    QObject::connect(&welcome, &WelcomeWindow::startGameRequested,
                     &game, &QWidget::show);
    QObject::connect(&welcome, &WelcomeWindow::startGameRequested,
                     &controller, &GameController::startGame);

    // 2) Контроллер → игровое окно
    QObject::connect(&controller, &GameController::roundStarted,
                     &game, &GameWindow::onRoundStarted);
    QObject::connect(&controller, &GameController::scoreChanged,
                     &game, &GameWindow::onScoreChanged);
    QObject::connect(&controller, &GameController::answerResult,
                     &game, &GameWindow::onAnswerResult);
    QObject::connect(&controller, &GameController::pictureHintShown,
                     &game, &GameWindow::onPictureHintShown);

    // 3) Игровое окно → контроллер
    QObject::connect(&game, &GameWindow::answerSubmitted,
                     &controller, &GameController::submitAnswer);
    QObject::connect(&game, &GameWindow::pictureHintRequested,
                     &controller, &GameController::requestPictureHint);

    // 4) Конец игры → окно результата
    QObject::connect(&controller, &GameController::gameFinished,
                     &game, &QWidget::hide);
    QObject::connect(&controller, &GameController::gameFinished,
                     &result, &ResultWindow::setResult);
    QObject::connect(&controller, &GameController::gameFinished,
                     &result, &QWidget::show);

    // 5) Окно результата → окно правильных ответов
    QObject::connect(&result, &ResultWindow::answersRequested,
                     &answers, &QWidget::show);
    QObject::connect(&result, &ResultWindow::answersRequested,
                     &answers, [&]() { answers.setPeople(controller.people()); });

    welcome.resize(500, 500);
    game.resize(500, 500);
    result.resize(500, 500);
    answers.resize(500, 500);

    welcome.show();
    return app.exec();
}