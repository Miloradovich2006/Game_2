#pragma once
#include <QWidget>

class QLabel;
class QPushButton;

class ResultWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ResultWindow(QWidget *parent = nullptr);

signals:
    void answersRequested();

public slots:
    void setResult(int score, int maxPossible);

private:
    QLabel      *resultLabel = nullptr;
    QPushButton *answersBtn  = nullptr;
};