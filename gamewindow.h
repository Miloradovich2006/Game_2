#include <QWidget>
#include <QString>

class QLabel;
class QLineEdit;
class QPushButton;
class QProgressBar;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

signals:
    void answerSubmitted(const QString &answer);
    void pictureHintRequested();

public slots:
    void onRoundStarted(int current, int total,
                        const QString &textHint, int maxScore);
    void onScoreChanged(int score);
    void onAnswerResult(bool correct, int awarded, const QString &expectedName);
    void onPictureHintShown(const QString &imagePath);

private slots:
    void onAnswerClicked();
    void onPictureClicked();

private:
    QLabel       *roundLabel   = nullptr;
    QLabel       *hintLabel    = nullptr;
    QLabel       *scoreLabel   = nullptr;
    QLabel       *pictureLabel = nullptr;
    QLineEdit    *answerEdit   = nullptr;
    QPushButton  *answerBtn    = nullptr;
    QPushButton  *pictureBtn   = nullptr;
    QProgressBar *progressBar  = nullptr;
};