
#include "Window.h"
#include "Game.h"
#include "Player.h"
#include "Ball.h"

#include <SDL.h>

//https://www.reddit.com/r/gamedev/comments/4cfvaw/im_tired_of_low_effort_video_tutorials_lets_share/

int main(int argc, char* args[]) 
{
	Window window(700, 700);
	Game game(window);
	Player player(game);
	Ball ball(player);

	SDL_Event e;
	//Game loop
	while (!game.isGameOver())
	{
		//Listen for events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				game.endGame();
			}
		}

		game.inputManager(player, game, ball);
		game.update(game, player, ball);
		game.render(player, ball, window);

	}

	return 0;
}

//Player movement(