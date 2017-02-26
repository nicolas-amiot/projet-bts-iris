#include "batimentserviceimpl.h"

Metier::BatimentServiceImpl::BatimentServiceImpl()
{
    batimentDataSrv = PhysiqueFactory::getBatimentDataServiceImpl();
}

Batiment Metier::BatimentServiceImpl::add(Batiment batiment)
{
    Batiment bat;
    if(!batiment.getNomBatiment().isEmpty() && !batiment.getPlan().isEmpty()){
        bat = batimentDataSrv->add(batiment);
    }
    return bat;
}

bool Metier::BatimentServiceImpl::remove(Batiment batiment)
{
    bool execute = false;
    if(batiment.getId() > 0){
        execute = batimentDataSrv->remove(batiment);
    }
    return execute;
}

bool Metier::BatimentServiceImpl::update(Batiment batiment)
{
    bool execute = false;
    if(batiment.getId() > 0){
        if(!batiment.getNomBatiment().isEmpty() && !batiment.getPlan().isEmpty()){
            execute = batimentDataSrv->update(batiment);
        }
    }
    return execute;
}

QList<Batiment> Metier::BatimentServiceImpl::getAll(int debut, int parPage)
{
    QList<Batiment> bat;
    if(debut >= 0 && parPage > 0){
        bat = batimentDataSrv->getAll(debut, parPage);
    }
    return bat;
}

int Metier::BatimentServiceImpl::getCount()
{
    return batimentDataSrv->getCount();
}

Batiment Metier::BatimentServiceImpl::getById(long id)
{
    Batiment bat;
    if(id > 0){
        bat = batimentDataSrv->getById(id);
    }
    return bat;
}

Batiment Metier::BatimentServiceImpl::getByNomBatiment(QString nomBatiment)
{
    Batiment bat;
    if(!nomBatiment.isEmpty()){
        bat = batimentDataSrv->getByNomBatiment(nomBatiment);
    }
    return bat;
}

QList<QString> Metier::BatimentServiceImpl::getListNomBatiment(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = batimentDataSrv->getListNomBatiment(debut, parPage);
    }
    return listStr;
}

int Metier::BatimentServiceImpl::getCountListNomBatiment()
{
    int count = batimentDataSrv->getCountListNomBatiment();
    return count;
}

Batiment Metier::BatimentServiceImpl::getBySalle(Salle salle)
{
    Batiment bat;
    if(salle.getId() > 0){
        bat = batimentDataSrv->getBySalle(salle);
    }
    return bat;
}

QList<Salle> Metier::BatimentServiceImpl::getListSalle(int debut, int parPage)
{
    QList<Salle> salles;
    if(debut >= 0 && parPage > 0){
        salles = batimentDataSrv->getListSalle(debut, parPage);
    }
    return salles;
}

int Metier::BatimentServiceImpl::getCountListSalle()
{
    int count = batimentDataSrv->getCountListSalle();
    return count;
}

Batiment Metier::BatimentServiceImpl::getByPlan(QString plan)
{
    Batiment bat;
    if(!plan.isEmpty()){
        bat = batimentDataSrv->getByPlan(plan);
    }
    return bat;
}

QList<QString> Metier::BatimentServiceImpl::getListPlan(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = batimentDataSrv->getListPlan(debut, parPage);
    }
    return listStr;
}

int Metier::BatimentServiceImpl::getCountListPlan()
{
    int count = batimentDataSrv->getCountListPlan();
    return count;
}
