#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
  Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
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
bool Interp4Rotate::ExecCmd(Scena *pScena,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
