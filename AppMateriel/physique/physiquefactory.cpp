#include "physiquefactory.h"

Physique::BatimentDataService* PhysiqueFactory::batimentDataSrv = 0;
Physique::LocalisationDataService* PhysiqueFactory::localisationDataSrv = 0;
Physique::MaterielDataService* PhysiqueFactory::materielDataSrv = 0;
Physique::MetrologueDataService* PhysiqueFactory::metrologueDataSrv = 0;
Physique::PortiqueDataService* PhysiqueFactory::portiqueDataSrv = 0;
Physique::SalleDataService* PhysiqueFactory::salleDataSrv = 0;
Physique::TypeDataService* PhysiqueFactory::typeDataSrv = 0;
Physique::LecteurRFIDDataService* PhysiqueFactory::lecteurRFIDDataSrv = 0;

Physique::BatimentDataService* PhysiqueFactory::getBatimentDataServiceImpl(){
    if(batimentDataSrv == 0){
        batimentDataSrv = new Physique::BatimentDataServiceImpl();
    }
    return batimentDataSrv;
}

Physique::LocalisationDataService* PhysiqueFactory::getLocalisationDataServiceImpl(){
    if(localisationDataSrv == 0){
        localisationDataSrv = new Physique::LocalisationDataServiceImpl();
    }
    return localisationDataSrv;
}

Physique::MaterielDataService* PhysiqueFactory::getMaterielDataServiceImpl(){
    if(materielDataSrv == 0){
        materielDataSrv = new Physique::MaterielDataServiceImpl();
    }
    return materielDataSrv;
}

Physique::MetrologueDataService* PhysiqueFactory::getMetrologueDataServiceImpl(){
    if(metrologueDataSrv == 0){
        metrologueDataSrv = new Physique::MetrologueDataServiceImpl();
    }
    return metrologueDataSrv;
}

Physique::PortiqueDataService* PhysiqueFactory::getPortiqueDataServiceImpl(){
    if(portiqueDataSrv == 0){
        portiqueDataSrv = new Physique::PortiqueDataServiceImpl();
    }
    return portiqueDataSrv;
}

Physique::SalleDataService* PhysiqueFactory::getSalleDataServiceImpl(){
    if(salleDataSrv == 0){
        salleDataSrv = new Physique::SalleDataServiceImpl();
    }
    return salleDataSrv;
}

Physique::TypeDataService* PhysiqueFactory::getTypeDataServiceImpl(){
    if(typeDataSrv == 0){
        typeDataSrv = new Physique::TypeDataServiceImpl();
    }
    return typeDataSrv;
}

Physique::LecteurRFIDDataService *PhysiqueFactory::getLecteurRFIDDataServiceImpl()
{
    if(lecteurRFIDDataSrv == 0){
        lecteurRFIDDataSrv = new Physique::LecteurRFIDDataServiceImpl();
    }
    return lecteurRFIDDataSrv;
}
