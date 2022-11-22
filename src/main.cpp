#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include <sstream>
#include <vector>
#include "Testy.hh"
#include "Vector3D.hh"
#include "Scena.hh"
#include "ProgramInterpreter.hh"
#include "Send.hh"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>


#define PORT 2926
#define LINE_SIZE 500


/*
bool ExecPreprocesor(const char *NazwaPliku, istringstream &IStrm4Cmds) {
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

  if (!pProc)
    return false;

  while (fgets(Line,LINE_SIZE,pProc)) {
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}
*/

/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}






int main(int argc, char *argv[]) {  
  if(argc < 2) {
    cerr << "Za mało argumentów wywołania programu..." << endl;
    exit(-1);
  }
  
  //  istringstream Strumien;

  //  if (!ExecPreprocesor(argv[1], Strumien)) {
  //    cerr << "Niepoprawny plik do wczytania..." << endl;
  //     exit(-1);
  // }

   ProgramInterpreter Boss;
  
   //  Configuration *Config = new Configuration;
  //  if (!ReadFile("config/config.xml",Config)) {
   if (!Boss.Read_XML_Config("config/config.xml")) {
     return 1;
   }
   
   // MIEJSCE NA TESTY 
   /*
     Testy TEST;
  //if(TEST.TworzenieBibliotekiMove()){
  // if(TEST.TworzenieCmdBibliotek()){
  // if(TEST.TworzenieKolekcjiBibliotek()){
  // if(TEST.CzytanieParametorw(Strumien)){
  //if(TEST.WektorCmd(Strumien)){
    cout << "Poprawnie wykonano test. Działa." << endl;
    return 1;
  }
  else{
    cerr << "Coś poszło nie tak :(. Zabijam się..." << endl;
    exit(-1);
  }
  */
   
   // if (!OpenConnection(Boss.Socket2Serv)) return 1;

   
   for(unsigned long int i = 0; i < Boss.rConfig->GetLibsVector().size(); ++i) {
     Boss._LibMenager.AddLibInterface(Boss.rConfig->GetLibsVector()[i]);
   }
   
   
   Boss._Scn.AddMobileObj(Boss.rConfig);

   
   //Send(Boss.Socket2Serv"Clear\n");
   
   //Boss.SendSceneState2Server();
   
   Boss.ExecProgram(argv[1]);
   
   
   //  vector<Interp4Command*> CmdCollection;
  
   //  string Name;
   // while(!Strumien.eof()) {
   //  Strumien >> Name;
   //  if(Name.length() > 0){
   //   CmdCollection.push_back(Boss._LibMenager[Name]->getCmd());
   //   CmdCollection.back()->ReadParams(Strumien);
   // }
   //  }
  
   // for(Interp4Command* cmd : CmdCollection){
   //  cmd->PrintSyntax();
   //   cmd->PrintCmd();
   //  }
   
   Send(Boss.Socket2Serv,"Close\n");
   close(Boss.Socket2Serv);
}
