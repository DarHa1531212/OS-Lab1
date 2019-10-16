#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

vector<vector<vector<unsigned long int>>> vecteurTemporaire;

mutex mtx;

struct Chunk
{
	vector<vector<vector<unsigned long int>>> chunkDeMatrices;
	int noChunk;
};


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
vector<vector<unsigned long int>> LireMatrice(int largeurDeMatrice, int hauteurDeMatrice, int nbrIteration, ifstream& fichierDeMatrices) {

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
vector<vector<unsigned long int>> CalculerProduitMatriciel(vector<vector<unsigned long int>> matriceA, vector<vector<unsigned long int>> matriceB)
{
	int caseActuelle = 0;


	int largeurMatriceA = matriceA.at(0).size();
	int hauteurMatriceA = matriceA.size();

	int largeurMatriceB = matriceB.at(0).size();
	int hauteurMatriceB = matriceB.size();

	vector<vector<unsigned long int>>matriceC(hauteurMatriceA, vector<unsigned long int>(largeurMatriceB));

	int temp;

	for (int i = 0; i < hauteurMatriceA; i++)//nombre ligne matrice1
	{

		for (int j = 0; j < largeurMatriceB; j++)//le nombre de colonnes de la matrice2
		{
			for (int k = 0; k < largeurMatriceA; k++)// le nombre colonnes matrice1
			{

				temp = (matriceA[i][k] * matriceB[k][j]);
				caseActuelle = caseActuelle + temp;
			}
			matriceC[i][j] = caseActuelle;
			caseActuelle = 0;
		}
		
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

	for (int h = 0; h < vecteurDeMatrices.size(); h++)
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



/**
* @brief  écrit le contenu du vecteur de matrices dans un fichier texte
* @note
* @param  vecteurDeMatrices: contient toutes les matrices
* @param  nomFichier: le nom du fichier dans lequel les matrices seront écrites
* @retval retourne 0 si la fonction s'est bien déroulée
*/
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
* @brief  Pour traiter les fragments du vecteur de matrices sur 1, 2 ou 4 threads (selon le nombre de matrices restantes) et les rassembler dans l'ordre dans le vecteur de matrice temporaire (variable globale).
* @note
* @param  nbrThreads: Le nombre de threads qui traitent les matrices dans la fonction.
* @param  noChunk: Le numéro du morceau du vecteur de matrices qui est affecté au thread qui appelé la fonction.
* @param  vecteurProduitMatrice: Contient l'ensemble des matrices qui doivent être traiter par les threads.
* @retval retourne 1 si la fonction s'est bien déroulée
*/
int CalculerChunk(int nbrThreads, int noChunk, vector<vector<vector<unsigned long int>>>vecteurProduitMatrice) {

	int tailleChunk = vecteurProduitMatrice.size() / (nbrThreads * 2);
	Chunk chunk;
	chunk.noChunk = noChunk;
	chunk.chunkDeMatrices = vector<vector<vector<unsigned long int>>>((vecteurProduitMatrice.size() / (nbrThreads * 2)),
		vector<vector<unsigned long int>>((vecteurProduitMatrice.at(0).size()), vector<unsigned long int>(vecteurProduitMatrice.at(0).at(0).size())));


	for (int i = 0; i < tailleChunk; i++)
	{
		//Si l'index d'au moins une des deux matrices impliquées dans l'opération est un multiple de 100, le processus ne fait rien pendant 60 secondes avant de faire l'opération.
		if (((((tailleChunk * noChunk) + i) > 0) && ((((tailleChunk * noChunk) + i) % 100) == 0)) || (((vecteurProduitMatrice.size() - (tailleChunk * noChunk) - i) % 100) == 0))
		{
			this_thread::sleep_for(std::chrono::seconds(60));//Fait dormir le thread ayant franchi la condition du if pendant 1min.

			chunk.chunkDeMatrices.at(i) = CalculerProduitMatriciel(vecteurProduitMatrice.at((tailleChunk * noChunk) + i),
				vecteurProduitMatrice.at(vecteurProduitMatrice.size() - (tailleChunk * noChunk) - i - 1));

		}
		else//Sinon l'opération est effectuée sans sleep.
			chunk.chunkDeMatrices.at(i) = CalculerProduitMatriciel(vecteurProduitMatrice.at((tailleChunk * noChunk) + i),
				vecteurProduitMatrice.at(vecteurProduitMatrice.size() - (tailleChunk * noChunk) - i - 1));

	}

	//Section critique

	//lock_guard essaie de prendre le controle du mutex qu'il recoit, quand le controle sort du scope actuel, le lock_guard est detruit et le mutex est relache
	lock_guard<mutex> guard(mtx);
	int position;
	for (int x = 0; x < tailleChunk; x++)
	{
		position = (tailleChunk * noChunk) + x;
		vecteurTemporaire.at(position) = chunk.chunkDeMatrices.at(x);
	}

	return 1;
}



/**
* @brief  Affectation de morceaux de vecteur de matrices aux threads afin d'effectuer le produits matriciel de la première matrice avec la dernière, la deuxième avec l'avant dernière...
* @note
* @param  vecteurProduitMatrice: contient toutes les matrices
* @retval retourne un vecteur de matrices contenant 2 fois moins de matrice que le vecteur passé en paramètre.
*/
int AffecterMatricesPourProduitMatriciel(int nbrDeThreads, vector<vector<vector<unsigned long int>>>vecteurProduitMatrice)
{
	unsigned long int nombresDeMatrices = vecteurProduitMatrice.size();

	vecteurTemporaire = vector<vector<vector<unsigned long int>>>((nombresDeMatrices / 2),
		vector<vector<unsigned long int>>((vecteurProduitMatrice.at(0).size()), vector<unsigned long int>(vecteurProduitMatrice.at(0).at(0).size())));

	//Switch pour l'initiation de threads en fonction du nombre de matrices restantes
	switch (nbrDeThreads)
	{
		//Possible d'avoir seulement un thread qui execute CalculerChunk.
		case 1:
		{
			std::thread t1([&]() {CalculerChunk(nbrDeThreads, 0, vecteurProduitMatrice); });
			t1.join();
			t1.~thread();//Tue les threads
			break;
		}

		//Impossible de traiter les opérations sur les matrices sur 4 threads, mais il y en a assez pour le faire sur 2 threads
		case 2:
		{
			std::thread t1([&]() {CalculerChunk(nbrDeThreads, 0, vecteurProduitMatrice); });
			std::thread t2([&]() {CalculerChunk(nbrDeThreads, 1, vecteurProduitMatrice); });
			t1.join();
			t2.join();
			t1.~thread();
			t2.~thread();
			break;
		}	

		//Il y a assez de matrices pour affectuer les produits matriciels sur les matrices en utilisant 4threads.
		case 4:
		{
			std::thread t1([&]() {CalculerChunk(nbrDeThreads, 0, vecteurProduitMatrice); });
			std::thread t2([&]() {CalculerChunk(nbrDeThreads, 1, vecteurProduitMatrice); });
			std::thread t3([&]() {CalculerChunk(nbrDeThreads, 2, vecteurProduitMatrice); });
			std::thread t4([&]() {CalculerChunk(nbrDeThreads, 3, vecteurProduitMatrice); });
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t1.~thread();
			t2.~thread();
			t3.~thread();
			t4.~thread();
			break;
		}

	}

	return 1;
}


/**
* @brief  Affiche le temps d'execution ainsi que la matrice finale.
* @note
* @param  matriceFinale: Contient la dernière matrice résultante des opérations de produits matriciels.
* @param  vecteurProduitMatrice: contient toutes les matrices
* @retval Retourne 1 si la fonction s'est exécuté jusqu'à la fin.
*/
int AffichageMatriceFinale(vector<vector<unsigned long int>> matriceFinale)
{
	int compteurLigneAffichage = 0;

	for (int x = 0; x < matriceFinale.size(); x++)
	{
		cout << "\t" << "Ligne" << (x + 1) << "\n\t";
		for (int y = 0; y < matriceFinale.at(0).size(); y++)
		{
			string affichageCase = to_string(y) + ": " + to_string(matriceFinale[x][y]) + " ";
			cout << setw(16) << setiosflags(ios::left) << affichageCase;
			compteurLigneAffichage++;
			if (compteurLigneAffichage == 5)
			{
				cout << "\n\t";
				compteurLigneAffichage = 0;
			}

		}
		cout << "\n\n";
		compteurLigneAffichage = 0;
	}

	return 1;
}




/**
* @brief  point d'entrée du programme
* @note   les étapes du programmes sont sous forme de fonction dans le main
* @retval retourne 0 si la fonction s'est bien déroulée
*/
int main() {
	
	//On met le temps actuel dans la varaible start
	auto start = chrono::system_clock::now();

	vector<vector<vector<unsigned long int>>> vecteurDeMatricesOriginal = RemplirFichier(100, 200, 1024, 500);
	vector<vector<vector<unsigned long int>>>vecteurDeMatricesTransposees = ChargerMatricesEnMemoireEtLesTransposer(100, 200, 1024, "mat_input.txt");

	//vecteur produit matriciel: 1024 matrices de 200 par 200
	vector<vector<vector<unsigned long int>>>vecteurProduitMatriciel(1024, vector<vector<unsigned long int>>(200, vector<unsigned long int>(200)));


	EcrireMatricesDansFichierTexte(vecteurDeMatricesTransposees, "mat_transp.txt");


	// on rempli les matrices du vecteur de matrices 200 par 200 des 1024 matrices résultant du premier produit matriciel
	for (int d = 0; d < 1024; d++)
	{
		vecteurProduitMatriciel[d] = CalculerProduitMatriciel(vecteurDeMatricesOriginal[d], vecteurDeMatricesTransposees[d]);

	}

	EcrireMatricesDansFichierTexte(vecteurProduitMatriciel, "mat_1024.txt");

	//Étape 4b à 4c
	while (vecteurProduitMatriciel.size() != 1) {
		

		//pour la gestion du nombre de thread en fonction du nombre de matrice
		if (vecteurProduitMatriciel.size() >= 8) 
		{
			AffecterMatricesPourProduitMatriciel(4, vecteurProduitMatriciel);
		}
		else if (vecteurProduitMatriciel.size() >= 4) 
		{
				AffecterMatricesPourProduitMatriciel(2, vecteurProduitMatriciel);
		} else 
		{
				AffecterMatricesPourProduitMatriciel(1, vecteurProduitMatriciel);
		}

		vecteurProduitMatriciel = vecteurTemporaire;


		//concaténation de la string du nom du fichier dans lequel on écrit la matrice
		EcrireMatricesDansFichierTexte(vecteurProduitMatriciel, ("mat_" + to_string(vecteurProduitMatriciel.size()) + ".txt"));
	}

	//Affichage matrice fin de programme
	AffichageMatriceFinale(vecteurProduitMatriciel[0]);

	//On met le temps actuel dans la variable end et on fait end-start pour avoir le temps d'execution
	auto end = std::chrono::system_clock::now();
	chrono::duration<double> tempsExecution = end-start;	
	cout << "\t" << "L'execution du devoir1 est termine. Le temps d'execution est de " << tempsExecution.count() << " secondes." << "\n\n\n";


	return 0;
}