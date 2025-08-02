QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gallery.cpp \
    main.cpp \
    name.cpp \
    page1.cpp \
    page2.cpp \
    page3.cpp

HEADERS += \
    gallery.h \
    name.h \
    page1.h \
    page2.h \
    page3.h \
    tiles.h

FORMS += \
    gallery.ui \
    name.ui \
    page1.ui \
    page2.ui \
    page3.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Agent1.qrc \
    angus.qrc \
    angus2.qrc \
    b.qrc \
    billy.qrc \
    billy2.qrc \
    boi.qrc \
    boi2.qrc \
    brown.qrc \
    brown2.qrc \
    bunka.qrc \
    bunka2.qrc \
    colonelbaba.qrc \
    colonelbaba2.qrc \
    death.qrc \
    death2.qrc \
    duraham.qrc \
    duraham2.qrc \
    eloi.qrc \
    eloi2.qrc \
    elsa.qrc \
    elsa2.qrc \
    frost.qrc \
    frost2.qrc \
    grid1.qrc \
    grid2.qrc \
    grid3.qrc \
    grid4.qrc \
    grid5.qrc \
    grid6.qrc \
    grid7.qrc \
    grid8.qrc \
    image1.qrc \
    image2.qrc \
    image3.qrc \
    kabu.qrc \
    kabu2.qrc \
    kanar.qrc \
    kanar2.qrc \
    karissa.qrc \
    karissa2.qrc \
    khan.qrc \
    khan2.qrc \
    medusa.qrc \
    medusa2.qrc \
    rajakal.qrc \
    rajakal2.qrc \
    rambo.qrc \
    rambo2.qrc \
    receton.qrc \
    reketon2.qrc \
    sabrina.qrc \
    sabrina2.qrc \
    salih.qrc \
    salih2.qrc \
    sanka.qrc \
    sanka2.qrc \
    sirlamorak.qrc \
    sirlamorak2.qrc \
    sirphilip.qrc \
    sirphilip2.qrc \
    tusk.qrc \
    tusk2.qrc
