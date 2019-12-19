#ifndef WIDGET_H
#define WIDGET_H

#include <utility>
#include <map>

#include <QWidget>
#include "nxdata.h"
#include "lookandfeel.h"

class Widget : public QWidget
{
    Q_OBJECT
     Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)

public:

    Widget();
    void setState(const QString newState);
    QString state() const {
        return currentState;
    }

    Q_INVOKABLE void squareClicked(QString which) {
        setGridItem(which);
        toggleState();
    }

    Q_INVOKABLE QString getIconPath()
    {
        return nxdata->getIconPath(currentState);
    }

signals:
    void stateChanged(const QString newState);
    void gameOver(const QString gameStatus);
    void gameReset();

protected:
    std::unique_ptr<NXData> nxdata;

private slots:
    void setHomeView();
    void setGameView();
    void newGame();
    void endGame(const QString gameStatus);
private:

    void initializeHomeView();

    QPixmap *noughtImg;
    QPixmap *crossImg;
    QWidget *homeView;
    QWidget *gameView;
    void initializeGameView();
    QStackedLayout *layout;
    scoreLabel *noughtScoreLabel;
    scoreLabel *crossScoreLabel;
    infoLabel *whoseTurn;
    void resetGame();
    void initializeWins();
     void setScoreLabels();
      bool gameInProgress = false;
      QString firstPlayer;
       QString toggleNX(QString item);
       std::map<QString, int> wins;
       void incrementWinner(const QString winner);
        QString currentState;
        void setGridItem(const QString which);
        void toggleState();


};
#endif
