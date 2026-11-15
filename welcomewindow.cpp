#include "welcomewindow.h"

#include <QLabel>
#include <QPushButton>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QWidget>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Угадай пупсика"));

    // Панель инструментов (QToolBar) — один из виджетов-требований
    QToolBar *toolbar = addToolBar(tr("Главная"));
    QAction *exitAction = toolbar->addAction(tr("Выход"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Статус-бар (QStatusBar) — ещё один виджет
    statusBar()->showMessage(tr("Добро пожаловать!"));

    // Центральный виджет и layout
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    QLabel *title = new QLabel(tr("Угадай пупсика 1-ой группы"), central);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold;");

    QLabel *question = new QLabel(tr("Начать игру?"), central);
    question->setAlignment(Qt::AlignCenter);

    QPushButton *startBtn = new QPushButton(tr("Начать игру"), central);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(question);
    layout->addWidget(startBtn, 0, Qt::AlignCenter);
    layout->addStretch();

    setCentralWidget(central);

    // connect только с указателями на функции
    connect(startBtn, &QPushButton::clicked,
            this, &WelcomeWindow::onStartClicked);
}

void WelcomeWindow::onStartClicked()
{
    emit startGameRequested();
}