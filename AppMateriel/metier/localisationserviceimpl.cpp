#include "localisationserviceimpl.h"

Metier::LocalisationServiceImpl::LocalisationServiceImpl()
{
    localisationDataSrv = PhysiqueFactory::getLocalisationDataServiceImpl();
}

Localisation Metier::LocalisationServiceImpl::add(Localisation localisation)
{
    Localisation loc;
    if(localisation.getMateriel().getId() > 0 && localisation.getSalle().getId() > 0){
        loc = localisationDataSrv->add(localisation);
    }
    return loc;
}

bool Metier::LocalisationServiceImpl::remove(Localisation localisation)
{
    bool execute = false;
    if(localisation.getId() > 0){
        execute = localisationDataSrv->remove(localisation);
    }
    return execute;
}

bool Metier::LocalisationServiceImpl::update(Localisation localisation)
{
    bool execute = false;
    if(localisation.getId() > 0){
        if(localisation.getMateriel().getId() > 0 && localisation.getSalle().getId() > 0){
            execute = localisationDataSrv->update(localisation);
        }
    }
    return execute;
}

QList<Localisation> Metier::LocalisationServiceImpl::getAll(int debut, int parPage)
{
    QList<Localisation> loc;
    if(debut >= 0 && parPage > 0){
        loc = localisationDataSrv->getAll(debut, parPage);
    }
    return loc;
}

int Metier::LocalisationServiceImpl::getCount()
{
    return localisationDataSrv->getCount();
}

Localisation Metier::LocalisationServiceImpl::getById(long id)
{
    Localisation loc;
    if(id > 0){
        loc = localisationDataSrv->getById(id);
    }
    return loc;
}

QList<Localisation> Metier::LocalisationServiceImpl::getBySalle(Salle salle, int debut, int parPage)
{
    QList<Localisation> loc;
    if(salle.getId() > 0){
        if(debut >= 0 && parPage > 0){
            loc = localisationDataSrv->getBySalle(salle, debut, parPage);
        }
    }
    return loc;
}

int Metier::LocalisationServiceImpl::getCountBySalle(Salle salle)
{
    int count = 0;
    if(salle.getId() > 0){
        count = localisationDataSrv->getCountBySalle(salle);
    }
    return count;
}

QList<Salle> Metier::LocalisationServiceImpl::getListSalle(int debut, int parPage)
{
    QList<Salle> salles;
    if(debut >= 0 && parPage > 0){
        salles = localisationDataSrv->getListSalle(debut, parPage);
    }
    return salles;
}

int Metier::LocalisationServiceImpl::getCountListSalle()
{
    int count = localisationDataSrv->getCountListSalle();
    return count;
}

Localisation Metier::LocalisationServiceImpl::getByMateriel(Materiel materiel)
{
    Localisation loc;
    if(materiel.getId() > 0){
        loc = localisationDataSrv->getByMateriel(materiel);
    }
    return loc;
}

QList<Materiel> Metier::LocalisationServiceImpl::getListMateriel(int debut, int parPage)
{
    QList<Materiel> materiels;
    if(debut >= 0 && parPage > 0){
        materiels = localisationDataSrv->getListMateriel(debut, parPage);
    }
    return materiels;
}

int Metier::LocalisationServiceImpl::getCountListMateriel()
{
    int count = localisationDataSrv->getCountListMateriel();
    return count;
}

QList<Localisation> Metier::LocalisationServiceImpl::getBySortie(bool sortie, int debut, int parPage)
{
    QList<Localisation> loc;
    loc = localisationDataSrv->getBySortie(sortie, debut, parPage);
    return loc;
}

int Metier::LocalisationServiceImpl::getCountBySortie(bool sortie)
{
    int count = 0;
    count = localisationDataSrv->getCountBySortie(sortie);
    return count;
}
