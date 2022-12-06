#include "Scena.hh"

Scena::Scena(){
}

Scena::~Scena(){
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

