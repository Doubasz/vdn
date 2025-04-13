#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "Jeu.h"

void txtAff(WinTXT &win, Jeu &jeu)
{
	std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();
	Player &player = jeu.getCurrentLevel().getPlayer();
	std::vector<Ennemy> &ennemies = jeu.getCurrentLevel().getEnnemies();

	win.clear();

	// Affichage des murs et des pastilles
	for (int x = 0; x < gameMap[0].size(); ++x){
        for (int y = 0; y < gameMap.size(); ++y){
                char c;
                /*switch(gameMap[y][x]){
                    case SANDBLOCK:
                        c = '#';
                        break;
                    case AIR:
                        c = ' ';
                        break;
                    default:
                        c = '?';
                        break;
                }*/
				if(gameMap[y][x] != NONE && gameMap[y][x] != ENNEMY){
					c = '#';
				}
				else{
					c = ' ';
				}

               win.print(x, y, c);      
        }
    }
		
    Rectangle playerPos = player.getBox();
	win.print(playerPos.x, playerPos.y, 'P');

	Rectangle atkBox = player.getAttackHitBox();
	win.print(atkBox.x, atkBox.y, 'A');
	
    for(const Ennemy& e : ennemies){
        win.print(e.getPos().x, e.getPos().y, 'E');
    }
	

	win.draw();
}


void txtBoucle(Jeu &jeu)
{
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)

    std::vector<std::vector<int>> tileMap = jeu.getCurrentLevel().getTileMap();

    if (tileMap.empty() || tileMap[0].empty()) {
        std::cerr << "Error: Game tile map is empty or invalid.\n";
        return;
    }

	WinTXT win(tileMap[0].size(), tileMap.size());

	bool ok = true;
	int c;

	do
	{
		txtAff(win, jeu);

#ifdef _WIN32
		Sleep(100);
#else
		usleep(100000);
#endif // WIN32

		std::string input = "";

		c = win.getCh();
        input = c;

		switch (c)
		{
		case '=':
			ok = false;
			break;
		}

        jeu.getCurrentLevel().deroulementLevel(input, 0.05);

		Player &player = jeu.getCurrentLevel().getPlayer();
		Rectangle playerRect = player.getBox();

		float playerCenterX = (playerRect.x + (playerRect.w / 2));
		float playerCenterY = (playerRect.y + (playerRect.h / 2));

		win.camera.update(playerCenterX, playerCenterY);

	} while (ok);
}
