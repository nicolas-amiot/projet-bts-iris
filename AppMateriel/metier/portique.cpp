#include "portique.h"

Portique::Portique()
{
    this->id = 0;
    this->x = 0;
    this->y = 0;
    this->salle1 = Salle();
    this->salle2 = Salle();
    this->lecteur = LecteurRFID();
}

Portique::Portique(float x, float y, Salle salle1, Salle salle2, LecteurRFID lecteur)
{
    this->id = 0;
    this->x = x;
    this->y = y;
    this->salle1 = salle1;
    this->salle2 = salle2;
    this->lecteur = lecteur;
}

Portique::~Portique()
{
}

long Portique::getId()
{
    return this->id;
}

float Portique::getX()
{
    return this->x;
}

float Portique::getY()
{
    return this->y;
}

Salle Portique::getSalle1()
{
    return this->salle1;
}

Salle Portique::getSalle2()
{
    return this->salle2;
}

LecteurRFID Portique::getLecteurRFID()
{
    return this->lecteur;
}

void Portique::setId(long id)
{
    this->id = id;
}

void Portique::setX(float x)
{
    this->x = x;
}

void Portique::setY(float y)
{
    this->y = y;
}

void Portique::setSalle1(Salle salle1)
{
    this->salle1 = salle1;
}

void Portique::setSalle2(Salle salle2)
{
    this->salle2 = salle2;
}

void Portique::setLecteurRFID(LecteurRFID lecteur)
{
    this->lecteur = lecteur;
}
