#include "answerswindow.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVBoxLayout>

AnswersWindow::AnswersWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Правильные ответы"));

    QVBoxLayout *layout = new QVBoxLayout(this);

    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(
        {tr("Имя и отчество"), tr("Текстовая подсказка"), tr("Картинка")});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    layout->addWidget(table);
}

void AnswersWindow::setPeople(const QVector<Person> &people)
{
    table->setRowCount(people.size());
    for (int i = 0; i < people.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(people[i].fullName));
        table->setItem(i, 1, new QTableWidgetItem(people[i].textHint));
        table->setItem(i, 2, new QTableWidgetItem(
            people[i].imagePath.isEmpty() ? tr("—") : people[i].imagePath));
    }
}