#include "metrologue.h"

Metrologue::Metrologue()
{
    this->id = 0;
    this->login = QString();
    this->password = QString();
}

Metrologue::Metrologue(QString login, QString password)
{
    this->id = 0;
    this->login = login;
    this->password = password;
}

Metrologue::~Metrologue()
{
}

long Metrologue::getId()
{
    return this->id;
}

QString Metrologue::getLogin()
{
    return this->login;
}

QString Metrologue::getPassword()
{
    return this->password;
}

void Metrologue::setId(long id)
{
    this->id = id;
}

void Metrologue::setLogin(QString login)
{
    this->login = login;
}

void Metrologue::setPassword(QString password)
{
    this->password = password;
}
