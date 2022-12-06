#include <iostream>
#include "Interp4Move.hh"
#include "Scena.hh"

using std::cout;
using std::endl;

#define BLAD cout << "TU BŁĄD -------- " << endl 


extern "C" {
  Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}





int Send(int Socket2Serv, const char *sMesg) {
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);
  
  while ((IlWyslanych = write(Socket2Serv,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}



/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 * 
 */
Interp4Move::Interp4Move() {
  _Speed_mmS = 0;
  _Distance_mm = 0;
}


/*!
 *
 */
void Interp4Move::PrintCmd() const{
  
  cout << GetCmdName() << " " << _Name_obj  << " " << _Speed_mmS << " " << _Distance_mm << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd(Scena  *pScena,  GuardedSocket *Socket) const
{
  Vector3D Przesuniecie;
  Przesuniecie[2] = 0.0;
  for (double dst = _Distance_mm; dst > 0; dst -= 1){

    pScena->FindMobileObj(_Name_obj)->LockAccess();
    Przesuniecie[0] = cos(pScena->FindMobileObj(_Name_obj)->GetAng_Yaw_deg()*3.14/180);
    Przesuniecie[1] = sin(pScena->FindMobileObj(_Name_obj)->GetAng_Yaw_deg()*3.14/180);
    pScena->FindMobileObj(_Name_obj)->UsePosition_m() =  pScena->FindMobileObj(_Name_obj)->GetPosition_m() + Przesuniecie;

    stringstream Napis;
    Napis << "UpdateObj Name=" << pScena->FindMobileObj(_Name_obj)->GetName() << " Trans_m=" << pScena->FindMobileObj(_Name_obj)->GetPosition_m() <<"\n";
    
    const string tmp2 = Napis.str();
    const char *napis = tmp2.c_str();
    Socket->LockAccess();
    Send(Socket->GetSocket(),napis);
    Socket->UnlockAccess();
    pScena->FindMobileObj(_Name_obj)->UnlockAccess();
    usleep(1000000/_Speed_mmS);
  }
  return true; 
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList) {

  if(!(Strm_CmdsList >> _Name_obj >> _Speed_mmS >> _Distance_mm))
    return false;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Prędkość[m/s]  DlugoscDrogi[m]" << endl;
}
