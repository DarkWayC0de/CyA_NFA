#include <iostream>
#include "../include/NFA.h"
int main() {
	system("clear");
	//system("cls");
    std::cout<<"Practica 7 de Computabilidad y Algoritmia";
    char opcion;
    CyA::NFA A;
    do{
        std::cout<< "\nc .-Cargar NFA"
                    "\nm .-Mostras NFA"
                    "\ni .-Identificar estados de muerte"
                    "\nh .-Identificar estados importantes"
                    "\nd .-Comprobar DFA"
                    "\na .-Analizar cadena"
                    "\nq .-Finalizar programa"
                    "\nIntroduce la letra de la acion a ejecutar:";
        std::cin>>opcion;
        //system("cls");
	system("clear");
        switch (opcion){
            case 'c':
                char nombrefichero[50];

                std::cout<<"Introduzca el nombre del fichero:";
                std::cin>>nombrefichero;
                A.cargar(nombrefichero);
                break;
            case 'm':
                if(!A.vacio()) {
                    A.write(std::cout);
                }else{
                    std::cout<<"Tines que cargar primero el NFA";
                }
                break;
            case 'i':
                if(!A.vacio()) {
                    A.muerte();
                }else{
                    std::cout<<"Tines que cargar primero el NFA";
                }
                break;
            case 'h':
                if (!A.vacio()){
                    A.importante();
                }else{
                    std::cout<<"Tines que cargar primero el NFA";
                }
                break;
            case 'd':
                if (!A.vacio()){
                    A.dfa();
                }else{
                    std::cout<<"Tines que cargar primero el NFA";
                }
                break;
            case 'a':
                if (!A.vacio()) {
                    A.cadena2();
                }else{
                    std::cout<<"Tines que cargar primero el NFA";
                }
                break;
            case 'q':
                break;

            default:
                std::cout<<"\nEsa opcion no te la he ofrecido. Por favor introduce una opcion del listado";
        }

    }while(opcion!='q');
    return 0;
}
