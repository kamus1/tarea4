#include<iostream>
#include<fstream>

using namespace std;


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


// funcion que retorna la cantidad de elementos 
int funcionContador(string nombreArchivo){
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
     return contador;
}

int main(){
    string nombreArchivo = "input.hubert";
    string texto;
    
    ifstream archivo;
        archivo.open(nombreArchivo, ios::in);//abrir archivo en modo lectura

    //verificar que el archivo se haya abierto correctamente
    if(archivo.fail()){
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }

    int cantidad = funcionContador(nombreArchivo);

    //definir puntero y array
    int *valores;
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

        //Insertion sort
        int aux, posicion; 

        for(i =0;i<cantidad; i++){
            posicion = i;
            aux = valores[i];

            while((posicion>0) && (valores[posicion-1] > aux)){
                valores[posicion] = valores[posicion -1];
                posicion --;
            }
            valores[posicion] = aux;
        }

        //crear archivo con valores ordenados por insertion sort
        ofstream archivoInsertion;
        archivoInsertion.open("output_1.hubert");

        //agregar valores a archivo
        for(i = 0; i<cantidad; i++){
            archivoInsertion<<valores[i]<<endl;
        }
        archivoInsertion.close();
        //liberar memoria
        delete [] valores;

    return 0;
}
