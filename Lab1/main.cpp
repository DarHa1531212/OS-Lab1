#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

/**
* @brief  Génère aléatoirement des nombres et les met dans un fichier de matrices
* @note
* @param  largeurDeMatrice: la largeur de chaque matrice à générer
* @param  hauteurDeMatrice: la hauteur de chaque matrice à générer
* @param  nbredeMatrices: le nombre de matrices à générer
* @param  borneSuperieureDeValeur: les matrces contiendront des nombres entre 1 et la borne supérieure
* @retval retourne 0 si la fonction s'est correctement exectuée
*/

vector<vector<vector<unsigned long int>>> RemplirFichier(int largeurDeMatrice, int hauteurDeMatrice, int nbredeMatrices, int borneSuperieureDeValeur)
{
	vector<vector<vector<unsigned long int>>> vecteurDeMatrices(nbredeMatrices, vector<vector<unsigned long int>>(hauteurDeMatrice, vector<unsigned long int>(largeurDeMatrice)));

	int hauteurTotaleDuFichier = hauteurDeMatrice * nbredeMatrices;

	ofstream mat_input;
	mat_input.open("mat_input.txt");
	for (int numeroDeMatrice = 0; numeroDeMatrice < nbredeMatrices; numeroDeMatrice++)
	{
		for (int ligneDeMatrice = 0; ligneDeMatrice < hauteurDeMatrice; ligneDeMatrice++)
		{
			if (ligneDeMatrice % hauteurDeMatrice == 0 && ligneDeMatrice > 0)
			{

				mat_input << endl;
			}

			for (int coloneDeMatrice = 0; coloneDeMatrice < largeurDeMatrice; coloneDeMatrice++)
			{

				int a = rand() % borneSuperieureDeValeur + 1;
				mat_input << (a) << " ";
				vecteurDeMatrices.at(numeroDeMatrice).at(ligneDeMatrice).at(coloneDeMatrice) = a;
			}
			mat_input << endl;
		}
		mat_input << endl;

	}

	mat_input.close();
	return vecteurDeMatrices;

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

	vector<vector<unsigned long int>> matriceTranspose(hauteurDeMatrice, vector<unsigned long int>(largeurDeMatrice));

	for (int ligneDeMatrice = 0; ligneDeMatrice < largeurDeMatrice; ligneDeMatrice++)
	{
		for (int j = 0; j < hauteurDeMatrice; j++)
		{
			matriceTranspose.at(j).at(ligneDeMatrice) = matriceATransposer.at(ligneDeMatrice).at(j);
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

	vector<vector<unsigned long int >> matriceTemporaire(hauteurDeMatrice, vector<unsigned long int>(largeurDeMatrice));

	unsigned long int nombre;
	for (int j = 0; j < hauteurDeMatrice; j++)
	{

		for (int ligneDeMatrice = 0; ligneDeMatrice < largeurDeMatrice; ligneDeMatrice++)
		{
			fichierDeMatrices >> nombre;

			matriceTemporaire[j][ligneDeMatrice] = nombre;

		}
	}

	return matriceTemporaire;
}

/**
* @brief  calcule de produit matriciel de deux matrices
* @note
* @param  colonnes: le nombre de colonnes dans la matrice
* @param  rangee: le nombre de rangées dans la matrice
* @param  matriceA: la première matrice
* @param  matriceB: la deixième matrice
* @retval la matrice résultante
*/
vector<vector<unsigned long int>> Produit(vector<vector<unsigned long int>> matriceA, vector<vector<unsigned long int>> matriceB)
{
	int case1;
	case1 = 0;
	int i = 0; //compter nombre colonnes matrice1
	int j = 0;

	int largeurMatriceA = matriceA.at(0).size();
	int hauteurMatriceA = matriceA.size();

	int largeurMatriceB = matriceB.at(0).size();
	int hauteurMatriceB = matriceB.size();

	vector<vector<unsigned long int>>matriceC(hauteurMatriceA, vector<unsigned long int>(largeurMatriceB));
	
	int temp;

	for (int k = 0; k < hauteurMatriceA; k++)//nombre ligne matrice1
	{

		for (int l = 0; l < largeurMatriceB; l++)//le nombre de colonnes de la matrice2
		{
			for (int m = 0; m < largeurMatriceA; m++)// le nombre colonnes matrice1
			{

				temp = (matriceA[l][m] * matriceB[m][l]);
				case1 = case1 + temp;
			}
			matriceC[j][i] = case1;
			case1 = 0;
			if (i == (largeurMatriceB - 1))
			{
				i = 0;
			}
			else
			{
				i++;
			}

		}
		j++;
	}

	return matriceC;
}


/**
* @brief  écrit le contenu du vecteur de matrices dans un fichier texte
* @note
* @param  vecteurDeMatrices: contient toutes les matrices
* @param  nomFichier: le nom du fichier dans lequel les matrices seront écrites
* @retval retourne 0 si la fonction s'est bien déroulée
*/
int EcrireMatricesDansFichierTexte(vector<vector<vector<unsigned long int>>> vecteurDeMatrices, string nomFichier)
{
	ofstream fichierMatrices;
	fichierMatrices.open(nomFichier);

	int largeurDeMatrice = vecteurDeMatrices.at(0).at(0).size();
	int hauteurDeMatrice = vecteurDeMatrices.at(0).size();

	for (int h = 0; h<1024; h++)
	{
		for (int i = 0; i < hauteurDeMatrice; i++)
		{

			for (int j = 0; j < largeurDeMatrice; j++)
			{
				fichierMatrices << vecteurDeMatrices[h][i][j] << " ";
			}
			fichierMatrices << endl;
		}
		fichierMatrices << endl;
	}

	fichierMatrices.close();

	return 0;

}


vector<vector<vector<unsigned long int>>> ChargerMatricesEnMemoireEtLesTransposer(int largeurDeMatrices, int hauteurDeMatrice, int nombreDeMatrices, string nomDuFichierDeMatrices)
{
	ifstream fichierDeMatrices;
	fichierDeMatrices.open(nomDuFichierDeMatrices.c_str());

	vector<vector<vector<unsigned long int>>> vecteurDeMatrices;
	vector<vector<vector<unsigned long int>>> vecteurDeMatricesTransposees;
	//int matriceTemporaire [largeurDeMatrices][hauteurDeMatrice];

	for (int i = 0; i < nombreDeMatrices; i++) {

		vector<vector<unsigned long int>> matrice = LireMatrice(largeurDeMatrices, hauteurDeMatrice, i, fichierDeMatrices);
		vecteurDeMatrices.insert(vecteurDeMatrices.end(), matrice);

		vector<vector<unsigned long int>> matriceTransposee = TransposerMatrice(matrice);
		vecteurDeMatricesTransposees.insert(vecteurDeMatricesTransposees.end(), matriceTransposee);


	}

	return vecteurDeMatricesTransposees;


}


/**
* @brief  écrit le contenu du vecteur de matrices dans un fichier texte
* @note
* @param  vecteurDeMatrices: contient toutes les matrices
* @param  nomFichier: le nom du fichier dans lequel les matrices seront écrites
* @retval retourne 0 si la fonction s'est bien déroulée
*/




/**
* @brief  point d'entrée du programme
* @note   les étapes du programmes sont sous forme de fonction dans le main
* @retval retourne 0 si la fonction s'est bien déroulée
*/
int main() {

	vector<vector<vector<unsigned long int>>> vecteurDeMatricesOriginal = RemplirFichier(100, 200, 1024, 500);
	vector<vector<vector<unsigned long int>>>vecteurDeMatricesTransposees = ChargerMatricesEnMemoireEtLesTransposer(100, 200, 1024, "mat_input.txt");

	//vecteur produit matriciel: 1024 matrices de 200 par 200
	vector<vector<vector<unsigned long int>>>vecteurProduitMatriciel1024(1204, vector<vector<unsigned long int>>(200, vector<unsigned long int>(200)));


	EcrireMatricesDansFichierTexte(vecteurDeMatricesTransposees, "mat_transp.txt");


	// on rempli les matrices du vecteur de matrices 200 par 200 des 1024 matrices résultant du premier produit matriciel
	for (int d = 0; d < 1024; d++)
	{
		vecteurProduitMatriciel1024[d]=Produit(vecteurDeMatricesOriginal[d], vecteurDeMatricesTransposees[d]);
		cout << "matrice faite" << endl;
	}
	
	EcrireMatricesDansFichierTexte(vecteurProduitMatriciel1024, "mat_1024.txt");

	return 0;
}