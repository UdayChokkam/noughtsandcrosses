#include <stdexcept>

#include <Qt>
#include <QtWidgets>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QFrame>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QQuickWidget>

#include <QQmlContext>
#include <QQmlEngine>

#include <QPixmap>
#include "noughtscrosseswidget.h"


Widget::Widget()

{



    firstPlayer = "nought";

    noughtImg = new QPixmap("://images/nought.png");
    crossImg = new QPixmap("://images/cross.png");
    initializeHomeView();
    initializeGameView();
    layout = new QStackedLayout;
    layout->addWidget(homeView);
    layout->addWidget(gameView);
    setLayout(layout);
}

void Widget::initializeHomeView()
{

    homeView = new QWidget;

    int size {46};
    QPixmap noughtImg46 = noughtImg->scaled(size, size, Qt::KeepAspectRatio,
                                            Qt::SmoothTransformation);
    QLabel *noughtHomeIcon = new QLabel;
    noughtHomeIcon->setPixmap(noughtImg46);


    QPixmap crossImg46 = crossImg->scaled(size, size, Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation);
    QLabel *crossHomeIcon = new QLabel;
    crossHomeIcon->setPixmap(crossImg46);


    QFrame *whiteLine = new QFrame;
    whiteLine->setFrameStyle(QFrame::VLine | QFrame::Plain);
    whiteLine->setStyleSheet("border: 2px solid white");
    whiteLine->setFixedHeight(80);


    QHBoxLayout *iconBox = new QHBoxLayout;
    iconBox->addStretch(100);
    iconBox->addWidget(noughtHomeIcon, Qt::AlignRight);
    iconBox->addStretch(10);
    iconBox->addWidget(whiteLine, Qt::AlignCenter);
    iconBox->addStretch(10);
    iconBox->addWidget(crossHomeIcon, Qt::AlignLeft);
    iconBox->addStretch(100);


    gameLabel *nameLabel = new gameLabel();
    QString noughtStr = "<font color=\"#F08113\">noughts</font>";
    QString plusStr = "<font color=\"white\"> + </font>";
    QString crossStr = "<font color=\"#B8398E\">crosses</font>";
    nameLabel->setText(noughtStr + plusStr + crossStr);
    nameLabel->setAlignment(Qt::AlignCenter);


    Button *startButton = new Button("&Start game", this);
    connect(startButton, SIGNAL(clicked()), this, SLOT(setGameView()));
    QHBoxLayout *startButtonBox = new QHBoxLayout;
    startButtonBox->addStretch(50);
    startButtonBox->addWidget(startButton, Qt::AlignCenter);
    startButtonBox->addStretch(50);

    QVBoxLayout *homeLayout = new QVBoxLayout;
    homeLayout->addSpacing(270);
    homeLayout->addWidget(nameLabel);
    homeLayout->addSpacing(85);
    homeLayout->addLayout(iconBox);
    homeLayout->addSpacing(100);
    homeLayout->addLayout(startButtonBox);
    homeLayout->addSpacing(78);
    homeView->setLayout(homeLayout);
}

void Widget::initializeGameView()
{

    gameView = new QWidget;


    int size {23};
    QPixmap noughtImg23 = noughtImg->scaled(size, size, Qt::KeepAspectRatio,
                                            Qt::SmoothTransformation);
    QLabel *noughtScoreIcon = new QLabel;
    noughtScoreIcon->setPixmap(noughtImg23);
    QPixmap crossImg23 = crossImg->scaled(size, size, Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation);
    QLabel *crossScoreIcon = new QLabel;
    crossScoreIcon->setPixmap(crossImg23);


    QQuickWidget *gameGrid = new QQuickWidget;
    gameGrid->engine()->rootContext()->setContextProperty("W", this);
    gameGrid->setSource(QUrl(QStringLiteral("qrc:/qml/gamegrid.qml")));


    QHBoxLayout *gameGridBox = new QHBoxLayout;
    gameGridBox->addStretch(20);
    gameGridBox->addWidget(gameGrid, Qt::AlignCenter);
    gameGridBox->addStretch(20);


    greyButton *backButton = new greyButton("&Back", this);
    Button *newButton = new Button("&New game", this);
    connect(backButton, SIGNAL(clicked()), this, SLOT(setHomeView()));
    connect(newButton, SIGNAL(clicked()), this, SLOT(newGame()));


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(newButton);


    noughtScoreLabel = new scoreLabel("nought");
    QHBoxLayout *noughtScoreBox = new QHBoxLayout;
    noughtScoreBox->addWidget(noughtScoreIcon, Qt::AlignRight);
    noughtScoreBox->addWidget(noughtScoreLabel, Qt::AlignLeft);

    crossScoreLabel = new scoreLabel("cross");
    QHBoxLayout *crossScoreBox = new QHBoxLayout;
    crossScoreBox->addWidget(crossScoreIcon, Qt::AlignRight);
    crossScoreBox->addWidget(crossScoreLabel, Qt::AlignLeft);





    QHBoxLayout *scoreBox = new QHBoxLayout;
    scoreBox->addLayout(noughtScoreBox);
    scoreBox->addStretch(50);
    scoreBox->addLayout(crossScoreBox);


    whoseTurn = new infoLabel;
    whoseTurn->setAlignment(Qt::AlignCenter);


    gameFrame *frame = new gameFrame;
    frame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    frame->setBaseSize(490, 660);


    QFrame *whiteLine = new QFrame;
    whiteLine->setFrameStyle(QFrame::HLine | QFrame::Plain);
    whiteLine->setStyleSheet("border: 2px solid white");


    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->addLayout(scoreBox);
    frameLayout->addWidget(whiteLine);
    frameLayout->addWidget(whoseTurn);
    frameLayout->addLayout(gameGridBox);
    frameLayout->addSpacing(75);
    frame->setLayout(frameLayout);


    connect(this, SIGNAL(stateChanged(QString)), whoseTurn, SLOT(setTextTurn(QString)));

    connect(this, SIGNAL(gameOver(QString)), this, SLOT(endGame(QString)));


    QVBoxLayout *gameLayout = new QVBoxLayout;
    gameLayout->addWidget(frame);
    gameLayout->addSpacing(33);
    gameLayout->addLayout(buttonLayout);
    gameLayout->addSpacing(78);
    gameView->setLayout(gameLayout);

}

void Widget::setGameView()
{


    layout->setCurrentIndex(1);
}


void Widget::setHomeView()
{

    layout->setCurrentIndex(0);
}


void Widget::endGame(const QString gameStatus)
{

    gameInProgress = false;


    if (gameStatus=="draw") {
        whoseTurn->setTextDraw();
    }
    else {
        whoseTurn->setTextWin(gameStatus);
        incrementWinner(gameStatus);
    }

}



void Widget::incrementWinner(const QString winner)
{
    wins[winner] += 1;

}

void Widget::setState(const QString newState)
{

    if (newState == "cross" || newState == "nought") {
        currentState = newState;
        emit stateChanged(currentState);
    }
    else
        throw std::invalid_argument("State should be 'nought' or 'cross'.");
}

QString Widget::toggleNX(QString item)
{
    if (item == "cross")
        return "nought";
    else if (item == "nought")
        return "cross";
    else
        throw std::invalid_argument("State should be 'nought' or 'cross'.");
}

void Widget::setGridItem(const QString which)
{

    std::size_t n {which.toUInt()};

    std::size_t row {n/3};
    std::size_t column {n%3};
    QString gameStatus = nxdata->setItem(row, column, currentState);

}

void Widget::toggleState()
{

    if (gameInProgress) {
        setState(toggleNX(currentState));
    }
}




