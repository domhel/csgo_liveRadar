#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Player.hpp"
#include <vector>
#include <string>
#include "Map.hpp"
#include <iostream>

dh::Map::Map(std::string name) : name(name) 
{
	// Load and Set Image Texture
	if (!assets.loadImage("Map Image", "res/" + name + "_radar.png"))
		std::cout << "Load from image error" << std::endl;
	tex.loadFromImage(assets.getImage("Map Image"));
	image.setTexture(tex);
	// End Texture Loading

	// Read Map Bounds
	FILE * fp = nullptr;
	std::string fnameBounds = "res/bounds_" + name + ".txt";
	std::cout << fnameBounds << std::endl;
	fopen_s(&fp, fnameBounds.c_str(), "r");
	int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
	if (fp != nullptr)
		fscanf_s(fp, "%d %d\n%d %d", &xmin, &xmax, &ymin, &ymax);
	std::cout << xmin << std::endl;
	std::cout << xmax << std::endl;
	std::cout << ymin << std::endl;
	std::cout << ymax << std::endl;
	if (fp != nullptr)
		fclose(fp);
	bounds = sf::IntRect(xmin, ymin, xmax - xmin, ymax - ymin);
	// End Bounds

	// Scale Image to Match its Size to CSGO Coordinates
	image.setPosition((float)xmin, (float)ymin);
	image.setScale(
		(xmax - xmin) / image.getLocalBounds().width,
		(ymax - ymin) / image.getLocalBounds().height
	);
	// End Scaling
}