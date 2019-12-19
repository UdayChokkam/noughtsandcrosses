#ifndef LOOK_H
#define LOOK_H

#include <stdexcept>

#include <QtWidgets>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QPixmap>

class Button: public QPushButton
{
    Q_OBJECT
public:
    using QPushButton::QPushButton;
};

class gameLabel : public QLabel
{
    Q_OBJECT
public:
    using QLabel::QLabel;

protected:

    QString plural(const QString str)
    {
        if (str == "nought")
            return "noughts";
        else if (str == "cross")
            return "crosses";
        else
            throw std::invalid_argument("Word should be 'nought' or 'cross'.");
    }

    QString capitalize(QString str)
    {
        str.replace(0, 1, str[0].toUpper());
        return str;
    }
};

class titleLabel : public gameLabel
{
    Q_OBJECT
};

class scoreLabel : public gameLabel
{
    Q_OBJECT
public:
    scoreLabel(const QString item)
    {
        setItem(item);
    }

public slots:
    void setText(int count)
    {
        QString labelText = QString(text + " score: %1").arg(count);
        QLabel::setText(labelText);
    }

    void setItem(const QString item)
    {
        text = plural(item);
        text = capitalize(text);
    }


protected:
    QString text;

};

class infoLabel : public gameLabel
{
    Q_OBJECT


public slots:
    void setTextTurn(const QString text="nought")
    {
        QString labelText = plural(text)  + " turn!";
        this->setText(labelText);
    }

    void setTextWin(const QString text)
    {
        QString labelText = plural(text)  + " won!";
        this->setText(labelText);
    }

    void setTextDraw()
    {
        this->setText("it's a draw");
    }
};

class greyButton : public QPushButton
{
    Q_OBJECT
public:
    using QPushButton::QPushButton;
};

class gameFrame : public QFrame
{
    Q_OBJECT
public:
    using QFrame::QFrame;
};

#endif
