#include "lecteurrfidioservicetestimpl.h"

PhysiqueIO::LecteurRFIDIOServiceTestImpl::LecteurRFIDIOServiceTestImpl()
{
    QDate dateControle = QDate::fromString("12/03/2015", "dd/MM/yyyy");
    QDate newDateControle = QDate::fromString("12/04/2015", "dd/MM/yyyy");
    Type type1 = Type("voltmetre", "voltmetre.png");
    type1.setId(1);
    Type type2 = Type("amperemetre", "amperemetre.jpg");
    type2.setId(2);
    Materiel materiel = Materiel("ZERZR1312", dateControle, newDateControle, "mat 1", type1);
    materiel.setId(1);
    materiels.append(materiel);
    dateControle = QDate::fromString("11/07/2014", "dd/MM/yyyy");;
    newDateControle = QDate::fromString("11/07/2015", "dd/MM/yyyy");
    materiel = Materiel("E1E21112", dateControle, newDateControle, "mat 2", type2);
    materiel.setId(2);
    materiels.append(materiel);
    dateControle = QDate::fromString("27/02/2015", "dd/MM/yyyy");;
    newDateControle = QDate::fromString("27/03/2015", "dd/MM/yyyy");
    materiel = Materiel("ZR82R2ZE", dateControle, newDateControle, "mat 3", type1);
    materiel.setId(3);
    materiels.append(materiel);
    materiel = Materiel();
    materiels.append(materiel);
    qsrand(time(NULL));
}


PhysiqueIO::LecteurRFIDIOServiceTestImpl::~LecteurRFIDIOServiceTestImpl()
{
}

Materiel PhysiqueIO::LecteurRFIDIOServiceTestImpl::lireBadge()
{
    int nb = qrand()%materiels.length();
    Materiel materiel = materiels.value(nb);
    if(materiel.getIdBadge().isEmpty()){
        qWarning("Test: Echec de la lecture du badge\n");
    }
    if(materiel.getIdBadge() == materiels.value(2).getIdBadge()){
        qWarning("Test: L'écriture sur ce badge avec %s va échouer en cas d'écriture\n", materiel.getIdBadge().toLatin1().data());
    }
    return materiel;
}

bool PhysiqueIO::LecteurRFIDIOServiceTestImpl::ecrireBadge(Materiel materiel)
{
    if(materiel.getIdBadge() == materiels.value(2).getIdBadge()){
        qWarning("Test: Echec de l'écriture du badge\n");
        return false;
    }else{
        return true;
    }
}
