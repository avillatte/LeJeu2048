#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>

const int TAILLE = 4;

class Jeu2048;

class Plateau {
private:
    int score;
    int nbCoups;
    Jeu2048* leJeu;

public:
    Plateau(Jeu2048* jeu);
    void Afficher();
    void CalculezScore();
    bool JouerCoup();
};

class Jeu2048 {
private:
    int grille[TAILLE][TAILLE];

public:
    enum ETATS_DU_JEU { EN_COURS, PERDU, GAGNE };
    Jeu2048();
    void ObtenirGrille(int _grille[][TAILLE]);
    void PlacerNouvelleTuile();
    void Deplacer(char _direction);
    bool Calculer();
    ETATS_DU_JEU RechercherFinDePartie();
};

// Definitions of Plateau methods
Plateau::Plateau(Jeu2048* jeu) : score(0), nbCoups(0), leJeu(jeu) {}

void Plateau::Afficher() {
    int laGrille[TAILLE][TAILLE];
    system("clear");
    leJeu->ObtenirGrille(laGrille);
    std::cout << "| Score: " << score << " | Nombre de coups: " << nbCoups << " |" << std::endl;
    std::cout << std::endl;
    for (int ligne = 0; ligne < TAILLE; ligne++) {
        std::cout << "   +";
        for (int indice = 0; indice < TAILLE; indice++)
            std::cout << std::setw(7) << std::setfill('-') << '+';
        std::cout << std::endl;

        std::cout << std::setw(2) << "|";
        for (int colonne = 0; colonne < TAILLE; colonne++) {
            if (laGrille[ligne][colonne] != 0) {
                std::cout << std::setw(6) << laGrille[ligne][colonne] << "|";
            } else {
                std::cout << std::setw(7) << "|";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "   +";
    for (int indice = 0; indice < TAILLE; indice++)
        std::cout << std::setw(7) << std::setfill('-') << '+';
    std::cout << std::endl;
}

void Plateau::CalculezScore() {
    int totalScore = 0;
    int laGrille[TAILLE][TAILLE];
    leJeu->ObtenirGrille(laGrille);
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            totalScore += laGrille[i][j];
        }
    }
    score = totalScore;
}

bool Plateau::JouerCoup() {
    bool retour = false;
    char touche;
    std::cin >> touche;
    touche = std::toupper(touche);

    if (std::strchr("BHGD", touche) != nullptr) {
        leJeu->Deplacer(touche);
        leJeu->PlacerNouvelleTuile();
        CalculezScore();
        return true;
    }

    if (touche == 'F') {
        retour = true;
    }

    return retour;
}


Jeu2048::Jeu2048() {

    std::memset(grille, 0, sizeof(grille));
    std::srand(std::time(nullptr));
    PlacerNouvelleTuile();
    PlacerNouvelleTuile();
}

void Jeu2048::ObtenirGrille(int _grille[][TAILLE]) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            _grille[i][j] = grille[i][j];
        }
    }
}

void Jeu2048::PlacerNouvelleTuile() {
    int ligne, colonne;
    do {
        ligne = std::rand() % TAILLE;
        colonne = std::rand() % TAILLE;
    } while (grille[ligne][colonne] != 0);

    grille[ligne][colonne] = (((std::rand() % 2) + 1) * 2);
}

void Jeu2048::Deplacer(char _direction) {
    for (int ligne = 0; ligne < TAILLE; ligne++) {
        for (int colonne = 0; colonne < TAILLE - 1; colonne++) {
            if (grille[ligne][colonne] == 0) {
                grille[ligne][colonne] = grille[ligne][colonne + 1];
                grille[ligne][colonne + 1] = 0;
            }
        }
    }
}

bool Jeu2048::Calculer() {

    return false; // Placeholder
}

Jeu2048::ETATS_DU_JEU Jeu2048::RechercherFinDePartie() {


    return EN_COURS; // Placeholder
}

int main() {
    Jeu2048 jeu;
    Plateau plateau(&jeu);

    while (true) {
        plateau.Afficher();
        plateau.CalculezScore();  // Update score before checking game over condition
        if (jeu.RechercherFinDePartie() != Jeu2048::EN_COURS) {
            // Game over, print message and break
            std::cout << "Game over!" << std::endl;
            break;
        }

        if (plateau.JouerCoup()) {
            // Player pressed 'F', exit the game
            std::cout << "Game ended by user." << std::endl;
            break;
        }
    }

    return 0;
}
