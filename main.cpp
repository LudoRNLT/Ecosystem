#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include "loup.cpp"


/*La fonction createMatrix prend en paramètres le nombre de lignes et le nombre de colonnes de la matrice,
et elle renvoie la matrice créée. La fonction printMatrix est utilisée pour afficher la matrice à l'écran.*/

// Fonction pour créer une matrice 3 dimension de lettres (pouvant contenir plusieurs lettres) de taille variable
std::vector<std::vector<std::vector<char>>> createMatrix(int rows,int cols, int MaxLetter = 4){
	std::vector<std::vector<std::vector<char>>> matrix(rows, std::vector<std::vector<char>>(cols, std::vector<char>(MaxLetter)));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < MaxLetter; ++k) {
                matrix[i][j][k] = ' '; // Initialise chaque case de la matrice avec un espace vide
            }
        }
    }

    return matrix;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// Fonction pour afficher une matrice de lettres
void printMatrix(const std::vector<std::vector<std::vector<char>>>& matrix) {
	char a = 'A';

	//affiche en fonction du nombre de lettres dans k toujours à la même distance pour le visuel

	std::cout << "   ";
	for(int k = 0; k < matrix[0].size(); k++){
		std::cout << "   " << k+1 << "   ";
	}
	std::cout << std::endl;

	std::cout << "  +";
	for(int k = 0; k < matrix[0].size(); k++){
		std::cout << "------+";
	}
	std::cout << std::endl;


    for (int i = 0; i < matrix.size(); ++i) {
		std::cout << a;
			a++;
        for (int j = 0; j < matrix[i].size(); ++j) {
			
			std::cout << " | ";

			std::cout << "\u001b[32m"<< matrix[i][j][0] << "\u001b[0m"; //affiche en vert
				
			std::cout << "\u001b[37m" << matrix[i][j][1] << "\u001b[0m"; //affiche en blanc
			
			std::cout << "\u001b[31m" << matrix[i][j][2] << "\u001b[0m"; //affiche en rouge
			
			std::cout << "\u001b[33m" << matrix[i][j][3] << "\u001b[0m"; //affiche en jaune
				
        }
		std::cout << " | " << std::endl;

		std::cout << "  +";
		for(int k = 0; k < matrix[0].size(); k++){
			std::cout << "------+";
		}
		std::cout << std::endl;
    }
	std::cout << std::endl;
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





// Fonction pour ajouter aléatoirement des lettres dans la matrice
void addRandomLetters(std::vector<std::vector<std::vector<char>>>& matrix, int Nb_M, int Nb_L,std::vector<Moutons>& NB_Moutons,std::vector<Loups>& NB_loups) {
	int rows = matrix.size();
    int cols = matrix[0].size();
	srand(time(NULL));
	int i;

	for (i = 0; i < Nb_M; i++){
		int a = rand() %rows;
		int b = rand() %cols;
		if(matrix[a][b][1] != 'M'){
			matrix[a][b][1] = 'M';
			NB_Moutons.push_back(Moutons(a,b));
		}else {
			i--;
		}
	}

	for (i = 0; i < Nb_L; i++){
		int a = rand() %rows;
		int b = rand() %cols;
		if(matrix[a][b][2] != 'L' && matrix[a][b][1] != 'M'){
			matrix[a][b][2] = 'L';
			NB_loups.push_back(Loups(a,b));
		}else {
			i--;
		}
	}
/*
	for (i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			matrix[i][j][0] = 'H';
		}
	}
*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void changeS(std::vector<std::vector<std::vector<char>>>& matrix){
    	int rows = matrix.size();
    int cols = matrix[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(matrix[i][j][3] == 'S'){
                matrix[i][j][3] = ' ';
                matrix[i][j][0] = 'H';
                std::cout << "De l'herbe à poussée sur la case [";
                std::cout << static_cast<char>('A' + i);
                std::cout<< j+1 << "]" << std::endl;
                
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TourMoutons(std::vector<std::vector<std::vector<char>>>& matrix, std::vector<Moutons>& NB_moutons, int tour){
    for (int i = 0; i < NB_moutons.size(); i++)
		{

			

            NB_moutons[i].mange(matrix);

			/*if (Rep == true && NB_moutons[i].MoutonAdjacent(matrix,NB_moutons) == true){
				std::cout << "Test" << std::endl;
				NB_moutons[i].reproduction(matrix,NB_moutons);
				Rep = false;
			}*/

			std::cout << "Le mouton place [";
			NB_moutons[i].printX();
			NB_moutons[i].printY();
            std::cout << "]" << std::endl;

            NB_moutons[i].deplacement2(matrix);
            std::cout << "S'est déplacé en [";
			NB_moutons[i].printX();
			NB_moutons[i].printY();
            std::cout << "]" << std::endl;
			
            NB_moutons[i].mouton_Etat(NB_moutons,matrix);

			NB_moutons[i].faim -= 1;
            NB_moutons[i].vie -= 1;
			//std::cout << NB_moutons[i].faim << " " << NB_moutons[i].vie << std::endl;
			if (tour%3 == 1 && NB_moutons.size() < (matrix.size() * matrix[0].size()) / 4){
				NB_moutons[i].reproduction(matrix,NB_moutons);
			}
		}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TourLoups(std::vector<std::vector<std::vector<char>>>& matrix, std::vector<Loups>& NB_Loups, std::vector<Moutons>& NB_moutons,int tour){
    for (int i = 0; i < NB_Loups.size(); i++)
		{

			NB_Loups[i].mange(matrix, NB_moutons);

			std::cout << "Le loup place place [";
			NB_Loups[i].printX();
			NB_Loups[i].printY();
            std::cout << "]" << std::endl;


            NB_Loups[i].deplacement(matrix);
            std::cout << "S'est déplacé en [";
			NB_Loups[i].printX();
			NB_Loups[i].printY();
            std::cout << "]" << std::endl;

			if (NB_Loups[i].LoupAdjacent(matrix,NB_Loups) == true && tour%5 == 1 && NB_Loups.size() < (matrix.size() * matrix[0].size()) / 4){
				NB_Loups[i].reproduction(matrix,NB_Loups);
			}

            NB_Loups[i].loup_Etat(NB_Loups,matrix);

			NB_Loups[i].faim -= 1;
            NB_Loups[i].vie -= 1;
			
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {


	/*Dans la fonction main, nous demandons à l'utilisateur de saisir le nombre de lignes et de colonnes souhaité.
Ensuite, nous utilisons la fonction createMatrix pour créer la matrice.
Enfin, nous affichons la matrice à l'aide de la fonction printMatrix.*/

    int rows = 5, cols = 5;
	//demande au user le nombre de ligne et colonne
    std::cout << "Entrez le nombre de lignes : ";
    std::cin >> rows;
    std::cout << "Entrez le nombre de colonnes : ";
    std::cin >> cols;

    std::vector<std::vector<std::vector<char>>> matrix = createMatrix(rows, cols);

    std::cout << "Matrice créée : " << std::endl;

    printMatrix(matrix);//print la matrice vierge





















	int Nb_M = rows, Nb_L = rows;
	//Demande au user le nb de moutons et loups
	std::cout << "Entrez le nombre de moutons : ";
    std::cin >> Nb_M;

	bool a = true;
	//while pour empecher un dépassement avec des try throw catch
	while(a){
		try{
			if (Nb_M > rows * cols - 1 || Nb_M < 1){
				throw 1;
			}
		}
		catch(int Num){
			std::cout << "Le nombre maximal de moutons est de " << rows*cols-1;
			std::cout << "Entrez le nombre de moutons valide: ";
			std::cin >> Nb_M;
			continue;
						
		}
		a = false;
	}

	std::cout << "Entrez le nombre de loups : ";
    std::cin >> Nb_L;
	//Empêche le dépassement et le fait qu'il y est 2 animaux sur une case
	//C'est à dire que moutons + loups ne pourront jamais dépasser le nombre de cases dispos
	a = true;
	
	while(a){
		try{
			if (Nb_L > rows * cols - Nb_M){
				throw 1;
			}
		}
		catch(int Num){
			std::cout << "Le nombre maximal de loups est de " << rows*cols-Nb_M;
			std::cout << "Entrez le nombre de loups valide: ";
			std::cin >> Nb_L;
			continue;
						
		}
		a = false;
	}

	std::vector<Moutons>NB_moutons;
	std::vector<Loups>NB_loups;

	addRandomLetters(matrix, Nb_M, Nb_L,NB_moutons,NB_loups);
	//std::cout << NB_loups.size();
	//std::cout << NB_moutons.size();
	printMatrix(matrix);






















	srand(time(NULL));
    int tour = 1;
	bool RepM = true;
	bool RepL = true;
	while (NB_moutons.size() > 0 || NB_loups.size() > 0){
		std::cout << "tour " << tour << std::endl;

		changeS(matrix);
        TourMoutons(matrix,NB_moutons, tour);
		if(NB_moutons.size() > 0){
			printMatrix(matrix);
		}
		
		TourLoups(matrix,NB_loups,NB_moutons, tour);
		if (NB_loups.size() > 0){
			printMatrix(matrix);
		}
        if(tour == 50){
			break;
		}
        tour += 1;
	}


	//std::cout << NB_loups.size() << " " << NB_moutons.size();
	std::cout << "Grille finale" << std::endl;
    std::cout << "Nombre de tours : " << tour-1 << std::endl;

	printMatrix(matrix);

    return 0;
}

