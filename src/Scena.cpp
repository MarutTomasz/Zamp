#include "Scena.hh"

Scena::Scena(){
}

Scena::~Scena(){
}

shared_ptr<MobileObj> Scena::FindMobileObj(const char *sObjName){
  return _Set_MobileObj[sObjName];
}

shared_ptr<MobileObj> Scena::FindMobileObj(const string &rObjName){
  return _Set_MobileObj[rObjName];
}

void Scena::AddMobileObj(Configuration *pConfig){
  //  shared_ptr<MobileObj> tmp = make_shared<MobileObj>(...);
  //  _set_MobileObj[...];
  
}

shared_ptr<MobileObj> Scena::operator [] (string &rName){
  return _Set_MobileObj[rName];
}

shared_ptr<MobileObj> Scena::operator [] (char *sName){
  return _Set_MobileObj[sName];
}

