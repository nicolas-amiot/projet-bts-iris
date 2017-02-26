#include "localisationdataserviceimpl.h"

Physique::LocalisationDataServiceImpl::LocalisationDataServiceImpl()
{
    salleDataSrv = PhysiqueFactory::getSalleDataServiceImpl();
    materielDataSrv = PhysiqueFactory::getMaterielDataServiceImpl();
    typeDataSrv = PhysiqueFactory::getTypeDataServiceImpl();
}

Localisation Physique::LocalisationDataServiceImpl::add(Localisation localisation)
{
    Localisation newLocalisation;
    query.prepare("INSERT INTO localisation (idMateriel, idSalle, sortie) VALUES (:idMateriel, :idSalle, :sortie)");
    query.bindValue(":idMateriel", (qlonglong)localisation.getMateriel().getId());
    query.bindValue(":idSalle", (qlonglong)localisation.getSalle().getId());
    query.bindValue(":sortie", localisation.getSortie());
    if(query.exec()) {
        newLocalisation = getById(query.lastInsertId().toLongLong());
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return newLocalisation;
}

bool Physique::LocalisationDataServiceImpl::remove(Localisation localisation)
{
    bool execute;
    query.prepare("DELETE FROM localisation WHERE id = :id");
    query.bindValue(":id", (qlonglong)localisation.getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::LocalisationDataServiceImpl::update(Localisation localisation)
{
    bool execute;
    query.prepare("UPDATE localisation SET idMateriel = :idMateriel, idSalle = :idSalle, sortie = :sortie WHERE id = :id");
    query.bindValue(":id", (qlonglong)localisation.getId());
    query.bindValue(":idMateriel", (qlonglong)localisation.getMateriel().getId());
    query.bindValue(":idSalle", (qlonglong)localisation.getSalle().getId());
    query.bindValue(":sortie", (qlonglong)localisation.getSortie());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

QList<Localisation> Physique::LocalisationDataServiceImpl::getAll(int debut, int parPage)
{
    QList<Localisation> localisations;
    Localisation localisation;
    query.prepare("SELECT * FROM localisation ORDER BY id ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            localisation = Localisation(materielDataSrv->getById(query.value(1).toLongLong()), salleDataSrv->getById(query.value(2).toLongLong()), query.value(3).toBool());
            localisation.setId(query.value(0).toLongLong());
            localisations.append(localisation);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return localisations;
}

int Physique::LocalisationDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM localisation");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Localisation Physique::LocalisationDataServiceImpl::getById(long id)
{
    Localisation localisation;
    query.prepare("SELECT * FROM localisation WHERE id = :id");
    query.bindValue(":id", (qlonglong)id);
    if(query.exec()) {
        if(query.next())
        {
            localisation = Localisation(materielDataSrv->getById(query.value(1).toLongLong()), salleDataSrv->getById(query.value(2).toLongLong()), query.value(3).toBool());
            localisation.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return localisation;
}

QList<Localisation> Physique::LocalisationDataServiceImpl::getBySalle(Salle salle, int debut, int parPage)
{
    QList<Localisation> localisations;
    Localisation localisation;
    query.prepare("SELECT * FROM localisation WHERE idSalle = :idSalle ORDER BY id ASC LIMIT :debut,:parPage");
    query.bindValue(":idSalle", (qlonglong)salle.getId());
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            localisation = Localisation(materielDataSrv->getById(query.value(1).toLongLong()), salleDataSrv->getById(query.value(2).toLongLong()), query.value(3).toBool());
            localisation.setId(query.value(0).toLongLong());
            localisations.append(localisation);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return localisations;
}

int Physique::LocalisationDataServiceImpl::getCountBySalle(Salle salle)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM localisation WHERE idSalle = :idSalle");
    query.bindValue(":idSalle", (qlonglong)salle.getId());
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Salle> Physique::LocalisationDataServiceImpl::getListSalle(int debut, int parPage)
{
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM salle WHERE id IN (SELECT DISTINCT idSalle FROM localisation) ORDER BY numSalle ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            salle = Salle(query.value(1).toFloat(), query.value(2).toFloat(), query.value(3).toFloat(), query.value(4).toFloat(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
            salle.setId(query.value(0).toLongLong());
            salles.append(salle);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return salles;
}

int Physique::LocalisationDataServiceImpl::getCountListSalle()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM salle WHERE id IN (SELECT DISTINCT idSalle FROM localisation)");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Localisation Physique::LocalisationDataServiceImpl::getByMateriel(Materiel materiel)
{
    Localisation localisation;
    query.prepare("SELECT * FROM localisation WHERE idMateriel = :idMateriel");
    query.bindValue(":idMateriel", (qlonglong)materiel.getId());
    if(query.exec()) {
        if(query.next())
        {
            localisation = Localisation(materielDataSrv->getById(query.value(1).toLongLong()), salleDataSrv->getById(query.value(2).toLongLong()), query.value(3).toBool());
            localisation.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return localisation;
}

QList<Materiel> Physique::LocalisationDataServiceImpl::getListMateriel(int debut, int parPage)
{
    QList<Materiel> materiels;
    Materiel materiel;
    query.prepare("SELECT * FROM materiel WHERE id IN (SELECT idMateriel FROM localisation) ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
            materiels.append(materiel);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiels;
}

int Physique::LocalisationDataServiceImpl::getCountListMateriel()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM materiel WHERE id IN (SELECT idMateriel FROM localisation)");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Localisation> Physique::LocalisationDataServiceImpl::getBySortie(bool sortie, int debut, int parPage)
{
    QList<Localisation> localisations;
    Localisation localisation;
    query.prepare("SELECT * FROM localisation WHERE sortie = :sortie ORDER BY id ASC LIMIT :debut,:parPage");
    query.bindValue(":sortie", sortie);
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            localisation = Localisation(materielDataSrv->getById(query.value(1).toLongLong()), salleDataSrv->getById(query.value(2).toLongLong()), query.value(3).toBool());
            localisation.setId(query.value(0).toLongLong());
            localisations.append(localisation);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return localisations;
}

int Physique::LocalisationDataServiceImpl::getCountBySortie(bool sortie)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM localisation WHERE sortie = :sortie");
    query.bindValue(":sortie", sortie);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}
