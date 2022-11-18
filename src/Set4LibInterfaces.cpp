#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces() {
}

Set4LibInterfaces::~Set4LibInterfaces(){
}

shared_ptr<LibInterface> Set4LibInterfaces::operator [](string Cmd) {
  return _LibsCollection[Cmd];
}



void Set4LibInterfaces::AddLibInterface(string Name) {
  const char* name = Name.c_str();
  shared_ptr<LibInterface> tmp = make_shared<LibInterface>(name,RTLD_LAZY);
  _LibsCollection[tmp->getCmdName()] = tmp;
  
}
