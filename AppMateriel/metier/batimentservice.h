#ifndef BATIMENTSERVICE_H
#define BATIMENTSERVICE_H
#include "metier/batiment.h"

namespace Metier {
class BatimentService
{
public:
    virtual Batiment add(Batiment batiment) = 0;
    virtual bool remove(Batiment batiment) = 0;
    virtual bool update(Batiment batiment) = 0;
    virtual QList<Batiment> getAll(int debut, int parPage) = 0;
    virtual int getCount() = 0;
    virtual Batiment getById(long id) = 0;
    virtual Batiment getByNomBatiment(QString nomBatiment) = 0;
    virtual QList<QString> getListNomBatiment(int debut, int parPage) = 0;
    virtual int getCountListNomBatiment() = 0;
    virtual Batiment getBySalle(Salle salle) = 0;
    virtual QList<Salle> getListSalle(int debut, int parPage) = 0;
    virtual int getCountListSalle() = 0;
    virtual Batiment getByPlan(QString plan) = 0;
    virtual QList<QString> getListPlan(int debut, int parPage) = 0;
    virtual int getCountListPlan() = 0;
};
}

#endif // BATIMENTSERVICE_H
