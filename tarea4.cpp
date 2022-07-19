#include<iostream>
#include<fstream>
#include <ctime> 
 

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

//codigo control c control v de quicksort CAAAAAMBIAR
void Quick_Sort(int* xArray, int xSize)
{
        int lPivot = xArray[xSize-1];
        int lIndexOfLargestElement = 0;
        for (int i = 0; i < xSize-1; i++)
        {
                if (xArray[i] < lPivot)
                {
                        // Swap largest element with this
                        int lTmp = xArray[i];
                        xArray[i] = xArray[lIndexOfLargestElement];
                        xArray[lIndexOfLargestElement]  = lTmp;
                        lIndexOfLargestElement++;
                }
        }
        // swap pivot with xArray[lIndexOfLargestElement]
        int lTmp = xArray[lIndexOfLargestElement];
        xArray[lIndexOfLargestElement] = xArray[xSize-1];
        xArray[xSize-1] = lTmp;
        if (lIndexOfLargestElement > 1)
                Quick_Sort(xArray, lIndexOfLargestElement);
        if (xSize-lIndexOfLargestElement-1 > 1)
                Quick_Sort(xArray+lIndexOfLargestElement+1, xSize-lIndexOfLargestElement-1);
}

void hubert_write(string nombreArchivo){
        //crear archivo con valores ordenados por insertion sort
        ofstream archivo;
        archivo.open(nombreArchivo);

        //agregar valores a archivo
        for(int i = 0; i<cantidad; i++){
            archivo<<valores[i]<<endl;
        }
        archivo.close();
}

int main(){
    //para medir el tiempo de ejecucion (creo que hay que borrarlo del codigo para la entrega)
    unsigned t0, t1;
    funcionContador();
    
    hubert_read();
    t0=clock();
    Insertion_Sort();
    t1 = clock();
    hubert_write("output_1.hubert");
    //liberar memoria
    delete[] valores;
    //calculo del tiempo
    double time = (double(t1-t0)/CLOCKS_PER_SEC);


    hubert_read();
    t0=clock();
    Quick_Sort(valores, cantidad);
    t1=clock();
    hubert_write("output_2.hubert");
    //liberar memoria
    delete[] valores;
    //calculo del tiempo
    double time2 = (double(t1-t0)/CLOCKS_PER_SEC);

    //muestra por pantalla los tiempos de ejecución 
    cout << "Tiempo de ejecucion de Insertion Sort: " << time << endl;
    cout << "Tiempo de ejecucion de Quick Sort: " << time2 << endl;
    return 0;
}
