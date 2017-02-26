#include "lecteurrfiddataserviceimpl.h"

Physique::LecteurRFIDDataServiceImpl::LecteurRFIDDataServiceImpl()
{
}

LecteurRFID Physique::LecteurRFIDDataServiceImpl::add(LecteurRFID lecteur)
{
    LecteurRFID newLecteur;
    query.prepare("INSERT INTO lecteur (ip, modele, etatOn) VALUES (:ip, :modele, :etatOn)");
    query.bindValue(":ip", lecteur.getIp());
    query.bindValue(":modele", lecteur.getModele());
    query.bindValue(":etatOn", lecteur.getEtatOn());
    if(query.exec()) {
        newLecteur = getById(query.lastInsertId().toLongLong());
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return newLecteur;
}

bool Physique::LecteurRFIDDataServiceImpl::remove(LecteurRFID lecteur)
{
    bool execute;
    query.prepare("DELETE FROM lecteur WHERE id = :id");
    query.bindValue(":id", (qlonglong)lecteur.getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::LecteurRFIDDataServiceImpl::update(LecteurRFID lecteur)
{
    bool execute;
    query.prepare("UPDATE lecteur SET ip = :ip, modele = :modele, etatOn = :etatOn WHERE id = :id");
    query.bindValue(":id", (qlonglong)lecteur.getId());
    query.bindValue(":ip", lecteur.getIp());
    query.bindValue(":modele", lecteur.getModele());
    query.bindValue(":etatOn", lecteur.getEtatOn());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

QList<LecteurRFID> Physique::LecteurRFIDDataServiceImpl::getAll(int debut, int parPage)
{
    QList<LecteurRFID> lecteurs;
    LecteurRFID lecteur;
    query.prepare("SELECT * FROM lecteur ORDER BY ip ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            lecteur = LecteurRFID(query.value(1).toString(), query.value(2).toString(), query.value(3).toBool());
            lecteur.setId(query.value(0).toLongLong());
            lecteurs.append(lecteur);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return lecteurs;
}

int Physique::LecteurRFIDDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM lecteur");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

LecteurRFID Physique::LecteurRFIDDataServiceImpl::getById(long id)
{
    LecteurRFID lecteur;
    query.prepare("SELECT * FROM lecteur WHERE id = :id");
    query.bindValue(":id", (qlonglong)id);
    if(query.exec()) {
        if(query.next())
        {
            lecteur = LecteurRFID(query.value(1).toString(), query.value(2).toString(), query.value(3).toBool());
            lecteur.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return lecteur;
}

LecteurRFID Physique::LecteurRFIDDataServiceImpl::getByIp(QString ip)
{
    LecteurRFID lecteur;
    query.prepare("SELECT * FROM lecteur WHERE ip = :ip");
    query.bindValue(":ip", ip);
    if(query.exec()) {
        if(query.next())
        {
            lecteur = LecteurRFID(query.value(1).toString(), query.value(2).toString(), query.value(3).toBool());
            lecteur.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return lecteur;
}

QList<QString> Physique::LecteurRFIDDataServiceImpl::getListIp(int debut, int parPage)
{
    QList<QString> listIp;
    query.prepare("SELECT ip FROM lecteur WHERE ip != '' ORDER BY ip ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listIp.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listIp;
}

int Physique::LecteurRFIDDataServiceImpl::getCountListIp()
{
    int count = 0;
    query.prepare("SELECT COUNT(ip) FROM lecteur WHERE ip != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<LecteurRFID> Physique::LecteurRFIDDataServiceImpl::getByModele(QString modele, int debut, int parPage)
{
    QList<LecteurRFID> lecteurs;
    LecteurRFID lecteur;
    query.prepare("SELECT * FROM lecteur WHERE modele = :modele ORDER BY ip ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    query.bindValue(":modele", modele);
    if(query.exec()) {
        while(query.next())
        {
            lecteur = LecteurRFID(query.value(1).toString(), query.value(2).toString(), query.value(3).toBool());
            lecteur.setId(query.value(0).toLongLong());
            lecteurs.append(lecteur);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return lecteurs;
}

int Physique::LecteurRFIDDataServiceImpl::getCountByModele(QString modele)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM lecteur WHERE modele = :modele");
    query.bindValue(":modele", modele);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<QString> Physique::LecteurRFIDDataServiceImpl::getListModele(int debut, int parPage)
{
    QList<QString> listModele;
    query.prepare("SELECT DISTINCT modele FROM lecteur WHERE modele != '' ORDER BY modele ASC LIMIT :debut,:parPage"); // Distinc permet de ne pas prendre les valeurs en doublon
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listModele.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listModele;
}

int Physique::LecteurRFIDDataServiceImpl::getCountListModele()
{
    int count = 0;
    query.prepare("SELECT COUNT(DISTINCT modele) FROM lecteur WHERE modele != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<LecteurRFID> Physique::LecteurRFIDDataServiceImpl::getByEtatOn(bool etatOn, int debut, int parPage)
{
    QList<LecteurRFID> lecteurs;
    LecteurRFID lecteur;
    query.prepare("SELECT * FROM lecteur WHERE etatOn = :etatOn ORDER BY ip ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    query.bindValue(":etatOn", etatOn);
    if(query.exec()) {
        while(query.next())
        {
            lecteur = LecteurRFID(query.value(1).toString(), query.value(2).toString(), query.value(3).toBool());
            lecteur.setId(query.value(0).toLongLong());
            lecteurs.append(lecteur);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return lecteurs;
}

int Physique::LecteurRFIDDataServiceImpl::getCountByEtatOn(bool etatOn)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM lecteur WHERE etatOn = :etatOn");
    query.bindValue(":etatOn", etatOn);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}
