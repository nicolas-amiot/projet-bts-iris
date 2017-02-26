#include "portiqueserviceimpl.h"

Metier::PortiqueServiceImpl::PortiqueServiceImpl()
{
    portiqueDataSrv = PhysiqueFactory::getPortiqueDataServiceImpl();
}

Portique Metier::PortiqueServiceImpl::add(Portique portique)
{
    Portique por;
    if(portique.getLecteurRFID().getId() > 0 && portique.getSalle1().getId() > 0 && portique.getSalle1().getId() != portique.getSalle2().getId() && portique.getX() >=0 && portique.getY() >= 0){
        por = portiqueDataSrv->add(portique);
    }
    return por;
}

bool Metier::PortiqueServiceImpl::remove(Portique portique)
{
    bool execute = false;
    if(portique.getId() > 0){
        execute = portiqueDataSrv->remove(portique);
    }
    return execute;
}

bool Metier::PortiqueServiceImpl::update(Portique portique)
{
    bool execute = false;
    if(portique.getId() > 0){
        if(portique.getLecteurRFID().getId() > 0 && portique.getSalle1().getId() > 0 && portique.getSalle1().getId() != portique.getSalle2().getId() && portique.getX() >=0 && portique.getY() >= 0){
            execute = portiqueDataSrv->update(portique);
        }
    }
    return execute;
}

QList<Portique> Metier::PortiqueServiceImpl::getAll(int debut, int parPage)
{
    QList<Portique> por;
    if(debut >= 0 && parPage > 0){
        por = portiqueDataSrv->getAll(debut, parPage);
    }
    return por;
}

int Metier::PortiqueServiceImpl::getCount()
{
    return portiqueDataSrv->getCount();
}

Portique Metier::PortiqueServiceImpl::getById(long id)
{
    Portique por;
    if(id > 0){
        por = portiqueDataSrv->getById(id);
    }
    return por;
}

Portique Metier::PortiqueServiceImpl::getByLecteurRFID(LecteurRFID lecteur)
{
    Portique por;
    if(lecteur.getId() > 0){
        por = portiqueDataSrv->getByLecteurRFID(lecteur);
    }
    return por;
}

QList<LecteurRFID> Metier::PortiqueServiceImpl::getListLecteurRFID(int debut, int parPage)
{
    QList<LecteurRFID> lecteurs;
    if(debut >= 0 && parPage > 0){
        lecteurs = portiqueDataSrv->getListLecteurRFID(debut, parPage);
    }
    return lecteurs;
}

int Metier::PortiqueServiceImpl::getCountListLecteurRFID()
{
    int count = portiqueDataSrv->getCountListLecteurRFID();
    return count;
}

QList<Portique> Metier::PortiqueServiceImpl::getBySalle(Salle salle, int debut, int parPage)
{
    QList<Portique> por;
    if(salle.getId() > 0){
        if(debut >= 0 && parPage > 0){
            por = portiqueDataSrv->getBySalle(salle, debut, parPage);
        }
    }
    return por;
}

int Metier::PortiqueServiceImpl::getCountBySalle(Salle salle)
{
    int count =0;
    if(salle.getId() > 0){
        count = portiqueDataSrv->getCountBySalle(salle);
    }
    return count;
}

QList<Salle> Metier::PortiqueServiceImpl::getListSalle(int debut, int parPage)
{
    QList<Salle> salles;
    if(debut >= 0 && parPage > 0){
        salles = portiqueDataSrv->getListSalle(debut, parPage);
    }
    return salles;
}

int Metier::PortiqueServiceImpl::getCountListSalle()
{
    int count = portiqueDataSrv->getCountListSalle();
    return count;
}
