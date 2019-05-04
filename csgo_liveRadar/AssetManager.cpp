#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include <map>
#include <string>

AssetManager::AssetManager() 
{}
AssetManager::~AssetManager()
{}

bool AssetManager::loadTexture(std::string name, std::string fileName) {
	sf::Texture tex;

	if (!tex.loadFromFile(fileName)) {
		return false;
	}
	textures[name] = tex;

	return true;
}
sf::Texture& AssetManager::getTexture(std::string name) {
	return textures.at(name);
}
bool AssetManager::loadFont(std::string name, std::string fileName) {
	sf::Font font;

	if (!font.loadFromFile(fileName)) {
		return false;
	}
	fonts[name] = font;

	return true;
}
sf::Font& AssetManager::getFont(std::string name) {
	return fonts.at(name);
}
bool AssetManager::loadImage(std::string name, std::string fileName) {
	sf::Image img;

	if (!img.loadFromFile(fileName)) {
		return false;
	}
	images[name] = img;

	return true;
}
sf::Image& AssetManager::getImage(std::string name) {
	return images.at(name);
}