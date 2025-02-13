#ifndef _TEXTUREMANAGER
#define _TEXTUREMANAGER
#include <raylib.h>
#include <string>
#include <unordered_map>

class TextureManager{
public:
	TextureManager();
	~TextureManager();
	Texture2D& getTexture(const std::string& textureName);
	int loadTexture(const std::string& textureName);
	void unloadTexture(const std::string& textureName);
	void unloadAllTextures();
	void drawTexture(const std::string& textureName, const float& posX, const float& posY);

private: 
	std::unordered_map<std::string, Texture2D> textures;
};

#endif
