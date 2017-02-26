#include "metierfactory.h"

Metier::BatimentService* MetierFactory::batimentSrv = 0;
Metier::LocalisationService* MetierFactory::localisationSrv = 0;
Metier::MaterielService* MetierFactory::materielSrv = 0;
Metier::MetrologueService* MetierFactory::metrologueSrv = 0;
Metier::PortiqueService* MetierFactory::portiqueSrv = 0;
Metier::SalleService* MetierFactory::salleSrv = 0;
Metier::TypeService* MetierFactory::typeSrv = 0;
Metier::LecteurRFIDService* MetierFactory::lecteurRFIDSrv = 0;

Metier::BatimentService* MetierFactory::getBatimentServiceImpl(){
    if(batimentSrv == 0){
        batimentSrv = new Metier::BatimentServiceImpl();
    }
    return batimentSrv;
}

Metier::LocalisationService* MetierFactory::getLocalisationServiceImpl(){
    if(localisationSrv == 0){
        localisationSrv = new Metier::LocalisationServiceImpl();
    }
    return localisationSrv;
}

Metier::MaterielService* MetierFactory::getMaterielServiceImpl(){
    if(materielSrv == 0){
        materielSrv = new Metier::MaterielServiceImpl();
    }
    return materielSrv;
}

Metier::MetrologueService* MetierFactory::getMetrologueServiceImpl(){
    if(metrologueSrv == 0){
        metrologueSrv = new Metier::MetrologueServiceImpl();
    }
    return metrologueSrv;
}

Metier::PortiqueService* MetierFactory::getPortiqueServiceImpl(){
    if(portiqueSrv == 0){
        portiqueSrv = new Metier::PortiqueServiceImpl();
    }
    return portiqueSrv;
}

Metier::SalleService* MetierFactory::getSalleServiceImpl(){
    if(salleSrv == 0){
        salleSrv = new Metier::SalleServiceImpl();
    }
    return salleSrv;
}

Metier::TypeService* MetierFactory::getTypeServiceImpl(){
    if(typeSrv == 0){
        typeSrv = new Metier::TypeServiceImpl();
    }
    return typeSrv;
}

Metier::LecteurRFIDService *MetierFactory::getLecteurRFIDServiceImpl()
{
    if(lecteurRFIDSrv == 0){
        lecteurRFIDSrv = new Metier::LecteurRFIDServiceImpl();
    }
    return lecteurRFIDSrv;
}
