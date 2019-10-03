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
 
vector<vector<unsigned long int>> TransposerMatrice(vector<vector<unsigned long int>> matriceATransposer)
{
    int largeurDeMatrice = matriceATransposer.size();
    int hauteurDeMatrice = matriceATransposer.at(0).size();

    vector<vector<unsigned long int>> matriceTranspose;

    for (int i = 0; i < largeurDeMatrice; i++)
    {
        for (int j = 0; j < hauteurDeMatrice ; j++)
        {
            matriceTranspose.at(j).at(i) = matriceATransposer.at(i).at(j);
        }
    }
   
    return matriceTranspose;
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
vector<vector<unsigned long int>> LireMatrice(int largeurDeMatrice, int hauteurDeMatrice, int nbrIteration, ifstream &fichierDeMatrices) {
    vector<vector<unsigned long int>> matriceTemporaire;

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

            unsigned long int nombre = strtoul(nombreEnString.c_str(), NULL, 0);

            matriceTemporaire[i][j] = nombre;

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

void EcrireMatricesDansFichierTexte( vector<vector<vector<unsigned long int>>> vecteurDeMatrices, string nomFichier)
{
    ofstream fichierMatrices;
    fichierMatrices.open(nomFichier.c_str(), ofstream::binary);
    
    int largeurDeMatrice = vecteurDeMatrices.at(0).at(0).size();
    int hauteurDeMatrice = vecteurDeMatrices.at(0).size();

    for(int h=0; h<vecteurDeMatrices.size();h++)
    {
        for (int i = 0; i < hauteurDeMatrice; i++)
        {
        
            for (int j = 0; j < largeurDeMatrice; j++)
            {
                fichierMatrices<<vecteurDeMatrices.at(h).at(i).at(j)<<" ";
            }
            fichierMatrices << endl;
        }
        fichierMatrices<<endl;
    }
        
    fichierMatrices.close();

}


void ChargerMatricesEnMemoireEtLesTransposer(int largeurDeMatrices, int hauteurDeMatrice, int nombreDeMatrices, string nomDuFichierDeMatrices)
{
    ifstream fichierDeMatrices;
    fichierDeMatrices.open(nomDuFichierDeMatrices.c_str());

    vector<vector<vector<unsigned long int>>> vecteurDeMatrices;
    vector<vector<vector<unsigned long int>>> vecteurDeMatricesTransposees;
    //int matriceTemporaire [largeurDeMatrices][hauteurDeMatrice];

    for(int i = 0; i < nombreDeMatrices; i++) {

        vector<vector<unsigned long int>> matrice = LireMatrice(largeurDeMatrices, hauteurDeMatrice, i, fichierDeMatrices);
        vecteurDeMatrices.insert(vecteurDeMatrices.begin(), matrice);

        vector<vector<unsigned long int>> matriceTransposee = TransposerMatrice(matrice);
        vecteurDeMatricesTransposees.insert(vecteurDeMatricesTransposees.begin(), matriceTransposee);


    }

    EcrireMatricesDansFichierTexte(vecteurDeMatricesTransposees, "mat_transp.txt");

    


}



int main() {

    RemplirFichier(100, 200, 1024, 500);
    ChargerMatricesEnMemoireEtLesTransposer(100, 200, 1024, "mat_input.txt");


    return 0;
}
