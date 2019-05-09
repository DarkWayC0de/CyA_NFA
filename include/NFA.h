//
// Created by DarkWayC0de_pc on 30/11/2018.
//
#ifndef NFA_NFA_H
#define NFA_NFA_H
#include "Estado.h"
#include <fstream>
#include <vector>

namespace CyA {
  class NFA {
    private:
        std::set<Estado> NFA_;
        unsigned nestados_, arranque_;

        void build (char nombrefichero[]);
        void analizar(void);
        void buscacadenas(unsigned estado, char cadena[],std::vector<std::pair<unsigned,char>>& lestados, unsigned itcadena,int&,bool &);
        bool aceptacion(unsigned a);
        void epsilon(std::set<unsigned> estadoactual);
        void buscarcadena2(char cadena[],unsigned it,std::set<unsigned> estadoactual,std::vector<std::pair<unsigned ,char>> recorridounsigned,unsigned& ncadena, bool& flag);

    public:
        NFA();
        ~NFA();
        void cargar(char nombrefichero[]);
        bool vacio (void);
        std::ostream& write(std::ostream &os) const;
        void muerte(void); //Revisar si un estdo de muerte puede ser de aceptacion
        void importante(void);
        void dfa(void);
        void cadena(void);
        void cadena2(void);

  };
}

#endif //NFA_NFA_H
