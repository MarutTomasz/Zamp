#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces() {
}

Set4LibInterfaces::~Set4LibInterfaces(){
}

shared_ptr<LibInterface> Set4LibInterfaces::operator [](string Cmd) {
  return _LibsCollection[Cmd];
}

void Set4LibInterfaces::AddLibInterface(string Name) {
  switch(Name[0]) {
  case 'M': {
    shared_ptr<LibInterface> tmp = make_shared<LibInterface>("libInterp4Move.so",RTLD_LAZY);
    _LibsCollection[Name] = tmp;
    break;
  }

  case 'R': {
    shared_ptr<LibInterface> tmp = make_shared<LibInterface>("libInterp4Rotate.so",RTLD_LAZY);
    _LibsCollection[Name] = tmp;
    break;
  }
    
  case 'P': {
    shared_ptr<LibInterface> tmp = make_shared<LibInterface>("libInterp4Pause.so",RTLD_LAZY);
    _LibsCollection[Name] = tmp;
    break;
  }
    
  case 'S': {
    shared_ptr<LibInterface> tmp = make_shared<LibInterface>("libInterp4Set.so",RTLD_LAZY);
    _LibsCollection[Name] = tmp;
    break;
  }
  }
  
}
