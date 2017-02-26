#ifndef METROLOGUESERVICEIMPL_H
#define METROLOGUESERVICEIMPL_H
#include "physique/metrologuedataservice.h"
#include "metier/metrologueservice.h"
#include "physique/physiquefactory.h"

namespace Metier {
class MetrologueServiceImpl : public MetrologueService
{
public:
    MetrologueServiceImpl();
    virtual Metrologue add(Metrologue metrologue);
    virtual bool remove(Metrologue metrologue);
    virtual bool update(Metrologue metrologue);
    virtual QList<Metrologue> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Metrologue getById(long id);
    virtual Metrologue getByLogin(QString login);
    virtual QList<QString> getListLogin(int debut, int parPage);
    virtual int getCountListLogin();
private:
    Physique::MetrologueDataService* metrologueDataSrv;
};
}

#endif // METROLOGUESERVICEIMPL_H
