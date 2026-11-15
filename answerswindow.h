#pragma once
#include <QWidget>
#include "gamecontroller.h"   // нужен Person

class QTableWidget;

class AnswersWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AnswersWindow(QWidget *parent = nullptr);
    void setPeople(const QVector<Person> &people);

private:
    QTableWidget *table = nullptr;
};