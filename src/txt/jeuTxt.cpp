
#include "jeuTxt.h"




    JeuTxt::JeuTxt(){
        // Partie initialisée avec le niveau par défaut
    }

    

    void JeuTxt::afficher() {
        // Affiche le niveau avec la position actuelle du joueur
        
        Vec2 playerPos = partie.getPlayer().getPos();

        for (int y = 0; y < niveau.getHeight(); ++y) {
            for (int x = 0; x < niveau.getWidth(); ++x) {
                if (x == niveau.getWidth() && y == niveau.getHeight()) {
                    std::cout << 'P'; // Affiche le joueur
                } else {
                    std::cout << niveau.getCase(x, y); // Affiche les autres cases
                }
            }
            std::cout << std::endl;
        }
    }

    void JeuTxt::boucleDeJeu() {
        bool running = true;
        bool update = false;
        afficher();
        while (running) {
                char key;
                cin >> key;
                if(update)
                    afficher();  
                if (key == 033) {
                    running = false; // Quitter le jeu si 'echap' est appuyé
                } else {
                    partie.handleInput(key, niveau); // Gérer l'entrée utilisateur
                    update = true;
                }
            

            // Mettre à jour la gravité et l'état du joueur
            
        


    
}
} 

