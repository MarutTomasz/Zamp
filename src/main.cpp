#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include <sstream>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <list>


#define LINE_SIZE 500

using namespace std;
using namespace xercesc;


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





/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}









int main(int argc, char *argv[]) {

  //   Configuration   Config;

  //   if (!ReadFile("config/config.xml",Config)) return 1;




  if(argc < 2) {
    cerr << "Za mało argumentów wywołania programu..." << endl;
    exit(-1);
  }
  
  istringstream Strumien;

  if ( !ExecPreprocesor(argv[1], Strumien)) {
      cerr << "Niepoprawny plik do wczytania..." << endl;
      exit(-1);
  }
  
  Set4LibInterfaces Bib;
  Bib.AddLibInterface("Move");
  Bib.AddLibInterface("Rotate");
  Bib.AddLibInterface("Set");
  Bib.AddLibInterface("Pause");
  
  
  string Name;
  Strumien >> Name;
  Interp4Command *tmp = Bib[Name]->getCmd();
  tmp->ReadParams(Strumien);
  tmp->PrintSyntax();
  tmp->PrintCmd();
  delete tmp;
  
  string Name2;
  Strumien >> Name2;
  Interp4Command *tmp2 = Bib[Name2]->getCmd();
  tmp2->ReadParams(Strumien);
  tmp2->PrintSyntax();
  tmp2->PrintCmd();
  delete tmp2;
  
  string Name3;
  Strumien >> Name3;
  Interp4Command *tmp3 = Bib[Name3]->getCmd();
  tmp3->ReadParams(Strumien);
  tmp3->PrintSyntax();
  tmp3->PrintCmd();
  delete tmp3;

}