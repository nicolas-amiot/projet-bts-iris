#include "physiqueiofactory.h"

PhysiqueIO::LecteurRFIDIOService* PhysiqueIOFactory::lecteurRFIDIOSrv = 0;

PhysiqueIO::LecteurRFIDIOService* PhysiqueIOFactory::getLecteurRFIDIOServiceImpl()
{
    if(lecteurRFIDIOSrv == 0){
        lecteurRFIDIOSrv = new PhysiqueIO::LecteurRFIDIOServiceTestImpl();
    }
    return lecteurRFIDIOSrv;
}
