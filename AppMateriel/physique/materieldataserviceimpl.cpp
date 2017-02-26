#include "materieldataserviceimpl.h"

Physique::MaterielDataServiceImpl::MaterielDataServiceImpl()
{
    typeDataSrv = PhysiqueFactory::getTypeDataServiceImpl();
}

Materiel Physique::MaterielDataServiceImpl::add(Materiel materiel)
{
    Materiel newMateriel;
    query.prepare("INSERT INTO materiel (idBadge, dateControle, newDateControle, nomMateriel, idType) VALUES (:idBadge, :dateControle, :newDateControle, :nomMateriel, :idType)");
    query.bindValue(":idBadge", materiel.getIdBadge());
    query.bindValue(":dateControle", materiel.getDateControle());
    query.bindValue(":newDateControle", materiel.getNewDateControle());
    query.bindValue(":nomMateriel", materiel.getNomMateriel());
    query.bindValue(":idType", (qlonglong)materiel.getType().getId());
    if(query.exec()) {
        newMateriel = getById(query.lastInsertId().toLongLong());
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return newMateriel;
}

bool Physique::MaterielDataServiceImpl::remove(Materiel materiel)
{
    bool execute;
    query.prepare("DELETE FROM materiel WHERE id = :id");
    query.bindValue(":id", (qlonglong)materiel.getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::MaterielDataServiceImpl::update(Materiel materiel)
{
    bool execute;
    query.prepare("UPDATE materiel SET idBadge = :idBadge, dateControle = :dateControle, newDateControle = :newDateControle, nomMateriel = :nomMateriel, idType = :idType WHERE id = :id");
    query.bindValue(":id", (qlonglong)materiel.getId());
    query.bindValue(":idBadge", materiel.getIdBadge());
    query.bindValue(":dateControle", materiel.getDateControle());
    query.bindValue(":newDateControle", materiel.getNewDateControle());
    query.bindValue(":nomMateriel", materiel.getNomMateriel());
    query.bindValue(":idType", (qlonglong)materiel.getType().getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

QList<Materiel> Physique::MaterielDataServiceImpl::getAll(int debut, int parPage)
{
    QList<Materiel> materiels;
    Materiel materiel;
    query.prepare("SELECT * FROM materiel ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
            materiels.append(materiel);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiels;
}

int Physique::MaterielDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM materiel");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Materiel Physique::MaterielDataServiceImpl::getById(long id)
{
    Materiel materiel;
    query.prepare("SELECT * FROM materiel WHERE id = :id");
    query.bindValue(":id", (qlonglong)id);
    if(query.exec()) {
        if(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiel;
}

Materiel Physique::MaterielDataServiceImpl::getByIdBadge(QString idBadge)
{
    Materiel materiel;
    query.prepare("SELECT * FROM materiel WHERE idBadge = :idBadge");
    query.bindValue(":idBadge", idBadge);
    if(query.exec()) {
        if(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiel;
}

QList<QString> Physique::MaterielDataServiceImpl::getListIdBadge(int debut, int parPage)
{
    QList<QString> listIdBadge;
    query.prepare("SELECT idBadge FROM materiel WHERE idBadge != '' ORDER BY idBadge ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listIdBadge.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listIdBadge;
}

int Physique::MaterielDataServiceImpl::getCountListIdBadge()
{
    int count = 0;
    query.prepare("SELECT COUNT(idBadge) FROM materiel WHERE idBadge != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Materiel> Physique::MaterielDataServiceImpl::getByDateControle(QDate dateControle, int debut, int parPage)
{
    QList<Materiel> materiels;
    Materiel materiel;
    query.prepare("SELECT * FROM materiel WHERE dateControle = :dateControle ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":dateControle", dateControle);
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
            materiels.append(materiel);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiels;
}

int Physique::MaterielDataServiceImpl::getCountByDateControle(QDate dateControle)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM materiel WHERE dateControle = :dateControle");
    query.bindValue(":dateControle", dateControle);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<QDate> Physique::MaterielDataServiceImpl::getListDateControle(int debut, int parPage)
{
    QList<QDate> listDateControle;
    query.prepare("SELECT DISTINCT dateControle FROM materiel WHERE dateControle != 0 ORDER BY dateControle ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listDateControle.append(query.value(0).toDate());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listDateControle;
}

int Physique::MaterielDataServiceImpl::getCountListDateControle()
{
    int count = 0;
    query.prepare("SELECT COUNT(DISTINCT dateControle) FROM materiel WHERE dateControle != 0");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Materiel> Physique::MaterielDataServiceImpl::getByNewDateControle(QDate newDateControle, int debut, int parPage)
{
    QList<Materiel> materiels;
    Materiel materiel;
    query.prepare("SELECT * FROM materiel WHERE newDateControle = :newDateControle ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":newDateControle", newDateControle);
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
            materiels.append(materiel);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiels;
}

int Physique::MaterielDataServiceImpl::getCountByNewDateControle(QDate newDateControle)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM materiel WHERE newDateControle = :newDateControle");
    query.bindValue(":newDateControle", newDateControle);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<QDate> Physique::MaterielDataServiceImpl::getListNewDateControle(int debut, int parPage)
{
    QList<QDate> listNewDateControle;
    query.prepare("SELECT DISTINCT newDateControle FROM materiel WHERE newDateControle != 0 ORDER BY newDateControle ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNewDateControle.append(query.value(0).toDate());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNewDateControle;
}

int Physique::MaterielDataServiceImpl::getCountListNewDateControle()
{
    int count = 0;
    query.prepare("SELECT COUNT(DISTINCT newDateControle) FROM materiel WHERE newDateControle != 0");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Materiel> Physique::MaterielDataServiceImpl::getByPeriode(QDate date, bool avant, int debut, int parPage)
{
    QList<Materiel> materiels;
    Materiel materiel;
    QString operateur;
    if(avant){
        operateur = "<=";
    }else{
        operateur = ">=";
    }
    query.prepare("SELECT * FROM materiel WHERE newDateControle "+ operateur +" :newDateControle ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":newDateControle", date);
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
            materiels.append(materiel);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiels;
}

int Physique::MaterielDataServiceImpl::getCountByPeriode(QDate date, bool avant)
{
    int count = 0;
    QString operateur;
    if(avant){
        operateur = "<=";
    }else{
        operateur = ">=";
    }
    query.prepare("SELECT COUNT(*) FROM materiel WHERE newDateControle "+ operateur +" :newDateControle");
    query.bindValue(":newDateControle", date);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Materiel> Physique::MaterielDataServiceImpl::getByType(Type type, int debut, int parPage)
{
    QList<Materiel> materiels;
    Materiel materiel;
    query.prepare("SELECT * FROM materiel WHERE idType = :idType ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":idType", (qlonglong)type.getId());
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
            materiels.append(materiel);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiels;
}

int Physique::MaterielDataServiceImpl::getCountByType(Type type)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM materiel WHERE idType = :idType");
    query.bindValue(":idType", (qlonglong)type.getId());
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Type> Physique::MaterielDataServiceImpl::getListType(int debut, int parPage)
{
    QList<Type> types;
    Type type;
    query.prepare("SELECT * FROM type WHERE id IN (SELECT DISTINCT idType FROM materiel) ORDER BY nomType ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            type = Type(query.value(1).toString(), query.value(2).toString());
            type.setId(query.value(0).toLongLong());
            types.append(type);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return types;
}

int Physique::MaterielDataServiceImpl::getCountListType()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM type WHERE id IN (SELECT DISTINCT idType FROM materiel)");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<Materiel> Physique::MaterielDataServiceImpl::getByNomMateriel(QString nomMateriel, int debut, int parPage)
{
    QList<Materiel> materiels;
    Materiel materiel;
    query.prepare("SELECT * FROM materiel WHERE nomMateriel = :nomMateriel ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":nomMateriel", nomMateriel);
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            materiel = Materiel(query.value(1).toString(), query.value(2).toDate(), query.value(3).toDate(), query.value(4).toString(), typeDataSrv->getById(query.value(5).toLongLong()));
            materiel.setId(query.value(0).toLongLong());
            materiels.append(materiel);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return materiels;
}

int Physique::MaterielDataServiceImpl::getCountByNomMateriel(QString nomMateriel)
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM materiel WHERE nomMateriel = :nomMateriel");
    query.bindValue(":nomMateriel", nomMateriel);
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

QList<QString> Physique::MaterielDataServiceImpl::getListNomMateriel(int debut, int parPage)
{
    QList<QString> listNomMateriel;
    query.prepare("SELECT DISTINCT nomMateriel FROM materiel WHERE nomMateriel != '' ORDER BY nomMateriel ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNomMateriel.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNomMateriel;
}

int Physique::MaterielDataServiceImpl::getCountListNomMateriel()
{
    int count = 0;
    query.prepare("SELECT COUNT(DISTINCT nomMateriel) FROM materiel WHERE nomMateriel != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}
