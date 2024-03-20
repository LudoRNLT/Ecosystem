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

class Loup;

class Moutons{
	protected:
		int posX;
		int posY;
		bool sexe; // true = mâle, false = femelle
	
	public:
		Moutons(int posX,int posY);
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
        void printX();
		void printY();
        int vie = 50;
		int faim = 5;
		bool est_mange = false;
		bool est_mort = false;
		void deplacement(std::vector<std::vector<std::vector<char>>>& matrix);
        void deplacement2(std::vector<std::vector<std::vector<char>>>& matrix);
		void reproduction(std::vector<std::vector<std::vector<char>>>& matrix, std::vector<Moutons>& NB_Moutons);
        //bool reproductionB = true;
		void supp_Mouton(std::vector<std::vector<std::vector<char>>>& matrix);
		void mange(std::vector<std::vector<std::vector<char>>>& matrix);
		bool getSexe();
        bool MoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_moutons);
		Moutons* getMoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_Moutons);
        void mouton_Etat(std::vector<Moutons>& NB_Moutons, std::vector<std::vector<std::vector<char>>>& matrix);
};

Moutons::Moutons(int x,int y){
	posX = x;
	posY = y;

	std::random_device rd; //bibliothèque random
    std::mt19937 gen(rd()); //générateur de nombres pseudo-aléatoires || Mersenne Twister
    std::uniform_int_distribution<int> dist(0, 1); //Soit 0 soit 1
    sexe = dist(gen) == 1;
}

void Moutons::setX(int x){
	this->posX = x;
}

void Moutons::setY(int y){
	this->posY = y;
}

int Moutons::getX(){
	return posX;
}

int Moutons::getY(){
	return posY;
}

void Moutons::printX(){
	std::cout << static_cast<char>('A' + posX);
}

void Moutons::printY(){
	std::cout<< posY+1;
}

bool Moutons::getSexe(){
        return this->sexe;
}

void Moutons::supp_Mouton(std::vector<std::vector<std::vector<char>>>& matrix){
	matrix[this->posX][this->posY][1] = ' ';
	if (est_mort){
		matrix[this->posX][this->posY][3] = 'S';
	}
}

void Moutons::deplacement(std::vector<std::vector<std::vector<char>>>& matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Parcourir toute la grille
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Si la case contient le mouton
            if (i == this->posX && j == this->posY) {

                int new_i = i;
                int new_j = j;

                // Vérifier les 8 cases adjacentes
                            // Générer un nombre aléatoire entre 0 et 8
                            int rand_num = rand() % 9;
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
                    if (matrix[new_i][new_j][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[new_i][new_j][1] = 'M';
						this->setX(new_i);
						this->setY(new_j);
                        matrix[i][j][1] = ' '; // la case d'origine devient vide
						return;
                    }
                }
            }
        }
    }
}



void Moutons::deplacement2(std::vector<std::vector<std::vector<char>>>& matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();

    
    // CAS 1 COIN EN HAUT A GAUCHE //
    if(this->posX == 0 && this->posY == 0){
        //std::cout << "1" << std::endl;
        for (int dx = 0; dx <= 1; dx++) {
            for (int dy = 0; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    }
                }
            }
        }
    }
    // CAS 2 COIN EN BAS A GAUCHE
    if (this->posX == rows-1 && this->posY == 0){
        //std::cout << "2" << std::endl;
        for (int dx = -1; dx <= 0; dx++) {
            for (int dy = 0; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    }
                }
            }
        }
    }
    //CAS 3 COIN EN HAUT A DROITE
    if (this->posX == 0 && this->posY == cols-1){
        //std::cout <<"3"<< std::endl;
        for (int dx = 0; dx <= 1; dx++) {
            for (int dy = -1; dy <= 0; dy++) {

                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L'){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }
        }
    }
    // CAS 4 COIN EN BAS A DROITE
    if (this->posX == rows - 1 && this->posY == cols - 1){
        //std::cout << "4" << std::endl;
        for (int dx = -1; dx <= 0; dx++) {
            for (int dy = -1; dy <= 0; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    }
                }
            }
        }
    }
    // CAS 5 LIGNE HAUT
    if (this->posX == 0 && this->posY != 0 && this->posY != cols-1){
        //std::cout << "5" << std::endl;
        for (int dx = 0; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    }
                }
            }
        }
    }
    //CAS 6 LIGNE BASSE
    if (this->posX == rows && this->posY != 0 && this->posY != cols-1){
        //std::cout << "6" << std::endl;
        for (int dx = -1; dx <= 0; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    }
                }
            }
        }
    }
    //CAS 7 LIGNE GAUCHE
    if (this->posY == 0 && this->posX != 0 && this->posX != rows - 1){
        //std::cout << "7" << std::endl;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = 0; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    }
                }
            }
        }
    }
    //CAS 8 LIGNE DROITE
    if (this->posY == cols-1 && this->posX != rows - 1 && this->posX != 0){
        //std::cout << "8" << std::endl;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 0; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                    if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                        // Déplacer le mouton vers la case adjacente
                        matrix[this->posX + dx][this->posY + dy][1] = 'M';
                        matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
						this->setX(this->posX + dx);
						this->setY(this->posY + dy);
						return;
                    }
                }
            }
        }
    }
    if (this->posX != 0 && this->posX != rows-1 && this->posY != 0 && this->posY != cols-1){
        //std::cout << "9 et plus" << std::endl;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                // Exclure la case actuelle du mouton
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (matrix[this->posX + dx][this->posY + dy][0] == 'H' && matrix[this->posX + dx][this->posY + dy][2] != 'L' ){
                    if (this->posX + dx >= 0 && this->posX + dx < rows && this->posY + dy >= 0 && this->posY + dy < cols) {
                        // Vérifier que la case adjacente est libre (ne contient pas de mouton)
                        if (matrix[this->posX + dx][this->posY + dy][1] != 'M') {
                            // Déplacer le mouton vers la case adjacente
                            matrix[this->posX + dx][this->posY + dy][1] = 'M';
                            matrix[this->posX][this->posY][1] = ' '; // la case d'origine devient vide
                            this->setX(this->posX + dx);
                            this->setY(this->posY + dy);
                            return;
                        }
                    }   
                }
            }
        }
    }
}

