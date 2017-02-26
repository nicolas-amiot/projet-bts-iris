#include "salle.h"

Salle::Salle()
{
    this->id = 0;
    this->x_ini = 0;
    this->y_ini = 0;
    this->x_fin = 0;
    this->y_fin = 0;
    this->numSalle = 0;
    this->nomSalle = QString();
    this->nomAtelier = QString();
}

Salle::Salle(float x_ini, float y_ini, float x_fin, float y_fin, int numSalle, QString nomSalle, QString nomAtelier)
{
    this->id = 0;
    this->x_ini = x_ini;
    this->y_ini = y_ini;
    this->x_fin = x_fin;
    this->y_fin = y_fin;
    this->numSalle = numSalle;
    this->nomSalle = nomSalle;
    this->nomAtelier = nomAtelier;
}

Salle::~Salle()
{
}

long Salle::getId()
{
    return this->id;
}

float Salle::getX_ini()
{
    return this->x_ini;
}

float Salle::getY_ini()
{
    return this->y_ini;
}

float Salle::getX_fin()
{
    return this->x_fin;
}

float Salle::getY_fin()
{
    return this->y_fin;
}

int Salle::getNumSalle()
{
    return this->numSalle;
}

QString Salle::getNomSalle()
{
    return this->nomSalle;
}

QString Salle::getNomAtelier()
{
    return this->nomAtelier;
}

void Salle::setId(long id)
{
    this->id = id;
}

void Salle::setX_ini(float x_ini)
{
    this->x_ini = x_ini;
}

void Salle::setY_ini(float y_ini)
{
    this->y_ini = y_ini;
}

void Salle::setX_fin(float x_fin)
{
    this->x_fin = x_fin;
}

void Salle::setY_fin(float y_fin)
{
    this->y_fin = y_fin;
}

void Salle::setNumSalle(int numSalle)
{
    this->numSalle = numSalle;
}

void Salle::setNomSalle(QString nomSalle)
{
    this->nomSalle = nomSalle;
}

void Salle::setNomAtelier(QString nomAtelier)
{
    this->nomAtelier = nomAtelier;
}
