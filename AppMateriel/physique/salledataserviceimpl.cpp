#include "salledataserviceimpl.h"

Physique::SalleDataServiceImpl::SalleDataServiceImpl()
{
}

Salle Physique::SalleDataServiceImpl::add(Salle salle)
{
    Salle newSalle;
    query.prepare("INSERT INTO salle (x_ini, y_ini, x_fin, y_fin, numSalle, nomSalle, nomAtelier) VALUES (:x_ini, :y_ini, :x_max, :y_max, :numSalle, :nomSalle, :nomAtelier)");
    query.bindValue(":x_ini", salle.getX_ini());
    query.bindValue(":y_ini", salle.getY_ini());
    query.bindValue(":x_fin", salle.getX_fin());
    query.bindValue(":y_fin", salle.getY_fin());
    query.bindValue(":numSalle", salle.getNumSalle());
    query.bindValue(":nomSalle", salle.getNomSalle());
    query.bindValue(":nomAtelier", salle.getNomAtelier());
    if(query.exec()) {
        newSalle = getById(query.lastInsertId().toLongLong());
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return newSalle;
}

bool Physique::SalleDataServiceImpl::remove(Salle salle)
{
    bool execute;
    query.prepare("DELETE FROM attribution WHERE idSalle = :idSalle"); // On supprime d'abord l'attribution qui contient la salle puis la salle
    query.bindValue(":idSalle", (qlonglong)salle.getId());
    if(execute = query.exec()) {
        qWarning("Attribution supprimé\n");
        query.prepare("DELETE FROM salle WHERE id = :id");
        query.bindValue(":id", (qlonglong)salle.getId());
        if(!(execute = query.exec())) {
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::SalleDataServiceImpl::update(Salle salle)
{
    bool execute;
    query.prepare("UPDATE salle SET x_ini = :x_ini, y_ini = :y_ini, x_fin = :x_fin, y_fin = :y_fin, numSalle = :numSalle, nomSalle = :nomSalle, nomAtelier = :nomAtelier WHERE id = :id");
    query.bindValue(":id", (qlonglong)salle.getId());
    query.bindValue(":x_ini", salle.getX_ini());
    query.bindValue(":y_ini", salle.getY_ini());
    query.bindValue(":x_fin", salle.getX_fin());
    query.bindValue(":y_fin", salle.getY_fin());
    query.bindValue(":numSalle", salle.getNumSalle());
    query.bindValue(":nomSalle", salle.getNomSalle());
    query.bindValue(":nomAtelier", salle.getNomAtelier());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

QList<Salle> Physique::SalleDataServiceImpl::getAll(int debut, int parPage)
{
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM salle ORDER BY numSalle ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            salle = Salle(query.value(1).toFloat(), query.value(2).toFloat(), query.value(3).toFloat(), query.value(4).toFloat(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
            salle.setId(query.value(0).toLongLong());
            salles.append(salle);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return salles;
}

int Physique::SalleDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM salle");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Salle Physique::SalleDataServiceImpl::getById(long id)
{
    Salle salle;
    query.prepare("SELECT * FROM salle WHERE id = :id");
    query.bindValue(":id", (qlonglong)id);
    if(query.exec()) {
        if(query.next())
        {
            salle = Salle(query.value(1).toFloat(), query.value(2).toFloat(), query.value(3).toFloat(), query.value(4).toFloat(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
            salle.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return salle;
}

QList<Salle> Physique::SalleDataServiceImpl::getByNomSalle(QString nomSalle, int debut, int parPage)
{
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM salle WHERE nomSalle = :nomSalle ORDER BY numSalle ASC LIMIT :debut,:parPage");
    query.bindValue(":nomSalle", nomSalle);
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            salle = Salle(query.value(1).toFloat(), query.value(2).toFloat(), query.value(3).toFloat(), query.value(4).toFloat(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
            salle.setId(query.value(0).toLongLong());
            salles.append(salle);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return salles;
}

int Physique::SalleDataServiceImpl::getCountByNomSalle(QString nomSalle)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM salle WHERE nomSalle = :nomSalle");
    query.bindValue(":nomSalle", nomSalle);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
       qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<QString> Physique::SalleDataServiceImpl::getListNomSalle(int debut, int parPage)
{
    QList<QString> listNomSalle;
    query.prepare("SELECT DISTINCT nomSalle FROM salle WHERE nomSalle != '' ORDER BY nomSalle ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNomSalle.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNomSalle;
}

int Physique::SalleDataServiceImpl::getCountListNomSalle()
{
    int count = 0;
    query.prepare("SELECT COUNT(DISTINCT nomSalle) FROM salle WHERE nomSalle != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Salle Physique::SalleDataServiceImpl::getByNumSalle(int numSalle)
{
    Salle salle;
    query.prepare("SELECT * FROM salle WHERE numSalle = :numSalle");
    query.bindValue(":numSalle", numSalle);
    if(query.exec()) {
        if(query.next())
        {
            salle = Salle(query.value(1).toFloat(), query.value(2).toFloat(), query.value(3).toFloat(), query.value(4).toFloat(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
            salle.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return salle;
}

QList<int> Physique::SalleDataServiceImpl::getListNumSalle(int debut, int parPage)
{
    QList<int> listNumSalle;
    query.prepare("SELECT numSalle FROM salle ORDER BY numSalle ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNumSalle.append(query.value(0).toInt());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNumSalle;
}

int Physique::SalleDataServiceImpl::getCountListNumSalle()
{
    int count = 0;
    query.prepare("SELECT COUNT(numSalle) FROM salle");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Salle> Physique::SalleDataServiceImpl::getByNomAtelier(QString nomAtelier, int debut, int parPage)
{
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM salle WHERE nomAtelier = :nomAtelier ORDER BY nomAtelier ASC LIMIT :debut,:parPage");
    query.bindValue(":nomAtelier", nomAtelier);
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            salle = Salle(query.value(1).toFloat(), query.value(2).toFloat(), query.value(3).toFloat(), query.value(4).toFloat(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
            salle.setId(query.value(0).toLongLong());
            salles.append(salle);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return salles;
}

int Physique::SalleDataServiceImpl::getCountByNomAtelier(QString nomAtelier)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM salle WHERE nomAtelier = :nomAtelier");
    query.bindValue(":nomAtelier", nomAtelier);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<QString> Physique::SalleDataServiceImpl::getListNomAtelier(int debut, int parPage)
{
    QList<QString> listNomAtelier;
    query.prepare("SELECT DISTINCT nomAtelier FROM salle WHERE nomAtelier != '' LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNomAtelier.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNomAtelier;
}

int Physique::SalleDataServiceImpl::getCountListNomAtelier()
{
    int count = 0;
    query.prepare("SELECT COUNT(DISTINCT nomAtelier) FROM salle WHERE nomAtelier != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}
