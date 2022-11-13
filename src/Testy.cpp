#include "Testy.hh"

Testy::Testy() {}

Testy::~Testy() {}

bool Testy::TworzenieBibliotekiMove() {

  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 0;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 0;
  }
  
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
  Interp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  
  cout << endl;
  pCmd->PrintSyntax();
  
  cout << endl;
  pCmd->PrintCmd();
  
  delete pCmd;
  dlclose(pLibHnd_Move);

  return 1;
  
}

bool Testy::TworzenieCmdBibliotek() {
  
  LibInterface move("libInterp4Move.so", RTLD_LAZY);
  LibInterface rotate("libInterp4Rotate.so", RTLD_LAZY);
  LibInterface set("libInterp4Set.so", RTLD_LAZY);
  LibInterface pause("libInterp4Pause.so", RTLD_LAZY);

  move.getCmdName();
  rotate.getCmdName();
  pause.getCmdName();
  set.getCmdName();
  return 1;
}


bool Testy::TworzenieKolekcjiBibliotek() {

  Set4LibInterfaces Bib;
  Bib.AddLibInterface("Move");
  Bib.AddLibInterface("Rotate");
  Bib.AddLibInterface("Pause");
  Bib.AddLibInterface("Set");
  
  Interp4Command *move=Bib["Move"]->getCmd();
  Interp4Command *rotate=Bib["Rotate"]->getCmd();
  Interp4Command *pause=Bib["Pause"]->getCmd();
  Interp4Command *set=Bib["Set"]->getCmd();
  
  move->GetCmdName();
  rotate->GetCmdName();
  pause->GetCmdName();
  set->GetCmdName();
  return 1;
   
  
}


bool Testy::CzytanieParametorw(istringstream &Strumien){

  Set4LibInterfaces Bib;
  Bib.AddLibInterface("Move");
  Bib.AddLibInterface("Rotate");
  Bib.AddLibInterface("Set");
  Bib.AddLibInterface("Pause");


  string Name;
  Interp4Command *tmp;
  
  Strumien >> Name;
  tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;
  
  Strumien >> Name;
  tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;

  Strumien >> Name;
  tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;

  Strumien >> Name;
  tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;

  Strumien >> Name;
  tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;

  Strumien >> Name;
  tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;

  Strumien >> Name;
  tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;


  return 1;
}

bool Testy::WektorCmd(istringstream &Strumien) {
  Set4LibInterfaces Bib;
  Bib.AddLibInterface("Move");
  Bib.AddLibInterface("Rotate");
  Bib.AddLibInterface("Set");
  Bib.AddLibInterface("Pause");

  vector<Interp4Command*> CmdCollection;

  string Name;
  while(!Strumien.eof()) {
    Strumien >> Name;
    if(Name.length() > 0){
      CmdCollection.push_back(Bib[Name]->getCmd());
      CmdCollection.back()->ReadParams(Strumien);
    }
  }
  
  for(Interp4Command* cmd : CmdCollection){
    cmd->PrintSyntax();
    cmd->PrintCmd();
  }

  return 1;
}


