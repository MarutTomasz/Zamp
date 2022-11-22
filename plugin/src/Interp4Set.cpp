#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
  Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
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
bool Interp4Set::ExecCmd(Scena  *pScena,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
