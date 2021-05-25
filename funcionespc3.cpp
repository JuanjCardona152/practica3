#include <fstream>
#include <iostream>
#include <string>
#include "funcionespc3.h"
#include <cmath>
using namespace std;
void codificar( int seed , int metodo , string nombre_arc , string nombre_exit  ){
    /*recibe un archivo "nombre_arc" que contiene un texto a codificar y regresa un archivo "nombre_exit"con el arcivo codificado en binarios
      usando "metodo" elegido. se usa la funcion asi:  codificar(4, 1, archivo_texto.txt, archivo_secreto.txt)
       NO INGRESAR TEXTOS CON ESPACIOS, YA QUE NO LEE LO QUE HAY DESPUES DEL ESPACIO*/

  //---------------------------------------------------------leer arhcivo de entrada-----------------------------------------------------------------
   string data;
   ifstream infile;
   infile.open("../practica3/BD/"+nombre_arc);
   if (!infile.is_open())
   {
     cout << "Error abriendo el archivo" << endl;
     exit(1);
   }

   cout << "Leyendo el archivo" << endl;
   infile >> data;
   cout << data << endl;
   int longitud = data.length()*8;   //cojo la longitud de la palabra
   infile.close();
                                     //generar un arreglo con las letras en decimal
int *arreglo = new int[longitud]{0}; int rec_dat=0; int posci = 0;
for (int i = 0; i < longitud/8 ; i++){
posci+=1;
char dato = data[rec_dat]; int ascii = dato + 0;
int *arr= new int [7]{0};
int cont = 0;
do{
int bin = ascii %2;
ascii = ascii /2;
arr[cont]=bin;
cont+=1;
}while(ascii != 0);
for (int j = 6; j > -1; j--){
arreglo[posci]= arr[j];
posci+=1;
}
rec_dat+=1;
delete [] arr;
}
//genneramos un arreglo donde se hara l a codificacion
int primar;//primar  genera cuantos grupos de n terminos se generan.
if (longitud% seed == 0){
     primar = longitud / seed; //si genera n grupos exactos sera longitud de caracteres (cada caracter son 8 numeros en binario) / seed.
}
else{
     primar = (longitud / seed) +1; //pero si queda sobrando asi sea 1 numero, primar sera +1 para poder contar este otro
}
int *arreglo_Codificado = new int[longitud]{0}; //genera un arreglo tipo int el cual sera escrito en el nuevo archivo

  //--------------------------------------------------------------------codificar----------------------------------------------------------------
    if(metodo == 1){ //trabja con el metodo 1
                //para coger de a n terminos, se itera sobre "arreglo" "primar" veces
        int inferior = 0; int superior = seed; //estas 2 vaariables cogeran termino por termino en un grupo de n terminos
        for (int i = 0; i != primar; i++){
            //contar los 1 y 0 del grupo anterior (en arreglo)  para ello se usa l = inferior- seed y superior -seed que corresponden al grupo anterior
            int ceros=0; int unos=0;
            for(int l = inferior-seed; l != superior-seed; l++){

                if (arreglo[l]==1){
                    unos+=1;
                }
                else{
                    ceros+=1;
                }
            }
            int n_doble = 1;   //contara las posciciones en los arreglos de 1 hasta n para saber cuando esta a 2 o 3 bits
            do{      //este do while va bit por bit de grupos de a n  bits usando a inferior y superior
                if (inferior < seed){          //trabajar con el primer arreglo de n terminos ya que este es el primero que se modifica en el metodo 1
                    if(arreglo[inferior]==1){
                        arreglo_Codificado[inferior]=0;
                    }
                    else{
                        arreglo_Codificado[inferior]=1;

                    }

                }
                else{                       //trabajar con los siguientes arreglos para su codificacion

                    if(ceros == unos){                   //evalua la condicion  --- Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.---
                        if(arreglo[inferior]==1){
                            arreglo_Codificado[inferior]=0;
                        }
                        else{
                            arreglo_Codificado[inferior]=1;
                        }
                    }
                    else if (ceros > unos){                         //evalua la condicion --- Si hay mayor cantidad de 0s se invierte cada 2 bits. ---
                        if (n_doble % 2 == 0){
                            if(arreglo[inferior]==1){
                                arreglo_Codificado[inferior]=0;
                            }
                            else{
                                arreglo_Codificado[inferior]=1;
                            }
                        }
                        else{
                            arreglo_Codificado[inferior]= arreglo[inferior];
                        }
                    }
                    else{                                           //evalua la condicion ---  Si hay mayor cantidad de 1s se invierte cada 3 bits.---
                        if (n_doble % 3 == 0){
                            if(arreglo[inferior]==1){
                                arreglo_Codificado[inferior]=0;
                            }
                            else{
                                arreglo_Codificado[inferior]=1;
                            }
                        }
                        else{
                            arreglo_Codificado[inferior]= arreglo[inferior];
                        }
                    }
                }
                inferior+=1; n_doble+=1;
            }while(inferior != superior);
           superior += seed; //superior incrementa en +n ya que esta cogiendo de a n grupos de terminos
        }
        }
    else if (metodo == 2){ //trabaja con el metodo 2
        int inferior = 0; int superior = seed;//estas 2 vaariables cogeran termino por termino en un grupo de n terminos
       for (int i = 0; i != primar; i++){
           do{ //este do while va bit por bit de grupos de a n  bits usando a inferior y superior
               int num_inicial=arreglo[((seed*(i+1))-1)]; //este algoritmo saca el numero de la Ultima poscicion de cualquier grupo de n elementos
               if (inferior == (seed*i)){  // seed*i saca la primera posicion en cualquier grupo de n elementos y compara si inferior esta en esa posicion
                   arreglo_Codificado[inferior]=num_inicial; //el ultimo numero del grupo de n elemntos pasa a ser el primero en el arrelgo_codificado
                    }
            else{
                   arreglo_Codificado[inferior]= arreglo[inferior-1]; // cada bit en la posicion "inferior" toma el valor del bit que esta  a su izquierda en arreglo_ codificado
               }
               inferior += 1;
           }while(inferior != superior);
           superior += seed; //superior incrementa en +n ya que esta cogiendo de a n grupos de terminos
       }

    }
    else{ //si se ingreso un metodo invalido no retorna nada
        cout << "metodo invalido \n no se puede codificar"<<endl;

    }

    //-----------------------------------------------------------escribir en archivo de salida-----------------------------------------------------
    ofstream outfile;
    outfile.open("../practica3/BD/"+nombre_exit); //abre en la carpeta BD o crea un archivo con el nombre "nombre_exit"
    if (!outfile.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }
    cout << "Escribiendo en el archivo" << endl;
      for (int i = 0 ; i < longitud ; i++){
         std::string texto = to_string(*(arreglo_Codificado+i));
         outfile << texto;
            }
     // Se cierra el archivo
     outfile.close();
    //liberamos memoria
    delete [] arreglo; delete [] arreglo_Codificado;
}
void decodificar( int seed , int metodo , string nombre_arc ){
    /*recibe un archivo "nombre_arc" que esta codificado y regresa un archivo "nombre_exit"con el arcivo decodificado
      usando "metodo" elegido, para resultados correctos es necesario decodificar por el mismo metodo que se codifico "nombre_arc" al igual que con
      la misma semilla de codificacion
      ejemplo: codifico "archivo.txt*" por el metodo 1 con la semilla 4...
     se usa la funcion asi:  decodificar(4, 1, archivo_secreto.txt, archivo_revelado.txt) */

    //---------------------------------------------------------leer arhcivo de entrada-----------------------------------------------------------------
     string data;
     ifstream infile;
     infile.open("../practica3/BD/"+nombre_arc);
     if (!infile.is_open())
     {
       cout << "Error abriendo el archivo" << endl;
       exit(1);
     }

     cout << "Leyendo el archivo" << endl;
     infile >> data;
     cout << data << endl;
     int longitud = data.length();   //cojo la longitud de la palabra
     infile.close();

  int *arreglo_Codificado = new int[longitud]{0}; //creamos un arreglo que sera descodificado
  for (int i = 0; i < longitud ; i++){
      int num_cd = data[i]-48;
        arreglo_Codificado[i]= num_cd;
  }
  int primar;
  if (longitud%seed == 0){
       primar = longitud / seed;
  }
  else{
       primar = (longitud / seed) +1;
  }
  int *arreglo_desCodificado = new int[longitud]{0};
    //--------------------------------------------------------------------decodificar----------------------------------------------------------------
    if(metodo == 1){

        int inferior = 0; int superior = seed;
        for (int i = 0; i != primar; i++){
            int ceros=0; int unos=0;
            for(int l = inferior-seed; l != superior-seed; l++){
                if (arreglo_desCodificado[l]==1){
                    unos+=1;
                }
                else{
                    ceros+=1;
                }
            }
            int n_doble = 1;
            do {
                if (inferior < seed){                                                         //trabajar con el primer arreglo de n terminos
                    if(arreglo_Codificado[inferior]==1){
                        arreglo_desCodificado[inferior]=0;
                    }
                    else{
                        arreglo_desCodificado[inferior]=1;
                    }
                }
                else{
                if(ceros == unos){
                    if(arreglo_Codificado[inferior]==1){
                        arreglo_desCodificado[inferior]=0;
                    }
                    else{
                        arreglo_desCodificado[inferior]=1;
                    }
                }
                else if (ceros > unos){
                    if (n_doble % 2 == 0){
                        if(arreglo_Codificado[inferior]==1){
                            arreglo_desCodificado[inferior]=0;
                        }
                        else{
                            arreglo_desCodificado[inferior]=1;
                        }
                    }
                    else{
                        arreglo_desCodificado[inferior]= arreglo_Codificado[inferior];
                    }
                }
                else{
                    if (n_doble % 3 == 0){
                        if(arreglo_Codificado[inferior]==1){
                            arreglo_desCodificado[inferior]=0;
                        }
                        else{
                            arreglo_desCodificado[inferior]=1;
                        }
                    }
                    else{
                        arreglo_desCodificado[inferior]= arreglo_Codificado[inferior];
                    }

                }

                }
                  cout << arreglo_desCodificado[inferior];
                  inferior+=1; n_doble +=1;
            }while(inferior != superior);
            superior+=seed;
        }
    }
    else if (metodo == 2){
        int inferior = 0; int superior = seed;
        for (int i = 0; i != primar; i++){
            do{
                int num_inicial=arreglo_Codificado[seed*i];
                if (inferior == (((seed*(i+1))-1))){
                    arreglo_desCodificado[inferior]=num_inicial;
                     }
             else{
                    arreglo_desCodificado[inferior]= arreglo_Codificado[inferior+1];
                }
                inferior += 1;
            }while(inferior != superior);
            superior += seed;
        }

    }
    else{cout<< "metodo invalido"<<endl;}

    //liberamos memoria
     delete [] arreglo_Codificado; delete []arreglo_desCodificado;
}
int inicio(){
    int op;
   cout <<"_____________________________________________" <<endl;
   cout <<"|Bienvenido a Su cajero ABRA-KADABRA        |" <<endl;
   cout <<"_____________________________________________" <<endl;
   cout <<"|  0  | ingresar como administrador         | " <<endl;
   cout <<"_____________________________________________" <<endl;
   cout <<"|  1  | ingresar como usuario               |" <<endl;
   cout <<"---------------------------------------------" <<endl;
   cout <<"|  9  | salir                               |" <<endl;
   cout <<"---------------------------------------------" <<endl;
  cout << "--->";cin >> op;
  for(int i = 0;  i < 10 ; i++){
      cout << "\n";
  }
  return op;
}
void registrar(){
    char data[100];
    //registro
    //- nombre archivo = cedula
    //-contenido= nombre + saldo
   // abrir un archivo en modo escritura
       ofstream outfile;
       //cedula
       cout << "ingrese cedula:";
       string cc; cin >> cc;
        cc+=".txt";
        cout << cc <<endl;
       // Se pone de manera explicita la ruta relativa donde se encuentra el archivo

        outfile.open("../practica3/BD/"+cc);

       // Se comprueba si el archivo fue abierto exitosamente
       if (!outfile.is_open())
       {
         cout << "Error abriendo el archivo" << endl;
         exit(1);
       }

       cout << "Escribiendo en el archivo" << endl; string name;
       cout << "Ingresa el nombre: ";cin.getline(data,100);
       // Escribir el dato ingresado en el archivo
       outfile << data << endl;
       cout << "Ingresa el saldo: "; cin >> data;
       cin.ignore();

       // Se escribe la edad en el archivo      
       outfile << data << endl;

       // Se cierra el archivo
       outfile.close();
}
bool comprobacion (string  nombre_arc){
    //ingresa el lugar donde se encuentra la contraseña codificada e hace la comprobacion de que la contraseña este correcta, retorna True si la ingreso bien
    bool encontrado = false;
    //---------------------------------------------------------leer arhcivo de entrada-----------------------------------------------------------------
     string data; int seed = 4;
     ifstream infile;
     infile.open("../practica3/BD/"+nombre_arc);
     if (!infile.is_open())
     {
       cout << "Error abriendo el archivo" << endl;
       exit(1);
     }

     infile >> data;
     int longitud = data.length();   //cojo la longitud de la palabra
     infile.close();
//---------------------------------------------------------------decodificamos-----------------------------------------------------------------------
  int *arreglo_Codificado = new int[longitud]{0}; //creamos un arreglo que sera descodificado
  for (int i = 0; i < longitud ; i++){
      int num_cd = data[i]-48;
        arreglo_Codificado[i]= num_cd;
  }
  int primar;
  if (longitud%seed == 0){
       primar = longitud / seed;
  }
  else{
       primar = (longitud / seed) +1;
  }
  int *arreglo_desCodificado = new int[longitud]{0};

  int inferior = 0; int superior = seed;
  for (int i = 0; i != primar; i++){
      do{
          int num_inicial=arreglo_Codificado[seed*i];
          if (inferior == (((seed*(i+1))-1))){
              arreglo_desCodificado[inferior]=num_inicial;
               }
       else{
              arreglo_desCodificado[inferior]= arreglo_Codificado[inferior+1];
          }
          inferior += 1;
      }while(inferior != superior);
      superior += seed;
  }
//-----------------------------convertimso a decimal-----------------------------------------
   seed = 8; inferior = 0;  superior = seed; double base = 2; int cont=0;
   char *arreDec = new char [longitud/8]{0} ;
    for (int i = 0; i != primar; i++){
    int exponente = 7;int sumatt=0;
        do{
     int auxDec = arreglo_desCodificado[inferior];
     int num = pow(base,exponente);
     sumatt = sumatt+(num * auxDec) ;
    inferior += 1; exponente -=1;
    }while(inferior != superior);
    arreDec[cont]=sumatt;
    superior += seed;cont+=1;
    }
//------------------------------------------------------------comprobamos si es igual a la clave ingresada----------------------------------------------
    string add; string arre="";
    for (int i = 0; i != longitud/8; i ++){
        arre+=*(arreDec+i);
    }
    bool correcta =false;
      while (correcta != true){
          cout << "Ingrese la contraseña de Administrador: ";
          cin >> add;//recorremos cada puesto comprobando si son iguales
          correcta =true;
              if (add != arre){
                    correcta = false;

          }
          if (correcta == false){
              cout << "contraseña incorrecta"<<endl;
              cout << "desea volver a intentarlo? (1. si/ 0. no) : "; int op ;cin >> op;
              if (op == 0){
                  correcta = true;
              }
              else{
                  correcta = false;
              }
          }
          else {
              cout << "ingresando..."<<endl;
              encontrado = true;
          }
      }
  return(encontrado);
}
void modificar(string nombre_arc){
    for (int i = 0; i != 20 ; i++){
        cout << endl;
    }
    //esta funcin es para hacer cambios en la cuenta, como retiro,s ingresos,  consultar saldo
    cout <<"Bienvenido A su Cajero virtual"<<endl;
    cout <<"___________________________________"<<endl;
    cout <<"| 0. | consultar saldo            |"<<endl;
    cout <<"___________________________________"<<endl;
    cout <<"| 1. | retirar plata              | "<<endl;
    cout <<"-----------------------------------"<<endl;
    int op; cin >> op;
    if(op == 0){
        //consultar saldo, leer el archivo
        string data; int seed = 4;
        ifstream infile;
        infile.open("../practica3/BD/"+nombre_arc);
        if (!infile.is_open())
        {
          cout << "Error abriendo el archivo" << endl;
          exit(1);
        }

        infile >> data;
        int longitud = data.length();   //cojo la longitud de la palabra
        infile.close();
   //---------------------------------------------------------------decodificamos-----------------------------------------------------------------------
     int *arreglo_Codificado = new int[longitud]{0}; //creamos un arreglo que sera descodificado
     for (int i = 0; i < longitud ; i++){
         int num_cd = data[i]-48;
           arreglo_Codificado[i]= num_cd;
     }
     int primar;
     if (longitud%seed == 0){
          primar = longitud / seed;
     }
     else{
          primar = (longitud / seed) +1;
     }
     int *arreglo_desCodificado = new int[longitud]{0};

     int inferior = 0; int superior = seed;
     for (int i = 0; i != primar; i++){
         do{
             int num_inicial=arreglo_Codificado[seed*i];
             if (inferior == (((seed*(i+1))-1))){
                 arreglo_desCodificado[inferior]=num_inicial;
                  }
          else{
                 arreglo_desCodificado[inferior]= arreglo_Codificado[inferior+1];
             }
             inferior += 1;
         }while(inferior != superior);
         superior += seed;
     }
   //-----------------------------convertimso a decimal-----------------------------------------
      seed = 8; inferior = 0;  superior = seed; double base = 2; int cont=0;
      char *arreDec = new char [longitud/8]{0} ;
       for (int i = 0; i != primar; i++){
       int exponente = 7;int sumatt=0;
           do{
        int auxDec = arreglo_desCodificado[inferior];
        int num = pow(base,exponente);
        sumatt = sumatt+(num * auxDec) ;
       inferior += 1; exponente -=1;
       }while(inferior != superior);
       arreDec[cont]=sumatt;
       superior += seed;cont+=1;
       }
        for (int i = 0; i != (longitud/8);i++){
            cout << *(arreDec+i);
        }
    }
    else if(op == 0){
        //abrir en modo escritura

    }
    else{
        cout<< "opcion invalida"<<endl;
    }

}
