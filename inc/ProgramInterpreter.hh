#ifndef PROGRAMINTERPRETER
#define PROGRAMINTERPRETER

#include <map>
#include <memory>
#include "Scena.hh"
#include "Set4LibInterfaces.hh"
#include "Send.hh"
#include "GuardedSocket.hh"


#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <list>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <queue>

#define LINE_SIZE 500

using namespace std;
using namespace xercesc;


class ProgramInterpreter {
public:
  Scena _Scn;
  Set4LibInterfaces _LibMenager;
  GuardedSocket Socket2Serv;
  Configuration *rConfig;
  bool ExecProgram(const char* FileName);
  bool SendSceneState2Server();
  bool Read_XML_Config(const char* sFileName);
  ProgramInterpreter();
};

#endif
