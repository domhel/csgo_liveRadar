#pragma once

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	bool loadTexture(std::string name, std::string fileName);
	sf::Texture& getTexture(std::string name);
	bool loadFont(std::string name, std::string fileName);
	sf::Font& getFont(std::string name);
	bool loadImage(std::string name, std::string fileName);
	sf::Image& getImage(std::string name);

private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::Image> images;
};
extern AssetManager assets;