#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "funcionespc3.h"
using namespace std;

int main () {

    char data[100];
    /*
    // abrir un archivo en modo escritura
    ofstream outfile;
    string str1;cin>> str1;
    str1+=".txt";
    // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
    outfile.open("../practica3/BD/"+str1);

    // Se comprueba si el archivo fue abierto exitosamente
    if (!outfile.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }
     outfile.close();
    */
    // abrir un archivo en modo escritura
    ofstream outfile;
    string str1;cin>> str1;
    str1+=".txt";
    // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
    outfile.open("../practica3/BD/"+str1);

    // Se comprueba si el archivo fue abierto exitosamente
    if (!outfile.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }

    cout << "Escribiendo en el archivo" << endl;
    cout << "Ingresa tu nombre: ";
    cin.getline(data, 100);

    // Escribir el dato ingresado en el archivo
    outfile << data << endl;

    cout << "Ingresa tu edad: ";
    cin >> data;
    cin.ignore();

    // Se escribe la edad en el archivo
    outfile << data << endl;

    // Se cierra el archivo
    outfile.close();

    return 0;

    //--------------------------------------------------------
bool a=true;
 while (a){
 int opcion= inicio();
 if (opcion == 0){
     //__------------------------------------------------------------------------CONTRASEÑA DE ADMIN: ABRKDA152
     cout << "BIENVENIDO  ZONA DE ADMIN"<<endl;
       bool aux_ingreso =  comprobacion ("sudo.txt");
       if (aux_ingreso ==true){
      //ingresar como admin (para hacer registros)
     cout << "Registro Administrador exitoso \n continua proceso de registro \n" << endl;
      registrar();
      cout << "registro exitoso"<<endl;
       }
       else{
           cout << "cerrando..."<<endl;
       }
  }
  else if (opcion == 1){
      //ingresar como usuario (para retirar o meter plata)
  }
  else if (opcion == 9){
      a = false;
  }
  else{
      cout << "-----------ERROR-------"<<endl;
  }

 }
return 0;
}
