#include "LibInterface.hh"

void LibInterface::CreateCmd() {
  void *pFun = dlsym(_LibHandler, "CreateCmd");
  if (!pFun) {
    cerr << "[ERROR] function not found: CreateCmd" << endl;
    exit(-1); 
  }
  
  _pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
  Interp4Command *tmp = _pCreateCmd();
  _CmdName = tmp->GetCmdName();
  delete tmp;
}


LibInterface::LibInterface(const char *Name, int mode) {
  _LibHandler = dlopen(Name, mode);

  if(!_LibHandler) {
    cerr << "[ERROR] library not found: " << Name << endl;
    exit(-1);
  }
  CreateCmd();
}


LibInterface::~LibInterface(){
  dlclose(_LibHandler);
}


std::string LibInterface::getCmdName(){
  return _CmdName;
}


Interp4Command* LibInterface::getCmd() const{
  return _pCreateCmd();
}

