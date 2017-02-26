#include "materielserviceimpl.h"

Metier::MaterielServiceImpl::MaterielServiceImpl()
{
    materielDataSrv = PhysiqueFactory::getMaterielDataServiceImpl();
    localisationSrv = MetierFactory::getLocalisationServiceImpl();
}

Materiel Metier::MaterielServiceImpl::add(Materiel materiel)
{
    Materiel mat;
    if(!materiel.getIdBadge().isEmpty() && !materiel.getNomMateriel().isEmpty() && materiel.getDateControle().isValid() && materiel.getNewDateControle().isValid() && materiel.getType().getId() > 0){
        mat = materielDataSrv->add(materiel);
    }
    return mat;
}

bool Metier::MaterielServiceImpl::remove(Materiel materiel)
{
    bool execute = false;
    if(materiel.getId() > 0){
        Localisation localisation = localisationSrv->getByMateriel(materiel);
        if(localisation.getId() > 0){
            localisationSrv->remove(localisation);
        }
        execute = materielDataSrv->remove(materiel);
    }
    return execute;
}

bool Metier::MaterielServiceImpl::update(Materiel materiel)
{
    bool execute = false;
    if(materiel.getId() > 0){
        if(!materiel.getIdBadge().isEmpty() && !materiel.getNomMateriel().isEmpty() && materiel.getDateControle().isValid() && materiel.getNewDateControle().isValid() && materiel.getType().getId() > 0){
            execute = materielDataSrv->update(materiel);
        }
    }
    return execute;
}

QList<Materiel> Metier::MaterielServiceImpl::getAll(int debut, int parPage)
{
    QList<Materiel> mat;
    if(debut >= 0 && parPage > 0){
        mat = materielDataSrv->getAll(debut, parPage);
    }
    return mat;
}

int Metier::MaterielServiceImpl::getCount()
{
    return materielDataSrv->getCount();
}

Materiel Metier::MaterielServiceImpl::getById(long id)
{
    Materiel mat;
    if(id > 0){
        mat = materielDataSrv->getById(id);
    }
    return mat;
}

Materiel Metier::MaterielServiceImpl::getByIdBadge(QString idBadge)
{
    Materiel mat;
    if(!idBadge.isEmpty()){
        mat = materielDataSrv->getByIdBadge(idBadge);
    }
    return mat;
}

QList<QString> Metier::MaterielServiceImpl::getListIdBadge(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = materielDataSrv->getListIdBadge(debut, parPage);
    }
    return listStr;
}

int Metier::MaterielServiceImpl::getCountListIdBadge()
{
    int count = materielDataSrv->getCountListIdBadge();
    return count;
}

QList<Materiel> Metier::MaterielServiceImpl::getByDateControle(QDate dateControle, int debut, int parPage)
{
    QList<Materiel> mat;
    if(dateControle.isValid()){
        if(debut >= 0 && parPage > 0){
            mat = materielDataSrv->getByDateControle(dateControle, debut, parPage);
        }
    }
    return mat;
}

int Metier::MaterielServiceImpl::getCountByDateControle(QDate dateControle)
{
    int count = 0;
    if(dateControle.isValid()){
        count = materielDataSrv->getCountByDateControle(dateControle);
    }
    return count;
}

QList<QDate> Metier::MaterielServiceImpl::getListDateControle(int debut, int parPage)
{
    QList<QDate> listDate;
    if(debut >= 0 && parPage > 0){
        listDate = materielDataSrv->getListDateControle(debut, parPage);
    }
    return listDate;
}

int Metier::MaterielServiceImpl::getCountListDateControle()
{
    int count = materielDataSrv->getCountListDateControle();
    return count;
}

QList<Materiel> Metier::MaterielServiceImpl::getByNewDateControle(QDate newDateControle, int debut, int parPage)
{
    QList<Materiel> mat;
    if(newDateControle.isValid()){
        if(debut >= 0 && parPage > 0){
            mat = materielDataSrv->getByNewDateControle(newDateControle, debut, parPage);
        }
    }
    return mat;
}

int Metier::MaterielServiceImpl::getCountByNewDateControle(QDate newDateControle)
{
    int count = 0;
    if(newDateControle.isValid()){
        count = materielDataSrv->getCountByNewDateControle(newDateControle);
    }
    return count;
}

QList<QDate> Metier::MaterielServiceImpl::getListNewDateControle(int debut, int parPage)
{
    QList<QDate> listNewDate;
    if(debut >= 0 && parPage > 0){
        listNewDate = materielDataSrv->getListNewDateControle(debut, parPage);
    }
    return listNewDate;
}

int Metier::MaterielServiceImpl::getCountListNewDateControle()
{
    int count = materielDataSrv->getCountListNewDateControle();
    return count;
}

QList<Materiel> Metier::MaterielServiceImpl::getByPeriode(QDate date, bool avant, int debut, int parPage)
{
    QList<Materiel> mat;
    if(date.isValid()){
        if(debut >= 0 && parPage > 0){
            mat = materielDataSrv->getByPeriode(date, avant, debut, parPage);
        }
    }
    return mat;
}

int Metier::MaterielServiceImpl::getCountByPeriode(QDate date, bool avant)
{
    int count = 0;
    if(date.isValid()){
        count = materielDataSrv->getCountByPeriode(date, avant);
    }
    return count;
}

QList<Materiel> Metier::MaterielServiceImpl::getByType(Type type, int debut, int parPage)
{
    QList<Materiel> mat;
    if(type.getId() > 0){
        if(debut >= 0 && parPage > 0){
            mat = materielDataSrv->getByType(type, debut, parPage);
        }
    }
    return mat;
}

int Metier::MaterielServiceImpl::getCountByType(Type type)
{
    int count = 0;
    if(type.getId() > 0){
        count = materielDataSrv->getCountByType(type);
    }
    return count;
}

QList<Type> Metier::MaterielServiceImpl::getListType(int debut, int parPage)
{
    QList<Type> types;
    if(debut >= 0 && parPage > 0){
        types = materielDataSrv->getListType(debut, parPage);
    }
    return types;
}

int Metier::MaterielServiceImpl::getCountListType()
{
    int count = materielDataSrv->getCountListType();
    return count;
}

QList<Materiel> Metier::MaterielServiceImpl::getByNomMateriel(QString nomMateriel, int debut, int parPage)
{
    QList<Materiel> mat;
    if(!nomMateriel.isEmpty()){
        if(debut >= 0 && parPage > 0){
            mat = materielDataSrv->getByNomMateriel(nomMateriel, debut, parPage);
        }
    }
    return mat;
}

int Metier::MaterielServiceImpl::getCountByNomMateriel(QString nomMateriel)
{
    int count = 0;
    if(!nomMateriel.isEmpty()){
        count = materielDataSrv->getCountByNomMateriel(nomMateriel);
    }
    return count;
}

QList<QString> Metier::MaterielServiceImpl::getListNomMateriel(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = materielDataSrv->getListNomMateriel(debut, parPage);
    }
    return listStr;
}

int Metier::MaterielServiceImpl::getCountListNomMateriel()
{
    int count = materielDataSrv->getCountListNomMateriel();
    return count;
}
