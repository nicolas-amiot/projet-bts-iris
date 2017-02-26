#include "portiquedataserviceimpl.h"

Physique::PortiqueDataServiceImpl::PortiqueDataServiceImpl()
{
    salleDataSrv = PhysiqueFactory::getSalleDataServiceImpl();
    lecteurDataSrv = PhysiqueFactory::getLecteurRFIDDataServiceImpl();
}


Portique Physique::PortiqueDataServiceImpl::add(Portique portique)
{
    Portique newPortique;
    query.prepare("INSERT INTO portique (x, y, idSalle1, idSalle2, idLecteur) VALUES (:x, :y, :idSalle1, :idSalle2, :idLecteur)");
    query.bindValue(":x", portique.getX());
    query.bindValue(":y", portique.getY());
    query.bindValue(":idSalle1", (qlonglong)portique.getSalle1().getId());
    if(portique.getSalle2().getId() > 0){
        query.bindValue(":idSalle2", (qlonglong)portique.getSalle2().getId());
    }else{
        query.bindValue(":idSalle2", QVariant::LongLong); // Permet de mettre null
    }
    query.bindValue(":idLecteur", (qlonglong)portique.getLecteurRFID().getId());
    if(query.exec()) {
        newPortique = getById(query.lastInsertId().toLongLong());
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return newPortique;
}

bool Physique::PortiqueDataServiceImpl::remove(Portique portique)
{
    bool execute;
    query.prepare("DELETE FROM portique WHERE id = :id");
    query.bindValue(":id", (qlonglong)portique.getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::PortiqueDataServiceImpl::update(Portique portique)
{
    bool execute;
    query.prepare("UPDATE portique SET x = :x, y = :y, idSalle1 = :idSalle1, idSalle2 = :idSalle2, idLecteur = :idLecteur WHERE id = :id");
    query.bindValue(":id", (qlonglong)portique.getId());
    query.bindValue(":x", portique.getX());
    query.bindValue(":y", portique.getY());
    query.bindValue(":idSalle1", (qlonglong)portique.getSalle1().getId());
    if(portique.getSalle2().getId() > 0){
        query.bindValue(":idSalle2", (qlonglong)portique.getSalle2().getId());
    }else{
        query.bindValue(":idSalle2", QVariant::LongLong); // Permet de mettre null
    }
    query.bindValue(":idLecteur", (qlonglong)portique.getLecteurRFID().getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

QList<Portique> Physique::PortiqueDataServiceImpl::getAll(int debut, int parPage)
{
    QList<Portique> portiques;
    Portique portique;
    query.prepare("SELECT * FROM portique ORDER BY id ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            portique = Portique(query.value(1).toFloat(), query.value(2).toFloat(), salleDataSrv->getById(query.value(3).toLongLong()), salleDataSrv->getById(query.value(4).toLongLong()), lecteurDataSrv->getById(query.value(5).toLongLong()));
            portique.setId(query.value(0).toLongLong());
            portiques.append(portique);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return portiques;
}

int Physique::PortiqueDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM portique");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Portique Physique::PortiqueDataServiceImpl::getById(long id)
{
    Portique portique;
    query.prepare("SELECT * FROM portique WHERE id = :id");
    query.bindValue(":id", (qlonglong)id);
    if(query.exec()) {
        if(query.next())
        {
            portique = Portique(query.value(1).toFloat(), query.value(2).toFloat(), salleDataSrv->getById(query.value(3).toLongLong()), salleDataSrv->getById(query.value(4).toLongLong()), lecteurDataSrv->getById(query.value(5).toLongLong()));
            portique.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return portique;
}

Portique Physique::PortiqueDataServiceImpl::getByLecteurRFID(LecteurRFID lecteur)
{
    Portique portique;
    query.prepare("SELECT * FROM portique WHERE idLecteur = :idLecteur");
    query.bindValue(":idLecteur", (qlonglong)lecteur.getId());
    if(query.exec()) {
        if(query.next())
        {
            portique = Portique(query.value(1).toFloat(), query.value(2).toFloat(), salleDataSrv->getById(query.value(3).toLongLong()), salleDataSrv->getById(query.value(4).toLongLong()), lecteurDataSrv->getById(query.value(5).toLongLong()));
            portique.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return portique;
}

QList<LecteurRFID> Physique::PortiqueDataServiceImpl::getListLecteurRFID(int debut, int parPage)
{
    QList<LecteurRFID> lecteurs;
    LecteurRFID lecteur;
    query.prepare("SELECT * FROM lecteur WHERE id IN (SELECT idLecteur FROM portique) ORDER BY ip ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            lecteur = LecteurRFID(query.value(1).toString(), query.value(2).toString(), query.value(3).toBool());
            lecteur.setId(query.value(0).toLongLong());
            lecteurs.append(lecteur);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return lecteurs;
}

int Physique::PortiqueDataServiceImpl::getCountListLecteurRFID()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM lecteur WHERE id IN (SELECT idLecteur FROM portique)");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Portique> Physique::PortiqueDataServiceImpl::getBySalle(Salle salle, int debut, int parPage)
{
    QList<Portique> portiques;
    Portique portique;
    query.prepare("SELECT * FROM portique WHERE idSalle1 = :idSalle1 OR idSalle2 = :idSalle2 ORDER BY id ASC LIMIT :debut,:parPage"); // Réccupère une liste de portique qui contient l'id de la salle soit dans la collone idSalle1 soit dans la collone idSalle2
    query.bindValue(":idSalle1", (qlonglong)salle.getId());
    query.bindValue(":idSalle2", (qlonglong)salle.getId());
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            portique = Portique(query.value(1).toFloat(), query.value(2).toFloat(), salleDataSrv->getById(query.value(3).toLongLong()), salleDataSrv->getById(query.value(4).toLongLong()), lecteurDataSrv->getById(query.value(5).toLongLong()));
            portique.setId(query.value(0).toLongLong());
            portiques.append(portique);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return portiques;
}

int Physique::PortiqueDataServiceImpl::getCountBySalle(Salle salle)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM portique WHERE idSalle1 = :idSalle1 OR idSalle2 = :idSalle2");
    query.bindValue(":idSalle1", (qlonglong)salle.getId());
    query.bindValue(":idSalle2", (qlonglong)salle.getId());
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Salle> Physique::PortiqueDataServiceImpl::getListSalle(int debut, int parPage)
{
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM salle WHERE id IN (SELECT DISTINCT idSalle1 FROM portique UNION SELECT idSalle2 FROM portique) ORDER BY numSalle ASC LIMIT :debut,:parPage"); // Réccupère toutes les salles où un portique est présent en vérifiant sur les 2 collones qu'aucune salle est déjà présente dans la liste
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

int Physique::PortiqueDataServiceImpl::getCountListSalle()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM salle WHERE id IN (SELECT DISTINCT idSalle1 FROM portique UNION SELECT idSalle2 FROM portique)");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

