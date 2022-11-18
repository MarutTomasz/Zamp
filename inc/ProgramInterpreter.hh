#ifndef PROGRAMINTERPRETER
#define PROGRAMINTERPRETER

#include <map>
#include <memory>
#include "Scena.hh"
#include "Set4LibInterfaces.hh"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <list>


using namespace std;
using namespace xercesc;



class ProgramInterpreter {
public:
  Scena _Scn;
  Set4LibInterfaces _LibMenager;
  int Socket2Serv = 2926;
  Configuration *rConfig;
  bool ExecProgram(const char* FileName);
  bool SendSceneState2Server();
  bool Read_XML_Config(const char* sFileName);
  ProgramInterpreter();
};


#endif