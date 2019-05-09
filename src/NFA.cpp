//
// Created by DarkWayC0de_pc on 30/11/2018.
//
#include "../include/NFA.h"
namespace CyA{
  NFA::NFA() {

  }
  NFA::~NFA() {

  }
  void NFA::cargar(char *nombrefichero) {
      if(!NFA_.empty()){
          NFA_.clear();
          nestados_=0;
          arranque_=0;
      }
      build(nombrefichero);
  }
  void NFA::build(char *nombrefichero) {
      std::ifstream archivo;
      archivo.open(nombrefichero);
      if(!archivo.fail()){
          std::cout<<"Apertura de archivo correcta";
          archivo>>nestados_;
          archivo>>arranque_;
          for (int i = 0; i < nestados_; ++i) {
              Estado aux;
              archivo>>aux.estado_>>aux.aceptacion_>>aux.transiciones_;
              for (int j = 0; j <aux.transiciones_; ++j) {
                  std::pair<char, unsigned> auxp;
                  archivo>>auxp.first>>auxp.second;
                  aux.transicion_.insert(auxp);
              }
              NFA_.insert(aux);
          }
          analizar();

          archivo.close();
      }else{
          std::cout<<"Error en la apertura del archivo apertura";
      }
  }
  void NFA::analizar() {
      bool erro=false;
      if(NFA_.size()==nestados_){
          for (std::set<Estado>::iterator i = NFA_.begin(); i != NFA_.end(); i++) {
              if (i->transicion_.size() != i->transiciones_) {
                  erro=true;
              }
          }
      }else{
          erro=true;
      }
      if(erro){
          std::cout << "\nError definicion de automata";

          NFA_.clear();
      } else{
          std::cout <<"\nCarga correcta";
      }
  }
  bool NFA::vacio() {
      return NFA_.empty();
  }
  std::ostream& NFA::write(std::ostream &os) const{
      os<<"NFA\n"
        <<nestados_<<"\n"
        <<arranque_<<"\n";
      for(std::set<Estado>::iterator i= NFA_.begin();i!=NFA_.end();i++){
          i->write(os);
          os<<"\n";
      }
  }
  void NFA::muerte() {
      int muerto;
      bool vivo=true;
      std::cout<<"Estados de muerte: ";
      for(std::set<Estado>::iterator i=NFA_.begin();i!=NFA_.end();i++){
          muerto=0;
          for (std::set<std::pair<char,unsigned>>::iterator j=i->transicion_.begin(); j !=i->transicion_.end(); ++j) {
              if(j->second==i->estado_) {
                  muerto++;
              }
          }
          if(muerto==(i->transiciones_)){
              vivo=false;
              std::cout<<"\nEl estado "<<i->estado_<<" es un estado de muerte";
              if(i->transiciones_!=0) {
                  std::cout << " porque todas sun transiciones apuntan a si mismo como vemos aqui:";
                  for (std::set<std::pair<char, unsigned>>::iterator j = i->transicion_.begin(); j != i->transicion_.end(); ++j) {
                      std::cout << " " << j->first << " " << j->second;
                  }
              }else{
                  std::cout<<" porque no tiene transiciones";
              }
              std::cout <<"\n";
          }
      }
      if(vivo){
          std::cout<<"\nEste NFA no tiene estados de muerte";
      }
  }
  void NFA::importante() {
      std::cout<<"El conjunto de estados importantes es {";
      for (std::set<Estado>::iterator i = NFA_.begin(); i != NFA_.end(); i++) {
          bool imp = false;
          if (!i->aceptacion_) {
              for (std::set<std::pair<char, unsigned>>::iterator j = i->transicion_.begin(); j != i->transicion_.end(); j++) {
                  if (j->first != '~') {
                      imp = true;
                      break;
                  }
              }
          } else {
              imp = true;
          }
          if (imp) {
              std::cout << " " << i->estado_;
          }
      }
      std::cout<<" }\n";
  }
  void NFA::dfa() {
      bool nodfa= false;
      for (std::set<Estado>::iterator i = NFA_.begin(); i !=NFA_.end();i++){
          std::set<std::pair<char, unsigned>>::iterator last = i->transicion_.begin();
          for (std::set<std::pair<char, unsigned>>::iterator j =i->transicion_.begin(); j!=i->transicion_.end();) {
              j++;
              if(j!=i->transicion_.end()) {
                  //std::cout << last->first << "==" << j->first << std::endl;
                  if (last->first == j->first /*||j->first =='~'*/) {
                      nodfa = true;
                  }
                  last = j;
              }
          }
      }
      if(nodfa){
        std::cout<<"NO es un DFA";
      }else{
          std::cout<<"Es un DFA";
      }


  }
  void NFA::cadena2(void){
      char cadena[100];
      std::cout << "Introduce la cadena a analizar: ";
      std::cin >> cadena;
      std::cout<<"Cadena de entrada: "<<cadena;
      std::set<unsigned> estadoactual;
      estadoactual.insert(arranque_);

      std::vector<std::pair<unsigned ,char>> recorrido;
      unsigned ncadena =1;
      bool flag= false;
      buscarcadena2(cadena,0,estadoactual, recorrido,ncadena,flag);
      std::cout<<"\nDecision final: ";
      if(flag){
          std::cout<<"\nCadena de entrada ACEPTADA";
      } else{
          std::cout<<"\nCadena de entrada NO ACEPTADA";
      }

  }
  void NFA::buscarcadena2(char cadena[],unsigned it,std::set<unsigned> estadoactual,std::vector<std::pair<unsigned ,char>> recorrido,
                          unsigned& ncadena, bool& flag){
          epsilon(estadoactual);
          for(std::set<Estado>::iterator i=NFA_.begin();i!=NFA_.end();i++){
              for(std::set<unsigned >::iterator j=estadoactual.begin();j!=estadoactual.end();j++) {
                  if (i->estado_ == j.operator*()){
                      for (std::set<std::pair<char, unsigned>>::iterator k=i->transicion_.begin();k!=i->transicion_.end();k++){
                          if(cadena[it]==k->first) {
                              std::pair<unsigned, char> auxpair(i->estado_, k->first);
                              recorrido.push_back(auxpair);
                              std::set<unsigned> nuevoestadoactual;
                              nuevoestadoactual.insert(k->second);
                              buscarcadena2(cadena,it+1,nuevoestadoactual,recorrido,ncadena,flag);
                              recorrido.pop_back();
                          }
                      }
                  }
              }
          }
      if(cadena[it]=='\0'){
          std::cout<<"\nCadena "<<ncadena;
          std::cout<<"\nEstado actual\tEntrada\t\tSiguiente estado\n";
          for (int i = 0; i <recorrido.size()-1; ++i) {
              std::cout<<recorrido[i].first<<"\t\t"<<recorrido[i].second<<"\t\t"<<recorrido[i+1].first<<"\n";
          }
          for (std::set<unsigned >::iterator j=estadoactual.begin();j!=estadoactual.end();j++) {
              std::cout << recorrido[recorrido.size() - 1].first << "\t\t" << recorrido[recorrido.size() - 1].second
                        << "\t\t" << j.operator*() << "\n";
              if (aceptacion(j.operator*())) {
                  std::cout << "Cadena de entrada ACEPTADA";
                  flag = true;
              } else {
                  std::cout << "Cadena de entrada No ACEPTADA";
              }
              ncadena++;
          }
      }
  }
  void NFA::epsilon(std::set<unsigned> estadoactual){
          for(std::set<Estado>::iterator i=NFA_.begin();i!=NFA_.end();i++){
              for(std::set<unsigned >::iterator j=estadoactual.begin();j!=estadoactual.end();j++) {
                  if (i->estado_ == j.operator*()){
                      for (std::set<std::pair<char, unsigned>>::iterator k=i->transicion_.begin();k!=i->transicion_.end();k++) {
                          if(k->first=='~'){
                              estadoactual.insert(k->second);
                          }
                      }
                  }
              }
          }
  }
  void NFA::cadena() {
      char cadena[100];
      bool flag=false;
      std::vector<std::pair<unsigned, char>> lestados;
      int ncadena=1;
      std::cout << "Introduce la cadena a analizar: ";
      std::cin >> cadena;
      std::cout<<"Cadena de entrada: "<<cadena;
      buscacadenas(arranque_, cadena, lestados, 0,ncadena, flag);
      std::cout<<"\nDecision final: ";
      if(flag){
          std::cout<<"\nCadena de entrada ACEPTADA";
             } else{
        std::cout<<"\nCadena de entrada NO ACEPTADA";
        }
  }
  void NFA::buscacadenas(unsigned estado, char cadena[],std::vector<std::pair<unsigned,char>>& lestados, unsigned itcadena, int& ncadena, bool& flag){
      if(cadena[itcadena]!='\0'){
          for (std::set<Estado>::iterator i=NFA_.begin();i!=NFA_.end();i++){
            if(i->estado_==estado){
              for (std::set<std::pair<char, unsigned>>::iterator j=i->transicion_.begin();j!=i->transicion_.end();j++){
                  std::pair<unsigned, char> auxpair;
                  if (j->first == '~') {
                      auxpair.first=i->estado_;
                      auxpair.second='~';
                      lestados.push_back(auxpair);
                      buscacadenas(j->second,cadena,lestados,itcadena,ncadena, flag);
                      lestados.pop_back();
                  }
                  if(j->first == cadena[itcadena]){
                      auxpair.first=i->estado_;
                      auxpair.second=j->first;
                      lestados.push_back(auxpair);
                      buscacadenas(j->second,cadena,lestados,itcadena+1,ncadena,flag);
                      lestados.pop_back();
                  }
              }

            }
          }
      }else{
          std::cout<<"\nCadena "<<ncadena;
          std::cout<<"\nEstado actual\tEntrada\t\tSiguiente estado\n";
          for (int i = 0; i <lestados.size()-1; ++i) {
              std::cout<<lestados[i].first<<"\t\t"<<lestados[i].second<<"\t\t"<<lestados[i+1].first<<"\n";
          }
          std::cout<<lestados[lestados.size()-1].first<<"\t\t"<<lestados[lestados.size()-1].second<<"\t\t"<<estado<<"\n";
          if(aceptacion(estado)){
              std::cout<<"Cadena de entrada ACEPTADA";
                flag=true;
          } else{
              std::cout<<"Cadena de entrada No ACEPTADA";
          }
          ncadena++;
      }
  }
  bool NFA::aceptacion(unsigned a) {
      for(std::set<Estado>::iterator i=NFA_.begin();i!=NFA_.end();i++){
          if(i->estado_==a){
              return i->aceptacion_;
          }
      }
      return false;
  }
}