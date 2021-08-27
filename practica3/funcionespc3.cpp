
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
     cout << "Error abriendo el archivo entrada" << endl;
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

void decodificar( int seed , int metodo , string nombre_arc ,string salida ){
   /* recibe un archivo "nombre_arc" que esta codificado y regresa un archivo "nombre_exit"con el arcivo decodificado
      usando "metodo" elegido, para resultados correctos es necesario decodificar por el mismo metodo que se codifico "nombre_arc" al igual que con
      la misma semilla de codificacion
      ejemplo: codifico "archivo.txt*" por el metodo 1 con la semilla 4...
     se usa la funcion asi:  decodificar(4, 1, archivo_secreto.txt, archivo_revelado.txt)*/

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

    ofstream outfile;

       // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
       outfile.open("../practica3/BD/"+salida);

       // Se comprueba si el archivo fue abierto exitosamente
       if (!outfile.is_open())
       {
         cout << "Error abriendo el archivo" << endl;
         exit(1);
       }

    //pasar de numeros a letras

    int high = 7; int low = 0;
    for(int i =0 ; i < longitud/8;i++){
        int dec = 0 ;
        double exponente = 0;
        for (int j = high; j > low-1 ;j--){
            if(arreglo_desCodificado[j]==1){
                dec+= pow(2,exponente);
            }
            exponente+=1;
        }
        high+=8;low+=8;
        char num = dec;
        outfile << num;

    }
    // escribimnos el archivo de salida---------------------------------------------------------------------------
    outfile.close();
    //liberamos memoria
     delete [] arreglo_Codificado; delete []arreglo_desCodificado;


}

int inicio(){
    int op;
   cout <<"_____________________________________________" <<endl;
   cout <<"|Bienvenido a Su cajero ABRA-KADABRA        |" <<endl;
   cout <<"_____________________________________________" <<endl;
   cout <<"|  1  | ingresar como administrador         | " <<endl;
   cout <<"_____________________________________________" <<endl;
   cout <<"|  2  | ingresar como usuario               |" <<endl;
   cout <<"---------------------------------------------" <<endl;
   cout <<"|  0  | salir                               |" <<endl;
   cout <<"---------------------------------------------" <<endl;
  cout << "--->";cin >> op;
  for(int i = 0;  i < 10 ; i++){
      cout << "\n";
  }
  return op;
}

// parte 2 del programa

