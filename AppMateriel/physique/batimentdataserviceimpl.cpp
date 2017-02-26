#include "batimentdataserviceimpl.h"

Physique::BatimentDataServiceImpl::BatimentDataServiceImpl()
{
}

Batiment Physique::BatimentDataServiceImpl::add(Batiment batiment)
{
    Batiment newBatiment;
    long id = 0;
    QList<long> idSallesNonAttribue;
    bool execute;
    query.prepare("INSERT INTO batiment (nomBatiment, plan) VALUES (:nomBatiment, :plan)"); // Requête préparée, les paramètres sont représenté comme ceci: :param
    query.bindValue(":nomBatiment", batiment.getNomBatiment()); // Ajoute les valeurs
    query.bindValue(":plan", batiment.getPlan());
    if(execute = query.exec()) { // Si la requête s'est éxécuté, on réccupère le dernier id inséré dans la bdd
        id = query.lastInsertId().toLongLong(); // Les résultats retournés sont des QVariant, type très puissant permettant de stocker n'importe quel type de variable
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    if(execute){
        query.prepare("SELECT id FROM salle WHERE id NOT IN (SELECT idSalle FROM attribution)"); // séléctionne tous les id des salles qui n'ont pas été attribués à un batiment
        if(query.exec()) {
            while(query.next()){
                idSallesNonAttribue.append(query.value(0).toLongLong());
            }
        }else{
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
        query.prepare("INSERT INTO attribution (id, idBatiment, idSalle) VALUES ('', :idBatiment, :idSalle)");
        foreach(Salle salle, batiment.getSalles()){ // Pour chaque salle du batiment
            if(idSallesNonAttribue.contains(salle.getId())){ // si l'id n'est pas attribué, on l'ajoute au batiment
                query.bindValue(":idBatiment", (qlonglong)id);
                query.bindValue(":idSalle", (qlonglong)salle.getId());
                if(!query.exec()) {
                    qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
                }
            }else{
                qWarning("Salle déjà attribuée");
            }
        }
    }
    if(id != 0){ // Si un id a été créé par la bdd, on réccupère le batiment
        newBatiment = getById(id);
    }
    return newBatiment;
}

bool Physique::BatimentDataServiceImpl::remove(Batiment batiment)
{
    bool execute;
    query.prepare("DELETE FROM attribution WHERE idBatiment = :idBatiment"); // Supprime d'abord les attributions qui contient le batiment puis le batiment
    query.bindValue(":idBatiment", (qlonglong)batiment.getId());
    if(execute = query.exec()) {
        qWarning("Attributions supprimées\n");
        query.prepare("DELETE FROM batiment WHERE id = :id");
        query.bindValue(":id", (qlonglong)batiment.getId());
        if(!(execute = query.exec())) {
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::BatimentDataServiceImpl::update(Batiment batiment)
{
    QList<long> idSallesBatiment;
    QList<long> idSallesNonAttribue;
    bool execute;
    query.prepare("UPDATE batiment SET nomBatiment = :nomBatiment, plan = :plan WHERE id = :id");
    query.bindValue(":id", (qlonglong)batiment.getId());
    query.bindValue(":nomBatiment", batiment.getNomBatiment());
    query.bindValue(":plan", batiment.getPlan());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    if(execute){
        query.prepare("SELECT idSalle FROM attribution WHERE idBatiment = :idBatiment"); // séléctionne tous les id des salles qui ont été attribués à notre batiment
        query.bindValue(":idBatiment", (qlonglong)batiment.getId());
        if(query.exec()) {
            while(query.next()){
                idSallesBatiment.append(query.value(0).toLongLong());
            }
        }else{
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
        query.prepare("SELECT id FROM salle WHERE id NOT IN (SELECT idSalle FROM attribution)"); // séléctionne tous les id des salles qui n'ont pas été attribués à un batiment
        if(query.exec()) {
            while(query.next()){
                idSallesNonAttribue.append(query.value(0).toLongLong());
            }
        }else{
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
        query.prepare("INSERT INTO attribution (id, idBatiment, idSalle) VALUES ('', :idBatiment, :idSalle)");
        foreach(Salle salle, batiment.getSalles()){
            if(idSallesNonAttribue.contains(salle.getId())){ // Si la salle n'est pas attribué, on l'ajoute
                query.bindValue(":idBatiment", (qlonglong)batiment.getId());
                query.bindValue(":idSalle", (qlonglong)salle.getId());
                if(!query.exec()) {
                    qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
                }
            }else{ // Sinon la salle est déjà attribué, mais l'est-elle à notre batiment?
                if(idSallesBatiment.contains(salle.getId())){
                    idSallesBatiment.removeOne(salle.getId()); // Si oui on la supprime de la liste des anciennes salle attribué à notre batiment
                }else{
                    qWarning("Salle déjà attribuée à un autre batiment\n");
                }
            }
        }
        query.prepare("DELETE FROM attribution WHERE idSalle = :idSalle");
        foreach(long idSalleBatiment, idSallesBatiment){ // Toutes les salles présente dans la liste des anciennes salle attribué à notre batiment ne le sont plus, on les supprime donc
            query.bindValue(":idSalle", (qlonglong)idSalleBatiment);
            if(!query.exec()) {
                qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
            }
        }
    }
    return execute;
}

QList<Batiment> Physique::BatimentDataServiceImpl::getAll(int debut, int parPage)
{
    bool execute;
    QList<Batiment> batiments_temp;
    QList<Batiment> batiments;
    Batiment batiment_temp;
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM batiment ORDER BY nomBatiment ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(execute = query.exec()) {
        while(query.next()) // Réccupère les infos excepté les salles puisque les infos se trouve dans la table attribution
        {
            batiment_temp = Batiment();
            batiment_temp.setId(query.value(0).toLongLong());
            batiment_temp.setNomBatiment(query.value(1).toString());
            batiment_temp.setPlan(query.value(2).toString());
            batiments_temp.append(batiment_temp);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    if(execute){
        query.prepare("SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution WHERE idBatiment = :idBatiment) ORDER BY numSalle"); // on séléctionne tous les id des salles qui sont attribués au batiment et on les ajoutes
        foreach(Batiment batiment, batiments_temp){
            query.bindValue(":idBatiment", (qlonglong)batiment.getId());
            if(query.exec()) {
                while(query.next())
                {
                    salle = Salle(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
                    salle.setId(query.value(0).toLongLong());
                    salles.append(salle);
                }
                batiment.setSalles(salles);
                batiments.append(batiment);
            }else{
                qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
            }
            salles.clear(); // A chaque batiment, on vide la liste de salle
        }
    }
    return batiments;
}

int Physique::BatimentDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM batiment"); // Réccupère le nombre total de batiment
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Batiment Physique::BatimentDataServiceImpl::getById(long id)
{
    bool execute;
    Batiment batiment;
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM batiment WHERE id = :id"); // Recherche par attribut
    query.bindValue(":id", (qlonglong)id);
    if(execute = query.exec()) {
        if(query.next())
        {
            batiment = Batiment();
            batiment.setId(query.value(0).toLongLong());
            batiment.setNomBatiment(query.value(1).toString());
            batiment.setPlan(query.value(2).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    if(execute){
        query.prepare("SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution WHERE idBatiment = :idBatiment) ORDER BY numSalle");
        query.bindValue(":idBatiment", (qlonglong)batiment.getId());
        if(query.exec()) {
            while(query.next())
            {
                salle = Salle(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
                salle.setId(query.value(0).toLongLong());
                salles.append(salle);
            }
            batiment.setSalles(salles);
        }else{
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
    }
    return batiment;
}

Batiment Physique::BatimentDataServiceImpl::getByNomBatiment(QString nomBatiment)
{
    bool execute;
    Batiment batiment;
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM batiment WHERE nomBatiment = :nomBatiment");
    query.bindValue(":nomBatiment", nomBatiment);
    if(execute = query.exec()) {
        if(query.next())
        {
            batiment = Batiment();
            batiment.setId(query.value(0).toLongLong());
            batiment.setNomBatiment(query.value(1).toString());
            batiment.setPlan(query.value(2).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    if(execute){
        query.prepare("SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution WHERE idBatiment = :idBatiment) ORDER BY numSalle");
        query.bindValue(":idBatiment", (qlonglong)batiment.getId());
        if(query.exec()) {
            while(query.next())
            {
                salle = Salle(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
                salle.setId(query.value(0).toLongLong());
                salles.append(salle);
            }
            batiment.setSalles(salles);
        }else{
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
    }
    return batiment;
}

QList<QString> Physique::BatimentDataServiceImpl::getListNomBatiment(int debut, int parPage)
{
    QList<QString> listNomBatiment;
    query.prepare("SELECT nomBatiment FROM batiment WHERE nombatiment != '' ORDER BY nomBatiment ASC LIMIT :debut,:parPage"); // Réccupère toutes les valeurs non vide enregistrées dans la bdd correspondant à la collone nomBatiment
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNomBatiment.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNomBatiment;
}

int Physique::BatimentDataServiceImpl::getCountListNomBatiment()
{
    int count = 0;
    query.prepare("SELECT COUNT(nomBatiment) FROM batiment WHERE nombatiment != ''"); // Réccupère le nombre de données non vide de la collone nomBatiment enregistré dans la bdd
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Batiment Physique::BatimentDataServiceImpl::getBySalle(Salle salle)
{
    bool execute;
    QList<Salle> salles;
    Salle salle_temp;
    Batiment batiment;
    query.prepare("SELECT * FROM batiment WHERE id IN (SELECT idBatiment FROM attribution WHERE idSalle = :idSalle)");
    query.bindValue(":idSalle", (qlonglong)salle.getId());
    if(execute = query.exec()) {
        if(query.next())
        {
            batiment = Batiment();
            batiment.setId(query.value(0).toLongLong());
            batiment.setNomBatiment(query.value(1).toString());
            batiment.setPlan(query.value(2).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    if(execute){
        query.prepare("SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution WHERE idBatiment = :idBatiment) ORDER BY numSalle");
        query.bindValue(":idBatiment", (qlonglong)batiment.getId());
        if(query.exec()) {
            while(query.next())
            {
                salle_temp = Salle(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
                salle_temp.setId(query.value(0).toLongLong());
                salles.append(salle_temp);
            }
            batiment.setSalles(salles);
        }else{
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
    }
    return batiment;
}

QList<Salle> Physique::BatimentDataServiceImpl::getListSalle(int debut, int parPage)
{
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution) ORDER BY numSalle ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            salle = Salle(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
            salle.setId(query.value(0).toLongLong());
            salles.append(salle);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return salles;
}

int Physique::BatimentDataServiceImpl::getCountListSalle()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM salle WHERE id IN (SELECT idSalle FROM attribution)");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Batiment Physique::BatimentDataServiceImpl::getByPlan(QString plan)
{
    bool execute;
    Batiment batiment;
    QList<Salle> salles;
    Salle salle;
    query.prepare("SELECT * FROM batiment WHERE plan = :plan");
    query.bindValue(":plan", plan);
    if(execute = query.exec()) {
        if(query.next())
        {
            batiment = Batiment();
            batiment.setId(query.value(0).toLongLong());
            batiment.setNomBatiment(query.value(1).toString());
            batiment.setPlan(query.value(2).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    if(execute){
        query.prepare("SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution WHERE idBatiment = :idBatiment) ORDER BY numSalle");
        query.bindValue(":idBatiment", (qlonglong)batiment.getId());
        if(query.exec()) {
            while(query.next())
            {
                salle = Salle(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toString(), query.value(7).toString());
                salle.setId(query.value(0).toLongLong());
                salles.append(salle);
            }
            batiment.setSalles(salles);
        }else{
            qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
        }
    }
    return batiment;
}

QList<QString> Physique::BatimentDataServiceImpl::getListPlan(int debut, int parPage)
{
    QList<QString> listPlan;
    query.prepare("SELECT plan FROM batiment WHERE plan != '' ORDER BY plan ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listPlan.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listPlan;
}

int Physique::BatimentDataServiceImpl::getCountListPlan()
{
    int count = 0;
    query.prepare("SELECT COUNT(plan) FROM batiment WHERE plan != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}
