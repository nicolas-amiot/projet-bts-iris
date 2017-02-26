#ifndef METROLOGUEDATASERVICEIMPL_H
#define METROLOGUEDATASERVICEIMPL_H
#include "physique/metrologuedataservice.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

namespace Physique {
class MetrologueDataServiceImpl : public MetrologueDataService
{
public:
    MetrologueDataServiceImpl();
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
    QSqlQuery query;
};
}

#endif // METROLOGUEDATASERVICEIMPL_H
