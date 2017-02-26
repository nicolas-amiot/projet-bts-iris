#include "lecteurrfidserviceimpl.h"

Metier::LecteurRFIDServiceImpl::LecteurRFIDServiceImpl()
{
    lecteurRFIDDataSrv = PhysiqueFactory::getLecteurRFIDDataServiceImpl();
    portiqueSrv = MetierFactory::getPortiqueServiceImpl();
}

LecteurRFID Metier::LecteurRFIDServiceImpl::add(LecteurRFID lecteur)
{
    LecteurRFID lec;
    if(!lecteur.getIp().isEmpty() && !lecteur.getModele().isEmpty()){
        lec = lecteurRFIDDataSrv->add(lecteur);
    }
    return lec;
}

bool Metier::LecteurRFIDServiceImpl::remove(LecteurRFID lecteur)
{
    bool execute = false;
    if(lecteur.getId() > 0){
        Portique portique = portiqueSrv->getByLecteurRFID(lecteur);
        if(portique.getId() > 0){
            portiqueSrv->remove(portique);
        }
        execute = lecteurRFIDDataSrv->remove(lecteur);
    }
    return execute;
}

bool Metier::LecteurRFIDServiceImpl::update(LecteurRFID lecteur)
{
    bool execute = false;
    if(lecteur.getId() > 0){
        if(!lecteur.getIp().isEmpty() && !lecteur.getModele().isEmpty()){
            execute = lecteurRFIDDataSrv->update(lecteur);
        }
    }
    return execute;
}

QList<LecteurRFID> Metier::LecteurRFIDServiceImpl::getAll(int debut, int parPage)
{
    QList<LecteurRFID> lec;
    if(debut >= 0 && parPage > 0){
        lec = lecteurRFIDDataSrv->getAll(debut, parPage);
    }
    return lec;
}

int Metier::LecteurRFIDServiceImpl::getCount()
{
    return lecteurRFIDDataSrv->getCount();
}

LecteurRFID Metier::LecteurRFIDServiceImpl::getById(long id)
{
    LecteurRFID lec;
    if(id > 0){
        lec = lecteurRFIDDataSrv->getById(id);
    }
    return lec;
}

LecteurRFID Metier::LecteurRFIDServiceImpl::getByIp(QString ip)
{
    LecteurRFID lec;
    if(!ip.isEmpty()){
        lec = lecteurRFIDDataSrv->getByIp(ip);
    }
    return lec;
}

QList<QString> Metier::LecteurRFIDServiceImpl::getListIp(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = lecteurRFIDDataSrv->getListIp(debut, parPage);
    }
    return listStr;
}

int Metier::LecteurRFIDServiceImpl::getCountListIp()
{
    int count = lecteurRFIDDataSrv->getCountListIp();
    return count;
}

QList<LecteurRFID> Metier::LecteurRFIDServiceImpl::getByModele(QString modele, int debut, int parPage)
{
    QList<LecteurRFID> lec;
    if(!modele.isEmpty()){
        if(debut >= 0 && parPage > 0){
            lec = lecteurRFIDDataSrv->getByModele(modele, debut, parPage);
        }
    }
    return lec;
}

int Metier::LecteurRFIDServiceImpl::getCountByModele(QString modele)
{
    int count = 0;
    if(!modele.isEmpty()){
        count = lecteurRFIDDataSrv->getCountByModele(modele);
    }
    return count;
}

QList<QString> Metier::LecteurRFIDServiceImpl::getListModele(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = lecteurRFIDDataSrv->getListModele(debut, parPage);
    }
    return listStr;
}

int Metier::LecteurRFIDServiceImpl::getCountListModele()
{
    int count = lecteurRFIDDataSrv->getCountListModele();
    return count;
}

QList<LecteurRFID> Metier::LecteurRFIDServiceImpl::getByEtatOn(bool etatOn, int debut, int parPage)
{
    QList<LecteurRFID> lec;
    if(debut >= 0 && parPage > 0){
        lec = lecteurRFIDDataSrv->getByEtatOn(etatOn, debut, parPage);
    }
    return lec;
}

int Metier::LecteurRFIDServiceImpl::getCountByEtatOn(bool etatOn)
{
    int count = lecteurRFIDDataSrv->getCountByEtatOn(etatOn);
    return count;
}
