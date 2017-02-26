#ifndef LECTEURRFIDIOSERVICETESTIMPL_H
#define LECTEURRFIDIOSERVICETESTIMPL_H
#include "lecteurrfidioservice.h"
#include <QString>
#include "metier/type.h"
#include "time.h"

namespace PhysiqueIO {
class LecteurRFIDIOServiceTestImpl : public LecteurRFIDIOService
{
public:
    LecteurRFIDIOServiceTestImpl();
    ~LecteurRFIDIOServiceTestImpl();
    Materiel lireBadge();
    bool ecrireBadge(Materiel materiel);
private:
    QList<Materiel> materiels;
};
}

#endif // LECTEURRFIDIOSERVICETESTIMPL_H
