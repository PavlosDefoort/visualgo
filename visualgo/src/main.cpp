
#include <SFML/Graphics.hpp>

#include<iostream>
#include <thread>
#include <future>


#include "Constants.h"
#include "Settings.h"
#include "Visualizer.h"
#include "SoundPlayer.h"
#include "Element.h"
#include "Sidebar.h"
#include "SortingAlgorithms.h"




const unsigned int SAMPLE_RATE = 44100;
int main()
{

	
	
	// create a window & settings
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 32), "visualgo", sf::Style::Fullscreen);
	window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(true);


	Settings settings(50, Merge);
	Visualizer visualizer(settings, window);
	SoundPlayer soundplayer;



	visualizer.Randomize();

	Sidebar sidebar(settings, window);

	auto future = std::async(std::launch::async, [&visualizer,&soundplayer]() 
	{
		
			SortingAlgorithms::SelectionSort(visualizer.GetElements(), soundplayer);

	});


	// while the window is kept open
	while (window.isOpen())
	{
		// store and loop through each event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// if closing window
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

				break;
			}
		}

		// clear frame
		window.clear(sf::Color(20, 20, 20));

		// update
		sidebar.Update(window);


		visualizer.UpdateElements();

		// render
		visualizer.Render(window);
		sidebar.Render(window);

		// show frame / draw calls
		window.display();
	}

	return 0;
}