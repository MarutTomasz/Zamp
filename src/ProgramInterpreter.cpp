#include "ProgramInterpreter.hh"



ProgramInterpreter::ProgramInterpreter() {
  rConfig = new Configuration;
}

bool ProgramInterpreter::ExecProgram(const char* NazwaPliku) {
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  istringstream Strumien;

  
  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

  if (!pProc)
    return false;

  while (fgets(Line,LINE_SIZE,pProc)) {
    OTmpStrm << Line;
  }

  Strumien.str(OTmpStrm.str());
  vector<Interp4Command*> CmdCollection;

  string Name;
  while(!Strumien.eof()) {
    Strumien >> Name;
    if(Name.length() > 0){
      CmdCollection.push_back(_LibMenager[Name]->getCmd());
      CmdCollection.back()->ReadParams(Strumien);
    }
  }
  
  for(Interp4Command* cmd : CmdCollection){
    //    cmd->ExecCmd(_Scn,Socket2Serv);
    cmd->PrintCmd();
  }
  
  
  
}


bool ProgramInterpreter::SendSceneState2Server() {
  for (int i = 0; i < rConfig->GetObjVector().size(); ++i){
    stringstream Napis;
    ObjData tmp = rConfig->GetObjVector()[i];
    Napis << "AddObj Name=" << tmp.GetName() << " RGB="  << tmp.GetRGB() << "  Scale=" << tmp.GetScale() <<
      " Shift=" << tmp.GetShift() << " RotXYZ_deg=" << tmp.GetRotXYZ() << " Trans_m=" << tmp.GetTrans() <<"\n";

    const string tmp2 = Napis.str();
    const char *napis = tmp2.c_str();
    Send(Socket2Serv,napis);
    
    
    
  }
  
  delete rConfig;
}


/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ProgramInterpreter::Read_XML_Config(const char* sFileName)
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




