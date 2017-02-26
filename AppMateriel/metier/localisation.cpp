#include "localisation.h"

Localisation::Localisation()
{
    this->id = 0;
    this->materiel = Materiel();
    this->salle = Salle();
    this->sortie = false;
}

Localisation::Localisation(Materiel materiel, Salle salle, bool sortie)
{
    this->id = 0;
    this->materiel = materiel;
    this->salle = salle;
    this->sortie = sortie;
}

Localisation::~Localisation()
{
}

long Localisation::getId()
{
    return this->id;
}

Materiel Localisation::getMateriel()
{
    return this->materiel;
}

Salle Localisation::getSalle()
{
    return this->salle;
}

bool Localisation::getSortie()
{
    return this->sortie;
}

void Localisation::setId(long id)
{
    this->id = id;
}

void Localisation::setMateriel(Materiel materiel)
{
    this->materiel = materiel;
}

void Localisation::setSalle(Salle salle)
{
    this->salle = salle;
}

void Localisation::setSortie(bool sortie)
{
    this->sortie = sortie;
}
