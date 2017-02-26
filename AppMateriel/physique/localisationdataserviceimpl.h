#ifndef LOCALISATIONDATASERVICEIMPL_H
#define LOCALISATIONDATASERVICEIMPL_H
#include "physique/localisationdataservice.h"
#include "metier/metierfactory.h"
#include "physique/materieldataservice.h"
#include "physique/salledataservice.h"
#include "physique/typedataservice.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

namespace Physique {
class LocalisationDataServiceImpl : public LocalisationDataService
{
public:
    LocalisationDataServiceImpl();
    virtual Localisation add(Localisation localisation);
    virtual bool remove(Localisation localisation);
    virtual bool update(Localisation localisation);
    virtual QList<Localisation> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Localisation getById(long id);
    virtual QList<Localisation> getBySalle(Salle salle, int debut, int parPage);
    virtual int getCountBySalle(Salle salle);
    virtual QList<Salle> getListSalle(int debut, int parPage);
    virtual int getCountListSalle();
    virtual Localisation getByMateriel(Materiel materiel);
    virtual QList<Materiel> getListMateriel(int debut, int parPage);
    virtual int getCountListMateriel();
    virtual QList<Localisation> getBySortie(bool sortie, int debut, int parPage);
    virtual int getCountBySortie(bool sortie);
private:
    QSqlQuery query;
    Physique::SalleDataService* salleDataSrv;
    Physique::MaterielDataService* materielDataSrv;
    Physique::TypeDataService* typeDataSrv;
};
}

#endif // LOCALISATIONDATASERVICEIMPL_H
