//
// Created by DarkWayC0de_pc on 17/11/2018.
//
#include "../include/Estado.h"
namespace CyA{
  Estado::Estado() {

  }
  Estado::~Estado() {

  }
  Estado& Estado::operator=(const CyA::Estado &a) {
    this->estado_=a.estado_;
    this->aceptacion_=a.aceptacion_;
    this->transiciones_=a.transiciones_;
    this->transicion_=a.transicion_;
    return *this;
  }
  int Estado::operator==(const CyA::Estado &a) const {
    if(this->estado_ != a.estado_)return 0;
    if(this->aceptacion_ != a.aceptacion_)return 0;
    if(this->transiciones_ != a.transiciones_)return 0;
    if(this->transicion_ != a.transicion_)return 0;
    return 1;
  }
  int Estado::operator<(const CyA::Estado &a) const {
    return (this->estado_<a.estado_);
  }
  std::ostream & Estado::write(std::ostream &os) const {
    os<<estado_<<" "<<aceptacion_<<" "<<transiciones_;
    for(std::set<std::pair<char,unsigned>>::iterator i=transicion_.begin();i!=transicion_.end();i++){
      os<<" "<<i->first<<" "<<i->second;
    }
  }

}


