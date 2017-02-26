#ifndef PHYSIQUEFACTORY_H
#define PHYSIQUEFACTORY_H
#include "physique/batimentdataserviceimpl.h"
#include "physique/localisationdataserviceimpl.h"
#include "physique/materieldataserviceimpl.h"
#include "physique/metrologuedataserviceimpl.h"
#include "physique/portiquedataserviceimpl.h"
#include "physique/salledataserviceimpl.h"
#include "physique/typedataserviceimpl.h"
#include "physique/lecteurrfiddataserviceimpl.h"

class PhysiqueFactory
{
private:
    static Physique::BatimentDataService* batimentDataSrv;
    static Physique::LocalisationDataService* localisationDataSrv;
    static Physique::MaterielDataService* materielDataSrv;
    static Physique::MetrologueDataService* metrologueDataSrv;
    static Physique::PortiqueDataService* portiqueDataSrv;
    static Physique::SalleDataService* salleDataSrv;
    static Physique::TypeDataService* typeDataSrv;
    static Physique::LecteurRFIDDataService* lecteurRFIDDataSrv;
public:
    static Physique::BatimentDataService* getBatimentDataServiceImpl();
    static Physique::LocalisationDataService* getLocalisationDataServiceImpl();
    static Physique::MaterielDataService* getMaterielDataServiceImpl();
    static Physique::MetrologueDataService* getMetrologueDataServiceImpl();
    static Physique::PortiqueDataService* getPortiqueDataServiceImpl();
    static Physique::SalleDataService* getSalleDataServiceImpl();
    static Physique::TypeDataService* getTypeDataServiceImpl();
    static Physique::LecteurRFIDDataService* getLecteurRFIDDataServiceImpl();
};

#endif // PHYSIQUEFACTORY_H
