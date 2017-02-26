#ifndef LOCALISATION_H
#define LOCALISATION_H
#include <QList>
#include "salle.h"
#include "materiel.h"


class Localisation
{
private:
    long id;
    Materiel materiel;
    Salle salle;
    bool sortie;
public:
    Localisation();
    Localisation(Materiel materiel, Salle salle, bool sortie);
    ~Localisation();

    long getId(void);
    Materiel getMateriel(void);
    Salle getSalle(void);
    bool getSortie(void);

    void setId(long id);
    void setMateriel(Materiel materiel);
    void setSalle(Salle salle);
    void setSortie(bool sortie);
};


#endif // LOCALISATION_H
