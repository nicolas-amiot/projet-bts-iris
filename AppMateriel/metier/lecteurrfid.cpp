#include "lecteurrfid.h"

LecteurRFID::LecteurRFID()
{
    this->id = 0;
    this->ip = QString();
    this->modele = QString();
    this->etatOn = false;
}

LecteurRFID::LecteurRFID(QString ip, QString modele, bool etatOn)
{
    this->id = 0;
    this->ip = ip;
    this->modele = modele;
    this->etatOn = etatOn;
}

LecteurRFID::~LecteurRFID()
{
}

long LecteurRFID::getId()
{
    return this->id;
}

QString LecteurRFID::getIp()
{
    return this->ip;
}

QString LecteurRFID::getModele()
{
    return this->modele;
}

bool LecteurRFID::getEtatOn()
{
    return this->etatOn;
}

void LecteurRFID::setId(long id)
{
    this->id = id;
}

void LecteurRFID::setIp(QString ip)
{
    this->ip = ip;
}

void LecteurRFID::setModele(QString modele)
{
    this->modele = modele;
}

void LecteurRFID::setEtatOn(bool etatOn)
{
    this->etatOn = etatOn;
}
