#ifndef SCENA
#define SCENA

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "MobileObj.hh"
#include <map>
#include <memory>
#include "Configuration.hh"
#include "Send.hh"

using namespace std;


class Scena {
private:
  map<string,shared_ptr<MobileObj>> _Set_MobileObj;
public:
  Scena();
  ~Scena();
  shared_ptr<MobileObj> FindMobileObj(const char *sObjName) {  return _Set_MobileObj[sObjName]; }

  shared_ptr<MobileObj> FindMobileObj(const string &rObjName){   return _Set_MobileObj[rObjName]; }

  void AddMobileObj(Configuration *pConfig);

  shared_ptr<MobileObj> operator [] (string &rName)  { return _Set_MobileObj[rName]; }

  shared_ptr<MobileObj> operator [] (char *sName) {  return _Set_MobileObj[sName]; }

};




#endif