// class: adminitrador
administrador::administrador(string _pasword){
    pasword = _pasword;
}
string administrador::decodificar_metodo2(string _nombreArchivo){
    /*recibe el nombre de un archivo y retorna un string con el texto q hbaia en este*/
    string texto;
    //---------------------------------------------------------leer arhcivo de entrada-----------------------------------------------------------------
    int seed = 4;
    string data;
     ifstream infile;
     infile.open("../practica3/BD/"+_nombreArchivo);
     if (!infile.is_open())
     {
       cout << "Error abriendo el archivo" << endl;
       exit(1);
     }

     cout << "Leyendo el archivo" << endl;
     infile >> data;

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
  //decodificamos el arreglo por el metodo 2
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
  //pasamos de binario a letras, tomando de a 8 caracteres
  int high = 7; int low = 0;
  for(int i =0 ; i < longitud/8;i++){
      int dec = 0 ;
      double exponente = 0;
      for (int j = high; j > low-1 ;j--){
          if(arreglo_desCodificado[j]==1){
              dec+= pow(2,exponente);
          }
          exponente+=1;
      }
      high+=8;low+=8;
      //pasamos de decimal a la representacion de este
      char num = dec;
      texto+=num;
  }
  return(texto);
}
void administrador::registrar(){
    //--------------------------------- validacion
    string cedula;
    string clave;
    string dinero;
    string texto;
    cout << "ingrese la cedula:"<<endl;
    cin >>cedula ;

    cout << "ingrese la contraseña:"<<endl;
    cin >> clave;

    cout << "ingrese el dinero:"<<endl;
    //valor max 2147483647
    cin >> dinero;
    texto+=dinero+"_"+clave;
    //abrir el archivo
       ofstream outfile;

       // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
       outfile.open("../practica3/BD/"+cedula+".txt");

       // Se comprueba si el archivo fue abierto exitosamente
       if (!outfile.is_open())
       {
         cout << "Error abriendo el archivo" << endl;
         exit(1);
      }
    //codificar la info

       int longitud = texto.length()*8;
       int seed = 4;
       int *arreglo = new int[longitud]{0}; int rec_dat=0; int posci = 0;
       for (int i = 0; i < longitud/8 ; i++){
       posci+=1;
       char dato = texto[rec_dat]; int ascii = dato + 0;
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


    //escribirla
      for (int i = 0 ; i < longitud ; i++){
         std::string textox = to_string(*(arreglo_Codificado+i));
         outfile << textox;

            }
     // Se cierra el archivo
     outfile.close();
    //liberamos memoriaa
    delete [] arreglo; delete [] arreglo_Codificado;



}
//class cliente
void cliente::modificar(){
    bool exit = false;
    while(!exit){
        cout <<endl<<endl<<endl;
        cout << "________________________________"<<endl;
        cout <<"| USUARIO : "<<cedula<<"            |"<<endl;
        cout << "________________________________"<<endl;
        cout << "|  consultar saldo     |   1   |"<<endl;
        cout << "--------------------------------"<<endl;
        cout << "|  retirar plata       |   2   |"<<endl;
        cout << "--------------------------------"<<endl;
        cout << "|  salir               |   0   |"<<endl;
        cout << "--------------------------------"<<endl;
        // seleccionar el menu de interacicon
        string opcion ;cout <<"-->>";
        cin >> opcion;
        if(opcion == "1"){
            string BD = cedula+".txt";
            string informacion = cliente::decodiicar_metodo2(BD); //decodificamos la informacion guardada en el archivo del cliente
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
            int retiro = 1000;
            int Plata = atoi(plata.c_str());
            //comprobamos que si pueda hacer la consulta y lo restamos
            if( (Plata - retiro) >= 0 ){
                //se puede retirar
                dinero -= retiro;
                string num_str1(std::to_string(dinero));
                cout << "-----------------------------"<<endl;
                cout << "su saldo disponible es:     |"<<endl<<num_str1<<endl;
                cout << "-----------------------------"<<endl;
            }

            //si no, retornamos error
            else{
                cout << "saldo insuficiente para consultar "  <<endl;
            }

            //reescrbimos la informacion
            string direc = cedula+".txt";
            string valor (std::to_string(dinero));
            string texto_descodifcado = valor+"_"+clave;
            string escribir = cliente::codificar_textometodo2(texto_descodifcado); //texto codficado
            //abrimos el archivo y escribimos
            ofstream outfile;
                bool Open = true;
               // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
               outfile.open("../practica3/BD/"+direc);

               // Se comprueba si el archivo fue abierto exitosamente
               if (!outfile.is_open())
               {
                 cout << "Error abriendo el archivo" << endl;
                 Open = false;
               }
               if(Open){
               outfile << escribir << endl;
               // Se cierra el archivo
               outfile.close();}

        }
        else if (opcion == "2") {
            if(dinero - 1000 >= 1000){
            dinero -= 1000; //restamos los 1000 Cop
            cout << dinero <<endl;
            string BD = cedula+".txt";
            string informacion = cliente::decodiicar_metodo2(BD); //decodificamos la informacion guardada en el archivo del cliente
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
            // ingrese el dinero a retirar
            int retiro = 0;
            cout << "-----------------------------"<<endl;
            cout << "monto a retirar  |"; cin >> retiro;
            cout << "-----------------------------"<<endl;
            int Plata = atoi(plata.c_str());
            //comprobamos que si pueda hacer el retiro y lo restamos

            if( (Plata - retiro) >= 0 ){
                //se puede retirar
                dinero -= retiro;
                string num_str1(std::to_string(dinero));
                cout << "-----------------------------"<<endl;
                cout << "nuevo saldo   |"<< num_str1<<endl;
                cout << "-----------------------------"<<endl<<endl<<endl<<endl;
            }
            //si no, retornamos error
            else{
                cout << "saldo insuficiente para retirar "<< retiro <<endl;
            }
            //reescrbimos la informacion
            string direc = cedula+".txt";
            string valor (std::to_string(dinero));
            string texto_descodifcado = valor+"_"+clave;
            string escribir = cliente::codificar_textometodo2(texto_descodifcado); //texto codficado
            //abrimos el archivo y escribimos
            ofstream outfile;
                bool Open = true;
               // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
               outfile.open("../practica3/BD/"+direc);

               // Se comprueba si el archivo fue abierto exitosamente
               if (!outfile.is_open())
               {
                 cout << "Error abriendo el archivo" << endl;
                 Open = false;
               }
               if(Open){
               outfile << escribir << endl;
               // Se cierra el archivo
               outfile.close();}
            }
            else{
                cout << "-----------------------------"<<endl;
                cout << "dinero insuficiente para transaccion "<<endl;
                cout << "-----------------------------"<<endl<<endl<<endl<<endl;
            }
    }

        else if (opcion == "0") {
            exit = true;

        }
        else {
            cout << "opcion incorrecta"<<endl<<endl<<endl<<endl;
        }
        }
    }
string cliente::codificar_metodo2(string _nombreArchivo){
    //codificar
        string textoCodificado;
        int seed = 4;
        //---------------------------------------------------------leer arhcivo de entrada-----------------------------------------------------------------
         string data;
         ifstream infile;
         infile.open("../practica3/BD/"+_nombreArchivo);
         if (!infile.is_open())
         {
           cout << "Error abriendo el archivo entrada" << endl;
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
     for (int i = 0 ; i < longitud ; i++){
        std::string texto = to_string(*(arreglo_Codificado+i));
        textoCodificado+=texto;
           }
     delete [] arreglo_Codificado;
     delete [] arreglo;
     return textoCodificado;
    }
string cliente::decodiicar_metodo2(string _nombreArchivo){
    //decodificar
        string texto;
        //---------------------------------------------------------leer arhcivo de entrada-----------------------------------------------------------------
        int seed = 4;
        string data;
         ifstream infile;
         infile.open("../practica3/BD/"+_nombreArchivo);
         if (!infile.is_open())
         {
           cout << "Error abriendo el archivo" << endl;
           exit(1);
         }

         cout << "Leyendo el archivo" << endl;
         infile >> data;

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
      //decodificamos el arreglo por el metodo 2
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
      //pasamos de binario a letras, tomando de a 8 caracteres
      int high = 7; int low = 0;
      for(int i =0 ; i < longitud/8;i++){
          int dec = 0 ;
          double exponente = 0;
          for (int j = high; j > low-1 ;j--){
              if(arreglo_desCodificado[j]==1){
                  dec+= pow(2,exponente);
              }
              exponente+=1;
          }
          high+=8;low+=8;
          //pasamos de decimal a la representacion de este
          char num = dec;
          texto+=num;
      }
      return(texto);
    }
string cliente::codificar_textometodo2(string data){
    //codificar
        string textoCodificado;
        int seed = 4;
        //---------------------------------------------------------leer arhcivo de entrada-----------------------------------------------------------------

         int longitud = data.length()*8;   //cojo la longitud de la palabra
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
     for (int i = 0 ; i < longitud ; i++){
        std::string texto = to_string(*(arreglo_Codificado+i));
        textoCodificado+=texto;
           }
     delete [] arreglo_Codificado;
     delete [] arreglo;
     return textoCodificado;
}
cliente::cliente(string _cedula,string _clave, int _dinero){
    cedula = _cedula;
    clave = _clave;
    dinero = _dinero;
}
 //class codificar
 codificar::codificar(int _seed, int _metodo,string _entrada, string _salida){
     seed = _seed;
     metodo = _metodo;
     entrada = _entrada;
     salida = _salida;
 }
//decodificar
 decodificar::decodificar(int _seed, int _metodo,string _entrada, string _salida){
     seed = _seed;
     metodo = _metodo;
     entrada = _entrada;
     salida = _salida;
 }
