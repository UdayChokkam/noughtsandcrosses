TEMPLATE = app
TARGET = noughtsandcrosses

QT += quick qml widgets quickwidgets

SOURCES += \
    main.cpp \
    noughtscrosseswidget.cpp \
    nxdata.cpp

HEADERS += \
    lookandfeel.h \
    noughtscrosseswidget.h \
    nxdata.h

target.path = .
INSTALLS += target

RESOURCES += \
    resources.qrc


