
#include <fstream>
#include <iostream>
#include <string>
#include "funcionespc3.h"
using namespace std;

int main () {
    //                                                                 main
    //---------------------------------------------------------------------------------------------------------------------------------
    cout << "BIENVENIDO A ...\npruebas primer punto practica 3\n "<<endl;
    while (true){

    cout << "ingrese 0 para  [ C 0 D 1 F 1 C A R ]\ningrese 1 para  [ D 3 C 0 D 1 F 1 C A R ] \n|||\nvvv"<<endl;
    int opcion; cin >> opcion;
    if(opcion == 0){
        //codificar
        cout << "0pcion:  [ C 0 D 1 F 1 C A R ]\n¿que hace?\nla opcion codificar coge un archivo con strings y lo transforma en un archivo binario codificado\n"<<endl;
        cout << "empezaremos con  el nombre de entrada y salida \n\n este se debe encontrar en la carpeta BD \n Por favor escriba el nombre del archivo de entrada  con su extension (Ejemplo: afile.txt ): ";
        string nombre_arc;cin >> nombre_arc;
        cout << "\n Por favor escriba el nombre del archivo de salida con su extension (Ejemplo: salida.txt ): ";
        string nombre_exit; cin >> nombre_exit;
        cout << "\n Por favor ingrese un numero como semilla de codificacion (Ejemplo: 5): ";
        int seed; cin >> seed;
        cout << "\n\nPara Ingresar el metodo de codificacion...tenga en cuenta cada metodo\n";
        cout << "ingrese 1 para conocer en que consiste cada metodo, o 0 para continuar : ";
        int op; cin >> op;
        if (op == 1){
        cout << "\n [ M 3 T 0 D 0 _ 1 ]\nse separan en bloques de n bits.\nEn el primer bloque se cambian todos los 1 por 0 y viceversa.\n Para los grupos siguientes se debe contar el número de 1s y 0s en el grupo anterior y hacer cambios según la siguiente regla: \n";
        cout <<" + Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.\n + Si hay mayor cantidad de 0s se invierte cada 2 bits.\n + Si hay mayor cantidad de 1s se invierte cada 3 bits.\n\n";
        cout << "\n [ M 3 T 0 D 0 _ 2 ]\nse separa en bloques de n bits.\nCada bit dentro de un grupo se desplaza una posición, de manera que el primer bit del grupo codificado corresponde al último bit del grupo sin codificar, el segundo bit codificado corresponde al primero sin codificar y así sucesivamente hasta que el último corresponde al penúltimo sin codificar.\n\n";
        }
        cout << "ingrese 1 (metodo 1) ó 2 para (metodo 2):";
        int metodo; cin >> metodo;
        void codificar( int seed , int metodo , string nombre_arc , string nombre_exit  );

    }
    else if(opcion == 1){
        //decodificar
        cout << "0pcion:  [  D 3 C 0 D 1 F 1 C A R ]\n ¿que hace?\n la opcion decodificar coge un archivo binario codificado y lo descodifica y lo convierte en letras \n"<<endl;
        cout << "empezaremos con  el nombre de entrada y salida \n\n este se debe encontrar en la carpeta BD \n Por favor escriba el nombre del archivo de entrada con su extension (Ejemplo: afile.txt ): ";
        string nombre_arc;cin >> nombre_arc;
        cout << "\n Por favor escriba el nombre del archivo de salida con su extension (Ejemplo: salida.txt ): ";
        string nombre_exit; cin >> nombre_exit;
        cout << "\n Por favor ingrese un numero como semilla de codificacion (Ejemplo: 5): ";
        int seed; cin >> seed;
        cout <<"ingrese el metodo de descodificación (tenga en cuenta usar el mismo metodo con el que se codifico , para la descodificacion) \n" ;
        cout << "ingrese 1 (metodo 1) ó 2 para (metodo 2):";
        int metodo; cin >> metodo;
        void decodificar( int seed , int metodo , string nombre_arc , string nombre_exit  );


    }
    else{cout << "-------------opcion incorrecta--------------"<<endl;}
    }
}
