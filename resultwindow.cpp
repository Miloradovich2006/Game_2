#include "resultwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ResultWindow::ResultWindow(QWidget *parent)
    : QWidget(parent)
{
 setWindowTitle(tr("Результат игры"));

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel(tr("Игра окончена!"), this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold;");

    resultLabel = new QLabel(this);
    resultLabel->setAlignment(Qt::AlignCenter);

    answersBtn = new QPushButton(tr("Посмотреть правильные ответы"), this);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(resultLabel);
    layout->addWidget(answersBtn);
    layout->addStretch();

    connect(answersBtn, &QPushButton::clicked,
            this, &ResultWindow::answersRequested);
}

void ResultWindow::setResult(int score, int maxPossible)
{
    resultLabel->setText(
        tr("Ваш результат: %1 из %2").arg(score).arg(maxPossible));
}