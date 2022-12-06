#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
  Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
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
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(){
  _Cord_X = 0;
  _Cord_Y = 0;
  _Ort_OZ = 0;
}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _Name_obj << " " << _Cord_X  << " " << _Cord_Y << " " << _Ort_OZ <<  endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd(Scena  *pScena, GuardedSocket *Socket) const
{
  Vector3D NowaPozycja;
  NowaPozycja[0] = _Cord_X;
  NowaPozycja[1] = _Cord_Y;
  NowaPozycja[2] = 0;
  pScena->FindMobileObj(_Name_obj)->LockAccess();
  pScena->FindMobileObj(_Name_obj)->UsePosition_m() = NowaPozycja;
  pScena->FindMobileObj(_Name_obj)->SetAng_Yaw_deg(_Ort_OZ); 
  stringstream Napis;
  Napis << "UpdateObj Name=" << pScena->FindMobileObj(_Name_obj)->GetName() << " Trans_m=" << pScena->FindMobileObj(_Name_obj)->GetPosition_m() << " RotXYZ_deg=(0,0," << pScena->FindMobileObj(_Name_obj)->GetAng_Yaw_deg() <<")\n";
  
  const string tmp2 = Napis.str();
  const char *napis = tmp2.c_str();

  Socket->LockAccess();
  Send(Socket->GetSocket(),napis);
  Socket->UnlockAccess();
  pScena->FindMobileObj(_Name_obj)->UnlockAccess();
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _Name_obj >> _Cord_X >> _Cord_Y >> _Ort_OZ))
    return false;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  X   Y  OZ" << endl;
}
