#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "lookandfeel.h"

class Widget : public QWidget
{
    Q_OBJECT

public:

    Widget();

private:

    void initializeHomeView();

    QPixmap *noughtImg;
    QPixmap *crossImg;
    QWidget *homeView;
    QStackedLayout *layout;

};
#endif
