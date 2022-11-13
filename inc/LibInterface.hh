#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <string>
#include <dlfcn.h>

#include "Interp4Command.hh"
#include "MobileObj.hh"

using namespace std;

class LibInterface {
private:
  void *_LibHandler;
  string _CmdName;
  Interp4Command *(*_pCreateCmd)(void);
  
public:
  LibInterface(const char *Name, int mode);
  ~LibInterface();

  string getCmdName();
  Interp4Command* getCmd() const;
  void CreateCmd();   
};

#endif
