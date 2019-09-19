#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

/*
Function: replit le fichier de matrices avec 1024 matrices de 100 par 200
no input parameters
no return value */
int RemplirFichier(int largeurDeMatrice, int hauteurDeMatrice, int nbredeMatrices, int borneSuperieureDeValeur) {

    int hauteurTotaleDuFichier = hauteurDeMatrice * nbredeMatrices;

    ofstream mat_input;
    mat_input.open("mat_input.txt");

    for (int i = 0; i < hauteurDeMatrice; i++)
    {
        if(i % hauteurDeMatrice == 0 && i > 0) {
            mat_input << endl;
        }
    
        for (int j = 0; j < largeurDeMatrice; j++)
        {
            int a  = rand() % borneSuperieureDeValeur + 1;
            mat_input << (a) << " ";
        }
        mat_input << endl;
    }
    mat_input.close();

    return 0;
}

 /**
  * @brief  cette fonction transpose une matrice
  * @note   
  * @param  Param_Colonne: nbre de colones de la matrice
  * @param  Param_Ligne: nbre de lignes de la matrice
  * @param  transfer[10][10]: matrice de départ
  * @param  transpo[10][10]: matrice transposée
  * @retval retourne 0 si la fonction s'est bien déroulée
  */
 
int TransposerMatrice(int Param_Colonne, int Param_Ligne, int transfer[10][10], int transpo[10][10])
{
    int a;
    int b;
    for (a = 0; a < Param_Ligne; a++)
    {
        for (b = 0; b < Param_Colonne; b++)
        {
            transpo[b][a] = transfer[a][b];
        }
    }
    cout << endl;
    return 0;
}


void ChargerMatriceEnMemoire(int hauteurDeMatrices, int longeurDeMatrice, int nombreDeMatrices, string nomDuFichierDeMatrices)
{
    ifstream fichierDeMatrices;
    fichierDeMatrices.open(nomDuFichierDeMatrices);


}

int main() {

    RemplirFichier(100, 200, 1024, 2000);


    return 0;
}
