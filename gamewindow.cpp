#include "gamewindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPixmap>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Угадай пупсика — игра"));

    QVBoxLayout *layout = new QVBoxLayout(this);

    roundLabel  = new QLabel(this);
    progressBar = new QProgressBar(this);
    hintLabel   = new QLabel(this);
    hintLabel->setWordWrap(true);
    pictureLabel = new QLabel(this);
    pictureLabel->setAlignment(Qt::AlignCenter);
    pictureLabel->setMinimumHeight(150);
    scoreLabel  = new QLabel(this);

    answerEdit  = new QLineEdit(this);
    answerEdit->setPlaceholderText(tr("Имя Отчество"));

    answerBtn   = new QPushButton(tr("Ответить"), this);
    pictureBtn  = new QPushButton(tr("Подсказка-картинка"), this);

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(answerBtn);
    buttons->addWidget(pictureBtn);

    layout->addWidget(roundLabel);
    layout->addWidget(progressBar);
    layout->addWidget(hintLabel);
    layout->addWidget(pictureLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(answerEdit);
    layout->addLayout(buttons);
    layout->addStretch();

    // Все connect — с указателями на функции, без SIGNAL/SLOT
    connect(answerBtn, &QPushButton::clicked,
            this, &GameWindow::onAnswerClicked);
    connect(pictureBtn, &QPushButton::clicked,
            this, &GameWindow::onPictureClicked);
    // Enter в поле ввода = нажать "Ответить"
    connect(answerEdit, &QLineEdit::returnPressed,
            this, &GameWindow::onAnswerClicked);
}

void GameWindow::onRoundStarted(int current, int total,
                                const QString &textHint, int maxScore)
{
    roundLabel->setText(tr("Раунд %1 из %2. Максимум за раунд: %3")
                            .arg(current).arg(total).arg(maxScore));
    progressBar->setMaximum(total);
    progressBar->setValue(current - 1);
    hintLabel->setText(tr("Подсказка: %1").arg(textHint));
    pictureLabel->clear();
    answerEdit->clear();
    answerEdit->setFocus();
    pictureBtn->setEnabled(!textHint.isEmpty()); // позже можно доработать
}

void GameWindow::onScoreChanged(int score)
{
    scoreLabel->setText(tr("Счёт: %1").arg(score));
}

void GameWindow::onAnswerResult(bool correct, int awarded, const QString &expectedName)
{
    if (correct) {
        QMessageBox::information(this, tr("Верно!"),
                                 tr("Правильно! Начислено %1 балл(ов).").arg(awarded));
    } else {
        QMessageBox::warning(this, tr("Неверно"),
                             tr("Правильный ответ: %1").arg(expectedName));
    }
}

void GameWindow::onPictureHintShown(const QString &imagePath)
{
    pictureBtn->setEnabled(false);   // больше нельзя в этом раунде
    if (imagePath.isEmpty()) {
        pictureLabel->setText(tr("(картинка-подсказка для этого раунда недоступна)"));
        return;
    }
    QPixmap pix(imagePath);
    if (pix.isNull()) {
        pictureLabel->setText(tr("(картинка не загружена: %1)").arg(imagePath));
        return;
    }
    pictureLabel->setPixmap(pix.scaledToHeight(140, Qt::SmoothTransformation));
}

void GameWindow::onAnswerClicked()
{
    emit answerSubmitted(answerEdit->text());
}

void GameWindow::onPictureClicked()
{
    auto reply = QMessageBox::question(
        this, tr("Подсказка-картинка"),
        tr("Вы уверены? Вы можете потерять 1 балл."),
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit pictureHintRequested();
    }
}