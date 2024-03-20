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
#include "mouton.cpp"

class Loups{
	protected:
		int posX;
		int posY;
		bool sexe; // true = mâle, false = femelle
	
	public:
		Loups(int posX,int posY);
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
        void printX();
		void printY();
        int vie = 60;
		int faim = 10;
		bool est_mort = false;
		void deplacement(std::vector<std::vector<std::vector<char>>>& matrix);
		void supp_Loups(std::vector<std::vector<std::vector<char>>>& matrix);
		void mange(std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_moutons);
		bool getSexe();
        bool LoupAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Loups>& NB_Loups);
        Loups* getLoupAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Loups>& NB_Loups);
        bool MoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_moutons);
		Moutons* getMoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_Moutons);
        void loup_Etat(std::vector<Loups>& NB_Loups, std::vector<std::vector<std::vector<char>>>& matrix);
        void reproduction(std::vector<std::vector<std::vector<char>>>& matrix, std::vector<Loups>& NB_Loups);
};

Loups::Loups(int x,int y){
    posX = x;
	posY = y;

	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    sexe = dist(gen) == 1;
}

void Loups::setX(int x){
	this->posX = x;
}

void Loups::setY(int y){
	this->posY = y;
}

void Loups::printX(){
	std::cout << static_cast<char>('A' + posX);
}

void Loups::printY(){
	std::cout<< posY+1;
}

int Loups::getX(){
	return this->posX;
}

int Loups::getY(){
	return this->posY;
}

bool Loups::getSexe(){
        return this->sexe;
}

void Loups::supp_Loups(std::vector<std::vector<std::vector<char>>>& matrix){
	matrix[this->posX][this->posY][2] = ' ';
	matrix[this->posX][this->posY][3] = 'S';
}

void Loups::deplacement(std::vector<std::vector<std::vector<char>>>& matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Parcourir toute la grille
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Si la case contient le mouton
            if (i == this->posX && j == this->posY) {
                // Générer un nombre aléatoire entre 0 et 8
                int rand_num = rand() % 9;
                int new_i = i;
                int new_j = j;
                // Calculer les indices de la case adjacente correspondante
                if (rand_num == 0) {
                    new_i = i - 1;
                    new_j = j - 1;
					rand_num = 8;
                } else if (rand_num == 1) {
                    new_i = i - 1;
					rand_num = 8;
                } else if (rand_num == 2) {
                    new_i = i - 1;
                    new_j = j + 1;
					rand_num = 8;
                } else if (rand_num == 3) {
                    new_j = j - 1;
					rand_num = 8;
                } else if (rand_num == 4) {
                    new_j = j + 1;
					rand_num = 8;
                } else if (rand_num == 5) {
                    new_i = i + 1;
                    new_j = j - 1;
					rand_num = 8;
                } else if (rand_num == 6) {
                    new_i = i + 1;
					rand_num = 8;
                } else if (rand_num == 7) {
                    new_i = i + 1;
                    new_j = j + 1;
					rand_num = 8;
                } // si rand_num == 8, ne rien faire (ne pas bouger)

                // Vérifier que les nouveaux indices ne sortent pas de la grille
                if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols) {
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[new_i][new_j][2] != 'L') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[new_i][new_j][2] = 'L';
						this->setX(new_i);
						this->setY(new_j);
                        matrix[i][j][2] = ' '; // la case d'origine devient vide
						return;
                    }
                }
            }
        }
    }
}

Moutons* Loups::getMoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_moutons){
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Vérifier les 8 cases adjacentes
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Exclure la case actuelle du mouton
            if (dx == 0 && dy == 0) {
                continue;
            }

            int newPosX = this->posX + dx;
            int newPosY = this->posY + dy;

            // Vérifier si les nouvelles coordonnées sont valides
            if (newPosX >= 0 && newPosX < rows && newPosY >= 0 && newPosY < cols) {
                // Vérifier si la case adjacente contient un mouton
                if (matrix[newPosX][newPosY][1] == 'M') {
                    return &NB_moutons[matrix[newPosX][newPosY][0]]; // Retourne l'objet mouton adjacent
                }
            }
        }
    }
    return nullptr;
}

