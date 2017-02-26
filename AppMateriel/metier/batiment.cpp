#include "batiment.h"

Batiment::Batiment()
{
    this->id = 0;
    this->nomBatiment = QString();
    this->salles = QList<Salle>();
    this->plan = QString();
}

Batiment::Batiment(QString nomBatiment, QList<Salle> salles, QString plan)
{
    this->id = 0;
    this->nomBatiment = nomBatiment;
    this->salles = salles;
    this->plan = plan;
}

Batiment::~Batiment()
{
}


long Batiment::getId()
{
    return this->id;
}

QString Batiment::getNomBatiment()
{
    return this->nomBatiment;
}

QList<Salle> Batiment::getSalles()
{
    return this->salles;
}

QString Batiment::getPlan()
{
    return this->plan;
}

void Batiment::setId(long id)
{
    this->id = id;
}

void Batiment::setNomBatiment(QString nomBatiment)
{
    this->nomBatiment = nomBatiment;
}

void Batiment::setSalles(QList<Salle> salles)
{
    this->salles = salles;
}

void Batiment::setPlan(QString plan)
{
    this->plan = plan;
}
