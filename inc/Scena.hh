#ifndef SCENA
#define SCENA

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "MobileObj.hh"

class Scena {
public:
  MobileObj* FindMobileObj(const char *sName);
  void AddMobileObj(MobileObj *pMobObj);

};




#endif

