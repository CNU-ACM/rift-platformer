#include "game_state.h"
#include "title_screen_state.h"

int main()
{
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 32;
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Rift Platformer", sf::Style::Default, contextSettings);
	window.setActive();

	game_state* mainState = new game_state(&window);
	mainState = (game_state*)(new title_screen(&window));

	while (window.isOpen())
	{
		mainState->Update();
	}

	return EXIT_SUCCESS;
}