bool Loups::MoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_moutons){
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Vérifier les 8 cases adjacentes
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Exclure la case actuelle du mouton
            if (dx == 0 && dy == 0) {
                continue;
            }

            int newPosX = this->posX + dx;
            int newPosY = this->posY + dy;

            // Vérifier si les nouvelles coordonnées sont valides
            if (newPosX >= 0 && newPosX < rows && newPosY >= 0 && newPosY < cols) {
                // Vérifier si la case adjacente contient un mouton
                if (matrix[newPosX][newPosY][1] == 'M') {
                    return true;
                }
            }
        }
    }

    return false; // Aucun mouton adjacent
}

void Loups::mange(std::vector<std::vector<std::vector<char>>>& matrix, std::vector<Moutons>& NB_moutons){
    
    if(matrix[this->posX][this->posY][1] == 'M'){
		matrix[this->posX][this->posY][1] = ' ';
        for (int i = 0; i < NB_moutons.size(); i++){
            if(NB_moutons[i].getX()==this->posX && NB_moutons[i].getY()==this->posY){
                NB_moutons[i].est_mange = true;
                this->faim = 10;
            }
        }
		
	}
	else{
		return;
    }
}

void Loups::loup_Etat(std::vector<Loups>& NB_Loups, std::vector<std::vector<std::vector<char>>>& matrix){
    if (this->faim < 0 || this->vie <=  0){
		this->est_mort = true;
	}
    if (this->est_mort) {
		std::cout << "Le loup place [";
		this->printX();
		this->printY();
		std::cout << "] est mort de faim." << std::endl;
				
		// Si le Mouton est mort
		// Supprime l'élément correspondant du vector NB_moutons

		for (int i = 0; i < NB_Loups.size(); i++){
            if (NB_Loups[i].posX == this->posX && this->posY == NB_Loups[i].posY){
                this->supp_Loups(matrix);
				NB_Loups.erase(NB_Loups.begin() + i);
                return;
            }
        }
	}

}

bool Loups::LoupAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Loups>& NB_Loups){
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Vérifier les 8 cases adjacentes
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Exclure la case actuelle du mouton
            if (dx == 0 && dy == 0) {
                continue;
            }

            int newPosX = this->posX + dx;
            int newPosY = this->posY + dy;

            // Vérifier si les nouvelles coordonnées sont valides
            if (newPosX >= 0 && newPosX < rows && newPosY >= 0 && newPosY < cols) {
                // Vérifier si la case adjacente contient un mouton
                if (matrix[newPosX][newPosY][2] == 'L') {
                    return true;
                }
            }
        }
    }

    return false; // Aucun mouton adjacent
}

Loups* Loups::getLoupAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Loups>& NB_Loups){
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Vérifier les 8 cases adjacentes
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Exclure la case actuelle du mouton
            if (dx == 0 && dy == 0) {
                continue;
            }

            int newPosX = this->posX + dx;
            int newPosY = this->posY + dy;

            // Vérifier si les nouvelles coordonnées sont valides
            if (newPosX >= 0 && newPosX < rows && newPosY >= 0 && newPosY < cols) {
                // Vérifier si la case adjacente contient un mouton
                if (matrix[newPosX][newPosY][2] == 'L') {
                    return &NB_Loups[matrix[newPosX][newPosY][0]]; // Retourne l'objet mouton adjacent
                }
            }
        }
    }
    return nullptr;
}

void Loups::reproduction(std::vector<std::vector<std::vector<char>>>& matrix, std::vector<Loups>& NB_Loups) {
    if (Loups::LoupAdjacent(matrix, NB_Loups)) {
        Loups* AutreL = Loups::getLoupAdjacent(matrix, NB_Loups);

        if (this->sexe != AutreL->sexe) {
            std::vector<std::pair<int, int>> positions = {
                { -1, -1 }, { -1, 0 }, { -1, 1 },
                { 0, -1 },              { 0, 1 },
                { 1, -1 },   { 1, 0 },  { 1, 1 }
            };

            for (const auto& pos : positions) {
                int newX = this->posX + pos.first;
                int newY = this->posY + pos.second;

                if (newX >= 0 && newX < matrix.size() && newY >= 0 && newY < matrix[0].size() && matrix[newX][newY][1] == ' ') {
                    matrix[newX][newY][1] == 'M';
                    NB_Loups.push_back(Loups(newX, newY));
                    std::cout << "Un loup est né en " << '[' << static_cast<char>('A' + newX) << newY << ']' << std::endl;
                    //std::this_thread::sleep_for(std::chrono::seconds(3));
                    return;
                }
            }
        }
    }
}