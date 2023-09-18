#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <fstream>
#include <string.h>

using namespace std;

string addZeros(int num, int desired_length){

	string base = "";

	for(int i=0; i < (desired_length - to_string(num).length()); i++)
    {
		base += "0";
	}

	base += to_string(num);
	return base;
}

string monthToNum(string mes, string *meses)
{
	for(int i = 0; i < 12; i++)
	{
		if(mes == meses[i])
		{
			return addZeros(i+1, 2);
		}
	}

	return "-1";

}

string removeDots(string hora)
{
	string resultado;
	for(int i=0; i<hora.length(); i++){
		if(hora[i] != ':') resultado += hora[i];
	}
	return resultado;
}

// Funci�n de ordenamiento del m�todo Quick Sort
int particion(vector<string> &A, int l, int r)
{
    // Define el pivote y la variable de ciclo de este
    int pivote = stoi(A[r]);
    int i = l - 1;

    for(int j = l; j < r; j++)
    {
        // Conforme cicla todo el arreglo, revisa si un valor es menor al pivote
        if(stoi(A[j]) < pivote)
        {
            // La variable de ciclo aumenta en 1 para que el intercambio se realice con el elemento siguiente
            i++;

            // El elemento correspondiente a la variable de ciclo y el comparado intercambian posiciones
            string aux = A[i];
            A[i] = A[j];
            A[j] = aux;
        }
    }

    // El pivote y el elemento correpondiente a donde termine la variable de ciclo intercambian posiciones
    string aux = A[i + 1];
    A[i + 1] = A[r];
    A[r] = aux;

    // Se devuelve i + 1, lo cual acorta el arreglo
    return(i + 1);
}

// || M�todo Quick Sort ||

/*
    Complejidad de tiempo:

Mejor Caso - n log n / linear�tmica
En promedio - n log n / linear�tmica
Peor caso - n^2 / cuadr�tica

    Complejidad de espacio: log n / logar�tmica
*/

void sortVector(vector<string> &A, int l, int r)
{
    // Continuan las recursiones mientras que la posici�n inicial sea menor a la final
    if(l < r)
    {
        /* Los pivotes representan elementos de comparaci�n tanto al inicio como al final
        del arreglo. Todos los elementos terminaran siendo pivotes conforme el arreglo se
        reduce, de esta manera todos los elementos se comparan y quedan ordenados.
        */
        int pivot = particion(A,l,r);

        // Recursiones con pivotes tanto al inicio como al final del arreglo
        sortVector(A,l, pivot - 1);
        sortVector(A, pivot + 1, r);
    }
}


int main(int argc, char* argv[])
{
	string sline;
	int index;

	vector<vector<string>> matriz;
	vector<string> datos;
	string meses[12] = {"Jan", "Feb", "Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

	ifstream inFile("bitacora.txt"); 	    //  input file stream
	ofstream outFile("salida.txt");		//	output file stream

	//	Verifica que los archivos se hayan abierto correctamente
	if (inFile.is_open() && outFile.is_open() )
	{	//	Lee linea a linea
		while ( getline(inFile, sline) )
		{

			string numerote;
			string line = sline;

			// Obtiene mes:
			index = line.find(" ");
			string mes = line.substr(0, index);
			numerote += monthToNum(mes, meses);

			//	Obtiene dia
			line = line.substr(index+1);
			index = line.find(" ");
			string dia = line.substr(0, index);
			numerote += addZeros(stoi(dia), 2);  

			//	Obtiene hora 
			line = line.substr(index+1);
			string hora = line.substr(0, 8);
			numerote += removeDots(hora);

			// Remove initial zero if present in numerote
			if(numerote[0] == '0'){
				numerote = numerote.substr(1);
			}

			vector<string> appendedElem = {numerote, sline};

			matriz.push_back(appendedElem);
			datos.push_back(numerote);
		}
	}

	// ordenar vector datos
	sortVector(datos, 0, datos.size() - 1);

	for(int i = 0; i < datos.size(); i++)
	{
		for(int j = 0; j < matriz.size(); j++)
		{
			if(datos[i] == matriz[j][0])
			{
				outFile << matriz[j][1] << endl;
			}
		}
	}
	inFile.close();
	outFile.close();
}
