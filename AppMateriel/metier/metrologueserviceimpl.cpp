#include "metrologueserviceimpl.h"

Metier::MetrologueServiceImpl::MetrologueServiceImpl()
{
    metrologueDataSrv = PhysiqueFactory::getMetrologueDataServiceImpl();
}

Metrologue Metier::MetrologueServiceImpl::add(Metrologue metrologue)
{
    Metrologue met;
    if(!metrologue.getLogin().isEmpty() && !metrologue.getPassword().isEmpty()){
        met = metrologueDataSrv->add(metrologue);
    }
    return met;
}

bool Metier::MetrologueServiceImpl::remove(Metrologue metrologue)
{
    bool execute = false;
    if(metrologue.getId() > 0){
        execute = metrologueDataSrv->remove(metrologue);
    }
    return execute;
}

bool Metier::MetrologueServiceImpl::update(Metrologue metrologue)
{
    bool execute = false;
    if(metrologue.getId() > 0){
        if(!metrologue.getLogin().isEmpty() && !metrologue.getPassword().isEmpty()){
            execute = metrologueDataSrv->update(metrologue);
        }
    }
    return execute;
}

QList<Metrologue> Metier::MetrologueServiceImpl::getAll(int debut, int parPage)
{
    QList<Metrologue> met;
    if(debut >= 0 && parPage > 0){
        met = metrologueDataSrv->getAll(debut, parPage);
    }
    return met;
}

int Metier::MetrologueServiceImpl::getCount()
{
    return metrologueDataSrv->getCount();
}

Metrologue Metier::MetrologueServiceImpl::getById(long id)
{
    Metrologue met;
    if(id > 0){
        met = metrologueDataSrv->getById(id);
    }
    return met;
}

Metrologue Metier::MetrologueServiceImpl::getByLogin(QString login)
{
    Metrologue met;
    if(!login.isEmpty()){
        met = metrologueDataSrv->getByLogin(login);
    }
    return met;
}

QList<QString> Metier::MetrologueServiceImpl::getListLogin(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = metrologueDataSrv->getListLogin(debut, parPage);
    }
    return listStr;
}

int Metier::MetrologueServiceImpl::getCountListLogin()
{
    int count = metrologueDataSrv->getCountListLogin();
    return count;
}
