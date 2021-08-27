
#ifndef FUNCIONESPC3_H
#define FUNCIONESPC3_H
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
void codificar( int , int  ,  string ,  string  );
void decodificar( int , int , string ,string  );
int inicio();
class administrador{
private:
    string pasword;
public:
    administrador(string);
    void registrar();      //agregar gente a la base de datos
   string decodificar_metodo2(string);
};
class cliente{
private:
    string cedula;
    string clave;
    int dinero;
public:
    cliente(string,string, int); //constructor
    void modificar(); //consultar saldo o retirar
    string codificar_metodo2(string);
    string codificar_textometodo2(string);
    string decodiicar_metodo2(string);
 };
class codificar{
private:
    int seed;
    int metodo;
    string entrada;
    string salida;
public:
    codificar (int,int,string,string);//constructor
    void codificar_metodo1();
    void codificar_metodo2();
};
class decodificar{
    int seed;
    int metodo;
    string entrada;
    string salida;
public:
    decodificar(int,int,string,string); //constructor
    void decodificar_metodo1();
    void decodificar_metodo2();

};

#endif // FUNCIONESPC3_H
