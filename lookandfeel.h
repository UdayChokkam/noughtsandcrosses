#ifndef LOOK_H
#define LOOK_H

#include <QPushButton>
#include <QLabel>
#include <QtWidgets>

class startGameButton: public QPushButton
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
#endif
