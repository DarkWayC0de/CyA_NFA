//
// Created by DarkWayC0de_pc on 17/11/2018.
//
#ifndef PR6_ESTADO_H
#define PR6_ESTADO_H
#include <set>
#include <iostream>
#include <iterator>

namespace CyA {
  class Estado {
  private:

  public:
    unsigned estado_, transiciones_;
    bool aceptacion_;
    std::set<std::pair<char,unsigned>> transicion_;

    Estado();
    virtual ~Estado();
    Estado &operator=(const Estado &a);
    int operator==(const Estado &a)const;
    int operator<(const Estado &a)const ;
    std::ostream& write(std::ostream &os) const;
  };
}

#endif //PR6_ESTADO_H
