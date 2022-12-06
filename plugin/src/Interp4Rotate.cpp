#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
  Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
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
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate() {
  _Angle_deg = 0;
  _Speed_degS = 0;
}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << _Name_obj << " " << _Speed_degS << " " << _Angle_deg << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd(Scena *pScena,  GuardedSocket *Socket) const
{
  for (double dst = _Angle_deg; dst > 0; dst-= 1){

    pScena->FindMobileObj(_Name_obj)->LockAccess();
    pScena->FindMobileObj(_Name_obj)->SetAng_Yaw_deg(pScena->FindMobileObj(_Name_obj)->GetAng_Yaw_deg() + 1); 
    stringstream Napis;
    Napis << "UpdateObj Name=" << pScena->FindMobileObj(_Name_obj)->GetName() << " RotXYZ_deg=(0,0," << pScena->FindMobileObj(_Name_obj)->GetAng_Yaw_deg() <<")\n";
    
    const string tmp2 = Napis.str();
    const char *napis = tmp2.c_str();


    Socket->UnlockAccess();
    Send(Socket->GetSocket(),napis);
    Socket->UnlockAccess();
    pScena->FindMobileObj(_Name_obj)->UnlockAccess();
    usleep(1000000/_Speed_degS);
  }
  
  return true; 
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _Name_obj >> _Speed_degS >> _Angle_deg))
    return false;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Prędkość[deg/s] Kąt[deg]" << endl;
}