Moutons* Moutons::getMoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_moutons){
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

bool Moutons::MoutonAdjacent(const std::vector<std::vector<std::vector<char>>>& matrix,  std::vector<Moutons>& NB_moutons){
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


void Moutons::reproduction(std::vector<std::vector<std::vector<char>>>& matrix, std::vector<Moutons>& NB_Moutons) {
    if (Moutons::MoutonAdjacent(matrix, NB_Moutons)) {
        Moutons* AutreM = Moutons::getMoutonAdjacent(matrix, NB_Moutons);

        if (this->sexe != AutreM->sexe) {
            std::vector<std::pair<int, int>> positions = {
                { -1, -1 }, { -1, 0 }, { -1, 1 },
                { 0, -1 },             { 0, 1 },
                { 1, -1 }, { 1, 0 }, { 1, 1 }
            };  

            for (const auto& pos : positions) {
                int newX = this->posX + pos.first;
                int newY = this->posY + pos.second;

                if (newX >= 0 && newX < matrix.size() && newY >= 0 && newY < matrix[0].size() && matrix[newX][newY][1] == ' ') {
                    matrix[newX][newY][1] == 'M';
                    NB_Moutons.push_back(Moutons(newX, newY));
                    std::cout << "Un mouton est né en " << '[' << static_cast<char>('A' + newX) << newY << ']' << std::endl;
                    //std::this_thread::sleep_for(std::chrono::seconds(3));
                    return;
                }
            }
        }
    }
}


void Moutons::mange(std::vector<std::vector<std::vector<char>>>& matrix){
	if(matrix[this->posX][this->posY][0] == 'H' && this->faim < 3){
		matrix[this->posX][this->posY][0] = ' ';
		this->faim = 5;
		std::cout << "Le mouton a mangé" << std::endl;
	}
	else{
		return;
	}
}

void Moutons::mouton_Etat(std::vector<Moutons>& NB_moutons, std::vector<std::vector<std::vector<char>>>& matrix){
    if (this->faim < 0 || this->vie <= 0){
		this->est_mort = true;
	}

			if (this->est_mange) {
				std::cout << "Le mouton place [";
				this->printX();
				this->printY();
				std::cout << "] s'est fait manger par un loup." << std::endl;
				
				
				// Si le Mouton a été mangé

				for (int i = 0; i < NB_moutons.size(); i++){
                    if (NB_moutons[i].posX == this->posX && this->posY == NB_moutons[i].posY){
                        this->supp_Mouton(matrix);
				        NB_moutons.erase(NB_moutons.begin() + i);
                        return;
                    }
                }
				
				
				
			}
			else if (this->est_mort) {
				std::cout << "Le mouton place [";
				this->printX();
				this->printY();
				std::cout << "] est mort de faim." << std::endl;
				
				// Si le Mouton est mort
				// Supprime l'élément correspondant du vector NB_moutons

				for (int i = 0; i < NB_moutons.size(); i++){
                    if (NB_moutons[i].posX == this->posX && this->posY == NB_moutons[i].posY){
                        this->supp_Mouton(matrix);
				        NB_moutons.erase(NB_moutons.begin() + i);
                        return;
                    }
                }
			}

}

