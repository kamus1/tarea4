#include<iostream>
#include<fstream>

using namespace std;

int cantidad, *valores;
string nombreArchivo = "input.hubert";

// trim from end (right)
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning (left)
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends (left & right)
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}


// funcion que determina la cantidad de elementos del archivo 
void funcionContador(){
    int contador = 0;
    string texto;
    ifstream archivo;
        archivo.open(nombreArchivo, ios::in);//abrir archivo en modo lectura
        
     while(!archivo.eof()){
        getline(archivo, texto); 
        trim(texto);
        if(texto != ""){
            contador ++;
        }
     }

     cantidad = contador;
     archivo.close();
}

//almacena los elementos del archivo en un array
void hubert_read(){
    string texto;
    ifstream archivo;
    archivo.open(nombreArchivo, ios::in);//abrir archivo en modo lectura

    //definir puntero array
    valores = new int[cantidad];

    //agregar valores a array
    int i = 0;
     while(!archivo.eof()){
        getline(archivo, texto); 
        trim(texto);
        
        if(texto != ""){
            valores[i] = stoi(texto); 
            i++;
        }
     }
     archivo.close();
}

//Insertion Sort
void Insertion_Sort(){
    int aux, i, posicion; 

    for(i =0;i<cantidad; i++){
        posicion = i;
        aux = valores[i];

        while((posicion>0) && (valores[posicion-1] > aux)){
            valores[posicion] = valores[posicion -1];
            posicion --;
        }
        valores[posicion] = aux;
    }

}

void hubert_write(){
        //crear archivo con valores ordenados por insertion sort
        ofstream archivoInsertion;
        archivoInsertion.open("output_1.hubert");

        //agregar valores a archivo
        for(int i = 0; i<cantidad; i++){
            archivoInsertion<<valores[i]<<endl;
        }
        archivoInsertion.close();
}

int main(){
    funcionContador();
    
    hubert_read();
    Insertion_Sort();
    hubert_write();

      
    //liberar memoria
    delete[] valores;

    return 0;
}
