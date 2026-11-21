#include "gamecontroller.h"

GameController::GameController(QObject *parent)
    : QObject(parent)
{
    // Пока 10 ЗАГЛУШЕК. Позже Маша/Амалия заменят на реальных людей
    // и вынесут в people.json в .qrc.
    m_people = {
                 {QStringLiteral("Шабашева Милена"),     QStringLiteral("Твиттерская..."),       QString()},
                 {QStringLiteral("Беляева Ангелина"),    QStringLiteral("Депутатка"),        QString()},
                 {QStringLiteral("Романова Мария"), QStringLiteral("Дресс код на свадьбу зеленый. Вход строго с открыткой"),   QString()},
                 {QStringLiteral("Козлова Софья"),  QStringLiteral("Каждую пару пытется убиться/сломать мебель/все сразу"),    QString()},
                 {QStringLiteral("Сорокина Мария"), QStringLiteral("Мечта управлять самолетом"),    QString()},
                 {QStringLiteral("Кучумова Амалия"), QStringLiteral("Сборник цитат"),       QString()},
                 {QStringLiteral("Новожилова Карина"), QStringLiteral("Сама написала только два курсача...один по алгебре"),       QString()},
                 {QStringLiteral("Лобанова Любовь"),  QStringLiteral("Главная роблоксерша"),       QString()},
                 {QStringLiteral("Антон Сергеевич"),    QStringLiteral("Ждем рефлексию всей группой"), QString()},
                 {QStringLiteral("Махова София"),QStringLiteral("Искала мужа по фамилии"),             QString()},
                 };
}

QString GameController::normalize(const QString &s)
{
    // Убираем лишние пробелы, приводим к нижнему регистру, ё → е
    QString t = s.trimmed().simplified().toLower();
    t.replace(QChar(u'ё'), QChar(u'е'));
    return t;
}

void GameController::startGame()
{
    m_currentIndex = -1;
    m_score = 0;
    emit scoreChanged(m_score);
    nextRound();
}

void GameController::nextRound()
{
    ++m_currentIndex;
    if (m_currentIndex >= m_people.size()) {
        // Игра окончена
        emit gameFinished(m_score, m_people.size() * 2);
        return;
    }
    m_pictureUsedThisRound = false;
    const Person &p = m_people[m_currentIndex];
    emit roundStarted(m_currentIndex + 1, m_people.size(), p.textHint, 2);
}

void GameController::submitAnswer(const QString &answer)
{
    if (m_currentIndex < 0 || m_currentIndex >= m_people.size())
        return;

    const Person &p = m_people[m_currentIndex];
    bool correct = (normalize(answer) == normalize(p.fullName));
    int awarded = 0;
    if (correct) {
        awarded = m_pictureUsedThisRound ? 1 : 2;
        m_score += awarded;
        emit scoreChanged(m_score);
    }
    emit answerResult(correct, awarded, p.fullName);

    // Сразу переходим к следующему раунду. Сигнал answerResult уже
    // обработан (в GameWindow он покажет QMessageBox и дождётся закрытия),
    // поэтому roundStarted обновит интерфейс уже после закрытия сообщения.
    nextRound();
}

void GameController::requestPictureHint()
{
    if (m_currentIndex < 0 || m_currentIndex >= m_people.size())
        return;
    if (m_pictureUsedThisRound)
        return;                    // картинка уже использована в этом раунде
    m_pictureUsedThisRound = true;
    emit pictureHintShown(m_people[m_currentIndex].imagePath);
}