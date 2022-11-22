#include "Send.hh"

int Send(int Socket2Serv, const char *sMesg) {
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);
  
  while ((IlWyslanych = write(Socket2Serv,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}
