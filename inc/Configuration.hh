#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "ObjData.hh"




class Configuration {
private:
  vector<string> _LibsVector;
  vector<ObjData> _ObjVector;
public:
  vector<string>& GetLibsVector() { return _LibsVector; }
  vector<ObjData>& GetObjVector() { return _ObjVector; }
  void AddLib(string name) { _LibsVector.push_back(name); }
  void AddObj(ObjData obj) { _ObjVector.push_back(obj); }
};


#endif
