#ifndef OBJDATA_HH
#define OBJDATA_HH

#include <vector>
#include "Vector3D.hh"

using namespace std;


class ObjData {
private:
  string _Name;
  Vector3D _Shift;
  Vector3D _Scale;
  Vector3D _RotXYZ;
  Vector3D _Trans;
  Vector3D _RGB;
public:
  ObjData() {
    for(int i=0; i<3; ++i){
    _Shift[i] = 0;
    _Scale[i] = 1;
    _RotXYZ[i] = 0;
    _Trans[i] = 0;
    _RGB[i] = 128;
    }
  }
  
  void SetShift(Vector3D shift) { _Shift = shift; }		
  void SetScale(Vector3D scale) { _Scale = scale; }
  void SetRotXYZ(Vector3D rotxyz) { _RotXYZ = rotxyz; }
  void SetTrans(Vector3D trans) { _Trans = trans; }
  void SetRGB(Vector3D rgb) { _RGB = rgb; }
  void SetName(string name) { _Name = name; }
  
  Vector3D GetShift() { return _Shift; }
  Vector3D GetScale() { return _Scale; }	
  Vector3D GetRotXYZ() { return _RotXYZ; }
  Vector3D GetTrans() { return _Trans; }		
  Vector3D GetRGB() { return _RGB; }
  string GetName() {return _Name; }
 
};

#endif
