#ifndef BATIMENTSERVICEIMPL_H
#define BATIMENTSERVICEIMPL_H
#include "physique/batimentdataservice.h"
#include "metier/batimentservice.h"
#include "physique/physiquefactory.h"
#include "metier/localisationservice.h"

namespace Metier {
class BatimentServiceImpl : public BatimentService
{
public:
    BatimentServiceImpl();
    virtual Batiment add(Batiment batiment);
    virtual bool remove(Batiment batiment);
    virtual bool update(Batiment batiment);
    virtual QList<Batiment> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Batiment getById(long id);
    virtual Batiment getByNomBatiment(QString nomBatiment);
    virtual QList<QString> getListNomBatiment(int debut, int parPage);
    virtual int getCountListNomBatiment();
    virtual Batiment getBySalle(Salle salle);
    virtual QList<Salle> getListSalle(int debut, int parPage);
    virtual int getCountListSalle();
    virtual Batiment getByPlan(QString plan);
    virtual QList<QString> getListPlan(int debut, int parPage);
    virtual int getCountListPlan();
private:
    Physique::BatimentDataService* batimentDataSrv;
};
}

#endif // BATIMENTSERVICEIMPL_H
