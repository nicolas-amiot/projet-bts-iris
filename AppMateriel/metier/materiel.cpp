#include "materiel.h"

Materiel::Materiel()
{
    this->id = 0;
    this->idBadge = QString();
    this->dateControle = QDate();
    this->newDateControle = QDate();
    this->nomMateriel = QString();
    this->type = Type();
}

Materiel::Materiel(QString idBadge, QDate dateControle, QDate newDateControle, QString nomMateriel, Type type)
{
    this->id = 0;
    this->idBadge = idBadge;
    this->dateControle = dateControle;
    this->newDateControle = newDateControle;
    this->nomMateriel = nomMateriel;
    this->type = type;
}

Materiel::~Materiel()
{
}

long Materiel::getId()
{
    return this->id;
}

QString Materiel::getIdBadge()
{
    return this->idBadge;
}

QDate Materiel::getDateControle()
{
    return this->dateControle;
}

QDate Materiel::getNewDateControle()
{
    return this->newDateControle;
}

QString Materiel::getNomMateriel()
{
    return this->nomMateriel;
}

Type Materiel::getType()
{
    return this->type;
}

void Materiel::setId(long id)
{
    this->id = id;
}

void Materiel::setDateControle(QDate dateControle)
{
    this->dateControle = dateControle;
}

void Materiel::setNewDateControle(QDate newDateControle)
{
    this->newDateControle = newDateControle;
}

void Materiel::setNomMateriel(QString nomMateriel)
{
    this->nomMateriel = nomMateriel;
}

void Materiel::setIdBadge(QString idBadge)
{
    this->idBadge = idBadge;
}

void Materiel::setType(Type type)
{
    this->type = type;
}
