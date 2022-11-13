#ifndef SET4LIBINTERFACE
#define SET4LIBINTERFACE

#include <map>
#include <memory>
#include "LibInterface.hh"

using namespace std;

class Set4LibInterfaces {
private:
  map<string,shared_ptr<LibInterface>> _LibsCollection;
  
public:
  Set4LibInterfaces();
  ~Set4LibInterfaces();
  void AddLibInterface(string Name);
  shared_ptr<LibInterface> operator [] (string Cmd);
};


#endif

