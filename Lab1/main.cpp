#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

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
 
int TransposerMatrice(vector<vector<int>> matriceATransposer)
{
    int largeurDeMatrice = matriceATransposer.size();
    int hauteurDeMatrice = matriceATransposer.at(0).size();

    vector<vector<int>> matriceTranspose;

    for (int i = 0; i < largeurDeMatrice; i++)
    {
        for (int j = 0; j < hauteurDeMatrice ; j++)
        {
            matriceTranspose.at(j).at(i) = matriceATransposer.at(i).at(j);
        }
    }
    cout << endl;
    return 0;
}

 /**
  * @brief  lit une matrice du fichier
  * @note   
  * @param  largeurDeMatrice: La largeur de la matrice
  * @param  hauteurDeMatrice: La hauteur de la matrice
  * @param  nbrIteration: Nombre de matrice déjà lues afin de positionner le curseur dans le fichier texte
  * @param  &fichierDeMatrices: Le fichier texte qqui contient les matrices
  * @retval retourne le vecteur qui contient la matrice lue
 */
vector<vector<int>> LireMatrice(int largeurDeMatrice, int hauteurDeMatrice, int nbrIteration, ifstream &fichierDeMatrices) {
    vector<vector<int>> matriceTemporaire;

    int positionCurseur = nbrIteration*hauteurDeMatrice;
    fichierDeMatrices.seekg(positionCurseur, ios::beg);

    for (int i = 0; i < hauteurDeMatrice; i++)
    {
        string ligne; 
        getline(fichierDeMatrices, ligne);

        for (int j = 0; j < largeurDeMatrice; i++)
        {
            //ici a corriger
            int positionEspace = ligne.find(' ');
            string nombreEnString = ligne.substr(0, positionEspace);

            ligne = ligne.substr(positionEspace + 1, (ligne.length() - positionEspace));

            int nombre = stoi(nombreEnString);

            matriceTemporaire.at(j).at(i) = nombre;

        }
    }
    
    return matriceTemporaire;
}

void Produit(int colonne, int rangee, int matriceA[10][10], int matriceB[10][10],int matriceC[10][10])
{
    int case1;
    case1 = 0;
    int y=0; //compter nombre colonne matrice1
    // les 4 prochaines lignes sont à enlever et il faut passer les paramètres ligne et colonne de matA et matB en paramètre de la fonction...
    int colmat1;
    int colmat2;
    int lignemat1;
    int lignemat2;
    colmat1 = colonne;
    colmat2 = rangee;
    lignemat1 = rangee;
    lignemat2 = colonne;
    int temp;
    for (int i = 0; i < lignemat1; i++)//nombre ligne matrice1
    {
    
        for (int j = 0; j < colmat2; j++)//le nombre de colonne de la matrice2
        {
            for (int k = 0; k < colmat1; k++)// le nombre colonne matrice1
            {
                temp= (matriceA[i][k] * matriceB[k][j]);
                case1 = case1 + temp;
            }
            matriceC[i][y] = case1;
            case1 = 0;
            if (y == (colmat2-1))
            {
                y = 0;
            }
            else
                y++;
        }
    }
}


void ChargerMatricesEnMemoireEtLesTransposer(int largeurDeMatrices, int hauteurDeMatrice, int nombreDeMatrices, string nomDuFichierDeMatrices)
{
    ifstream fichierDeMatrices;
    fichierDeMatrices.open(nomDuFichierDeMatrices.c_str());

    list<vector<vector<int>>> listeDeMatrices;
    list<vector<vector<int>>> listeDeMatricesTransposees;
    int matriceTemporaire [largeurDeMatrices][hauteurDeMatrice];

    for(int i = 0; i < nombreDeMatrices; i++) {

        vector<vector<int>> matrice = LireMatrice(largeurDeMatrices, hauteurDeMatrice, i, fichierDeMatrices);
        listeDeMatrices.push_front(matrice);

        //vector<vector<int>> matriceTransposee = TransposerMatrice()


    }



}



int main() {

    RemplirFichier(100, 200, 1024, 2000);
    ChargerMatricesEnMemoireEtLesTransposer(100, 200, 1024, "mat_input.txt");

    return 0;
}
