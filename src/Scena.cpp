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

  for(unsigned long int i = 0; i < pConfig->GetObjVector().size(); ++i) {
    shared_ptr<MobileObj> tmp = make_shared<MobileObj>();
    
    
    tmp->SetPosition_m(pConfig->GetObjVector()[i].GetTrans());
    tmp->SetName(pConfig->GetObjVector()[i].GetName().c_str());
    tmp->SetAng_Yaw_deg(pConfig->GetObjVector()[i].GetRotXYZ()[2]);
    _Set_MobileObj[tmp->GetName()] = tmp;
  }
}

shared_ptr<MobileObj> Scena::operator [] (string &rName){
  return _Set_MobileObj[rName];
}

shared_ptr<MobileObj> Scena::operator [] (char *sName){
  return _Set_MobileObj[sName];
}

