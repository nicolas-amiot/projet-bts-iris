#include "salleserviceimpl.h"

Metier::SalleServiceImpl::SalleServiceImpl()
{
    salleDataSrv = PhysiqueFactory::getSalleDataServiceImpl();
    localisationSrv = MetierFactory::getLocalisationServiceImpl();
    portiqueSrv = MetierFactory::getPortiqueServiceImpl();
}

Salle Metier::SalleServiceImpl::add(Salle salle)
{
    Salle sal;
    if(salle.getNumSalle() > 0 && salle.getX_fin() >= 0 && salle.getX_ini() >= 0 && salle.getY_fin() >= 0 && salle.getY_ini() >= 0){
        sal = salleDataSrv->add(salle);
    }
    return sal;
}

bool Metier::SalleServiceImpl::remove(Salle salle)
{
    bool execute = false;
    if(salle.getId() > 0){
        QList<Localisation> localisations = localisationSrv->getBySalle(salle, 0, localisationSrv->getCountBySalle(salle));
        foreach (Localisation localisation, localisations) {
            localisationSrv->remove(localisation);
        }
        QList<Portique> portiques = portiqueSrv->getBySalle(salle, 0, portiqueSrv->getCountBySalle(salle));
        foreach (Portique portique, portiques) {
            if(portique.getSalle1().getId() > 0 && portique.getSalle2().getId() <= 0){
                portiqueSrv->remove(portique);
            } else { // Le portique contient 2 salles
                if(salle.getId() == portique.getSalle1().getId()){
                    portique.setSalle1(portique.getSalle2());
                    portique.setSalle2(Salle());
                   portiqueSrv->update(portique);
                }
            }
        }
        execute = salleDataSrv->remove(salle);
    }
    return execute;
}

bool Metier::SalleServiceImpl::update(Salle salle)
{
    bool execute = false;
    if(salle.getId() > 0){
        if(salle.getNumSalle() > 0 && salle.getX_fin() >= 0 && salle.getX_ini() >= 0 && salle.getY_fin() >= 0 && salle.getY_ini() >= 0){
            execute = salleDataSrv->update(salle);
        }
    }
    return execute;
}

QList<Salle> Metier::SalleServiceImpl::getAll(int debut, int parPage)
{
    QList<Salle> sal;
    if(debut >= 0 && parPage > 0){
        sal = salleDataSrv->getAll(debut, parPage);
    }
    return sal;
}

int Metier::SalleServiceImpl::getCount()
{
    return salleDataSrv->getCount();
}

Salle Metier::SalleServiceImpl::getById(long id)
{
    Salle sal;
    if(id > 0){
        sal = salleDataSrv->getById(id);
    }
    return sal;
}

QList<Salle> Metier::SalleServiceImpl::getByNomSalle(QString nomSalle, int debut, int parPage)
{
    QList<Salle> sal;
    if(!nomSalle.isEmpty()){
        if(debut >= 0 && parPage > 0){
            sal = salleDataSrv->getByNomSalle(nomSalle, debut, parPage);
        }
    }
    return sal;
}

int Metier::SalleServiceImpl::getCountByNomSalle(QString nomSalle)
{
    int count = 0;
    if(!nomSalle.isEmpty()){
        count = salleDataSrv->getCountByNomSalle(nomSalle);
    }
    return count;
}

QList<QString> Metier::SalleServiceImpl::getListNomSalle(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = salleDataSrv->getListNomSalle(debut, parPage);
    }
    return listStr;
}

int Metier::SalleServiceImpl::getCountListNomSalle()
{
    int count = salleDataSrv->getCountListNomSalle();
    return count;
}

Salle Metier::SalleServiceImpl::getByNumSalle(int numSalle)
{
    Salle sal;
    if(numSalle > 0){
        sal = salleDataSrv->getByNumSalle(numSalle);
    }
    return sal;
}

QList<int> Metier::SalleServiceImpl::getListNumSalle(int debut, int parPage)
{
    QList<int> listNumSalle;
    if(debut >= 0 && parPage > 0){
        listNumSalle = salleDataSrv->getListNumSalle(debut, parPage);
    }
    return listNumSalle;
}

int Metier::SalleServiceImpl::getCountListNumSalle()
{
    int count = salleDataSrv->getCountListNumSalle();
    return count;
}

QList<Salle> Metier::SalleServiceImpl::getByNomAtelier(QString nomAtelier, int debut, int parPage)
{
    QList<Salle> sal;
    if(!nomAtelier.isEmpty()){
        if(debut >= 0 && parPage > 0){
            sal = salleDataSrv->getByNomAtelier(nomAtelier, debut, parPage);
        }
    }
    return sal;
}

int Metier::SalleServiceImpl::getCountByNomAtelier(QString nomAtelier)
{
    int count = 0;
    if(!nomAtelier.isEmpty()){
        count = salleDataSrv->getCountByNomAtelier(nomAtelier);
    }
    return count;
}

QList<QString> Metier::SalleServiceImpl::getListNomAtelier(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = salleDataSrv->getListNomAtelier(debut, parPage);
    }
    return listStr;
}

int Metier::SalleServiceImpl::getCountListNomAtelier()
{
    int count = salleDataSrv->getCountListNomAtelier();
    return count;
}
