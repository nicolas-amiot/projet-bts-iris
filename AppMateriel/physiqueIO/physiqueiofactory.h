#ifndef PHYSIQUEIOFACTORY_H
#define PHYSIQUEIOFACTORY_H

#include "physiqueIO/lecteurrfidioserviceimpl.h"
#include "physiqueIO/lecteurrfidioservicetestimpl.h"

class PhysiqueIOFactory
{
private:
    static PhysiqueIO::LecteurRFIDIOService* lecteurRFIDIOSrv;
public:
    static PhysiqueIO::LecteurRFIDIOService* getLecteurRFIDIOServiceImpl();
};

#endif // PHYSIQUEIOFACTORY_H
