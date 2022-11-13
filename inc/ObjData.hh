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
  ObjData();
  ~ObjData();
  void SetShift(Vector3D shift);		
  
  
};
