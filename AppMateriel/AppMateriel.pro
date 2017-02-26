#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T19:51:50
#
#-------------------------------------------------

QT       += core gui sql
QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppMateriel
TEMPLATE = app


SOURCES += \
    metier/typeserviceimpl.cpp \
    metier/type.cpp \
    metier/salleserviceimpl.cpp \
    metier/salle.cpp \
    metier/portiqueserviceimpl.cpp \
    metier/portique.cpp \
    metier/metrologueserviceimpl.cpp \
    metier/metrologue.cpp \
    metier/metierfactory.cpp \
    metier/materielserviceimpl.cpp \
    metier/materiel.cpp \
    metier/localisationserviceimpl.cpp \
    metier/localisation.cpp \
    metier/lecteurrfidserviceimpl.cpp \
    metier/lecteurrfid.cpp \
    metier/batimentserviceimpl.cpp \
    metier/batiment.cpp \
    physique/typedataserviceimpl.cpp \
    physique/servicesql.cpp \
    physique/salledataserviceimpl.cpp \
    physique/portiquedataserviceimpl.cpp \
    physique/physiquefactory.cpp \
    physique/metrologuedataserviceimpl.cpp \
    physique/materieldataserviceimpl.cpp \
    physique/localisationdataserviceimpl.cpp \
    physique/lecteurrfiddataserviceimpl.cpp \
    physique/batimentdataserviceimpl.cpp \
    client/main.cpp\
    client/menuwindow.cpp \
    client/connectionwindow.cpp \
    client/adminwindow.cpp \
    physiqueIO/physiqueiofactory.cpp \
    client/encodetomd5.cpp \
    physiqueIO/lecteurrfidioserviceimpl.cpp \
    physiqueIO/lecteurrfidioservicetestimpl.cpp \
    physiqueIO/physiqueiofactory.cpp \
    physiqueIO/lecteurrfidioservicetestimpl.cpp \
    physiqueIO/lecteurrfidioserviceimpl.cpp \
    physiqueIO/lecteurdriver.cpp

HEADERS  += \
    metier/typeserviceimpl.h \
    metier/typeservice.h \
    metier/type.h \
    metier/salleserviceimpl.h \
    metier/salleservice.h \
    metier/salle.h \
    metier/portiqueserviceimpl.h \
    metier/portiqueservice.h \
    metier/portique.h \
    metier/metrologueserviceimpl.h \
    metier/metrologueservice.h \
    metier/metrologue.h \
    metier/metierfactory.h \
    metier/materielserviceimpl.h \
    metier/materielservice.h \
    metier/materiel.h \
    metier/localisationserviceimpl.h \
    metier/localisationservice.h \
    metier/localisation.h \
    metier/lecteurrfidserviceimpl.h \
    metier/lecteurrfidservice.h \
    metier/lecteurrfid.h \
    metier/batimentserviceimpl.h \
    metier/batimentservice.h \
    metier/batiment.h \
    physique/typedataserviceimpl.h \
    physique/typedataservice.h \
    physique/servicesql.h \
    physique/salledataserviceimpl.h \
    physique/salledataservice.h \
    physique/portiquedataserviceimpl.h \
    physique/portiquedataservice.h \
    physique/physiquefactory.h \
    physique/metrologuedataserviceimpl.h \
    physique/metrologuedataservice.h \
    physique/materieldataserviceimpl.h \
    physique/materieldataservice.h \
    physique/localisationdataserviceimpl.h \
    physique/localisationdataservice.h \
    physique/lecteurrfiddataserviceimpl.h \
    physique/lecteurrfiddataservice.h \
    physique/batimentdataserviceimpl.h \
    physique/batimentdataservice.h \
    client/menuwindow.h \
    client/connectionwindow.h \
    client/adminwindow.h \
    physiqueIO/physiqueiofactory.h \
    physiqueIO/lecteurrfidioserviceimpl.h \
    physiqueIO/lecteurrfidioservice.h \
    client/encodetomd5.h \
    physiqueIO/lecteurrfidioservicetestimpl.h \
    physiqueIO/physiqueiofactory.h \
    physiqueIO/lecteurrfidioservicetestimpl.h \
    physiqueIO/lecteurrfidioserviceimpl.h \
    physiqueIO/lecteurrfidioservice.h \
    physiqueIO/lecteurdriver.h

FORMS    += \
    menuwindow.ui \
    connectionwindow.ui \
    adminwindow.ui

RESOURCES += \
    ressources.qrc
