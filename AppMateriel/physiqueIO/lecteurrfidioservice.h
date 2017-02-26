#ifndef LECTEURRFIDIOSERVICE_H
#define LECTEURRFIDIOSERVICE_H
#include <QString>
#include "metier/materielserviceimpl.h"

namespace PhysiqueIO {
class LecteurRFIDIOService
{
public:
   virtual bool ecrireBadge(Materiel materiel) = 0;
   virtual Materiel lireBadge() = 0;
};
}

#endif // LECTEURRFIDIOSERVICE_H
