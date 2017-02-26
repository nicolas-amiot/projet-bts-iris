#ifndef METIERFACTORY_H
#define METIERFACTORY_H
#include "metier/batimentserviceimpl.h"
#include "metier/localisationserviceimpl.h"
#include "metier/materielserviceimpl.h"
#include "metier/metrologueserviceimpl.h"
#include "metier/portiqueserviceimpl.h"
#include "metier/salleserviceimpl.h"
#include "metier/typeserviceimpl.h"
#include "metier/lecteurrfidserviceimpl.h"

class MetierFactory
{
private:
    static Metier::BatimentService* batimentSrv;
    static Metier::LocalisationService* localisationSrv;
    static Metier::MaterielService* materielSrv;
    static Metier::MetrologueService* metrologueSrv;
    static Metier::PortiqueService* portiqueSrv;
    static Metier::SalleService* salleSrv;
    static Metier::TypeService* typeSrv;
    static Metier::LecteurRFIDService* lecteurRFIDSrv;
public:
    static Metier::BatimentService* getBatimentServiceImpl();
    static Metier::LocalisationService* getLocalisationServiceImpl();
    static Metier::MaterielService* getMaterielServiceImpl();
    static Metier::MetrologueService* getMetrologueServiceImpl();
    static Metier::PortiqueService* getPortiqueServiceImpl();
    static Metier::SalleService* getSalleServiceImpl();
    static Metier::TypeService* getTypeServiceImpl();
    static Metier::LecteurRFIDService* getLecteurRFIDServiceImpl();
};

#endif // METIERFACTORY_H
