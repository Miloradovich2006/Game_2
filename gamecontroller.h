#pragma once
#include <QObject>
#include <QString>
#include <QVector>

// Простая структура с данными одного человека
struct Person
{
    QString fullName;      // "Имя Отчество"
    QString textHint;      // текстовая подсказка
    QString imagePath;     // путь к картинке в ресурсах, может быть пустым
};

// Класс-контроллер: хранит данные, счёт, текущий раунд.
// Не содержит виджетов — только логика.
class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);

    void startGame();                              // начать новую игру
    void submitAnswer(const QString &answer);      // проверить ответ
    void requestPictureHint();                     // показать картинку

    const QVector<Person> &people() const { return m_people; }

signals:
    void roundStarted(int current, int total,
                      const QString &textHint, int maxScore);
    void scoreChanged(int score);
    void answerResult(bool correct, int awarded, const QString &expectedName);
    void pictureHintShown(const QString &imagePath);
    void gameFinished(int score, int maxPossible);

private:
    void nextRound();
    static QString normalize(const QString &s);    // нормализуем ввод

    QVector<Person> m_people;
    int m_currentIndex = -1;
    int m_score = 0;
    bool m_pictureUsedThisRound = false;
};