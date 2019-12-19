#include "noughtscrosseswidget.h"

Widget::Widget()

{
    noughtImg = new QPixmap("://images/nought.png");
    crossImg = new QPixmap("://images/cross.png");
    initializeHomeView();

    layout = new QStackedLayout;
    layout->addWidget(homeView);
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


    startGameButton *startButton = new startGameButton("&Start game", this);

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



