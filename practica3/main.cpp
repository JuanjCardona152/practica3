#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "funcionespc3.h"
using namespace std;

int main () {
    int opcion = 9999;
    while(opcion != 0){
    opcion = inicio();
    if(opcion == 0){
        cout << "Hasta pronto"<<endl<<"gracias por confiar en nosotros"<<endl<<endl;
    }
    else if (opcion == 1){
        //para ingresar como admin tiene que ingresar con la contraseña, contraseña == si es un administrador
        //para comprobar , decodificamos "sudo" y comprobamos que si sea correcto y creamos el objeto tipo admin
        cout << "-----------------------------"<<endl;
        cout << "Ingrese la clave de administardor| ";
        string clave; cin >> clave;
        cout << "-----------------------------"<<endl;
        administrador nuevo_Admin = administrador(clave);
        string Security_Pasword = nuevo_Admin.decodificar_metodo2("sudo.txt"); //decodificamos y lo guardamos en un string
        //contraseña de seguridad:   ABRKDA152
        cout << "validando..."<<endl;
        bool admin = false;
        if (Security_Pasword == clave){
            cout <<endl<< "contraseña correcta"<<endl;
            admin = true;
        }
        else{
            cout << "contraseña incorrecta"<< endl;
        }
        //una vez validada la contraseña pasamos a registrar
        if(admin){
            nuevo_Admin.registrar();
        }
        else{
            cout<<"volviendo a Inicio"<<endl<<endl;
        }
        }
    else if  (opcion == 2){
        //para ingresar como usuario tiene q ingresar cedula y la clave. cedula == existe una base de datos,
        //clave == si es la persona indicada para el retiro (comprobamos decodificando el archivo y comprobando la info.
        //, metmos le dinero en una variable y luego creamos el objeto tipo cliente para el uso de sus metodos.
        cout << "-----------------------------"<<endl;
        cout << "Ingrese su cedula| ";
        string cC; cin >> cC;
        cout << "-----------------------------"<<endl;
        //creamos un cliente unicamente para uasr un metodo de este y validar el acceso
        cliente cliente_ayuda = cliente("000","000",0000);
        string informacion = cliente_ayuda.decodiicar_metodo2(cC+".txt");
        int separar = informacion.find("_");
        string plata;
        string validar;
        for (int i = 0; i < informacion.length() ; i ++ ) { // separar la contrasñea y el dinero disponible para trabajar con ellos
            if(informacion[i] != informacion[separar] && i < separar){
                plata+=informacion[i];
            }
            else if( i > separar){
                validar+= informacion[i];
            }
        }
        cout << "-----------------------------"<<endl;
        cout << "Ingrese su contraseña| ";
        string pw; cin >> pw;
        cout << "-----------------------------"<<endl;
        if(validar == pw){
            //pusobien la contraseña puede modificar los datos
            cout << endl<< "accediendo. . . "<<endl<<endl;
            int Plata = atoi(plata.c_str());
            cliente cl1ente = cliente(cC,pw,Plata);
            cl1ente.modificar();
        }
        else{
            cout << "contraseña incorrecta, por favor verifiquela y vuelva a ingresar"<<endl<<endl;
        }

        }
    else{
        cout << "Opcion incorrecta"<<endl<<endl<<endl;
        }
    }




return 0;
}
