#ifndef LOCALISATIONSERVICE_H
#define LOCALISATIONSERVICE_H
#include "metier/localisation.h"

namespace Metier {
class LocalisationService
{
public:
    virtual Localisation add(Localisation localisation) = 0;
    virtual bool remove(Localisation localisation) = 0;
    virtual bool update(Localisation localisation) = 0;
    virtual QList<Localisation> getAll(int debut, int parPage) = 0;
    virtual int getCount() = 0;
    virtual Localisation getById(long id) = 0;
    virtual QList<Localisation> getBySalle(Salle salle, int debut, int parPage) = 0;
    virtual int getCountBySalle(Salle salle) = 0;
    virtual QList<Salle> getListSalle(int debut, int parPage) = 0;
    virtual int getCountListSalle() = 0;
    virtual Localisation getByMateriel(Materiel materiel) = 0;
    virtual QList<Materiel> getListMateriel(int debut, int parPage) = 0;
    virtual int getCountListMateriel() = 0;
    virtual QList<Localisation> getBySortie(bool sortie, int debut, int parPage) = 0;
    virtual int getCountBySortie(bool sortie) = 0;
};
}

#endif // LOCALISATIONSERVICE_H
