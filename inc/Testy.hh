#ifndef TESTY_HH
#define TESTY_HH

#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include <sstream>
#include <vector>

using namespace std;

class Testy {
private:
  
  
public:
  Testy();
  ~Testy();
  bool TworzenieBibliotekiMove();
  bool TworzenieCmdBibliotek();
  bool TworzenieKolekcjiBibliotek();
  bool CzytanieParametorw(istringstream &Strumien);
  bool WektorCmd(istringstream &Strumien);
};

#endif
