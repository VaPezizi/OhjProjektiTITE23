#include <TextureManager.h>
#include <raylib.h>
#include <iostream>

TextureManager::TextureManager(){
	this->textures = std::unordered_map<std::string, Texture2D>();
}
TextureManager::~TextureManager(){
	unloadAllTextures();
	textures.clear();
}
Texture2D& TextureManager::getTexture(const std::string& textureName){
	if(textures.find(textureName) != textures.end()){
		return textures[textureName];
	}else{
		std::cerr << "ERROR: No texture named: " << textureName << " found!\nReturned empty texture!\n";
		abort();
	}	
}
//Returns -1 on error with loading texture, 1 on succes and 0 if the texture is already loaded
int TextureManager::loadTexture(const std::string& textureName){
	if(textures.find(textureName) == textures.end()){
		textures[textureName] = LoadTexture(textureName.c_str());	
		if(textures[textureName].id > 0 && textures[textureName].width > 0 && textures[textureName].height > 0 && textures[textureName].format > 0 && textures[textureName].mipmaps > 0){
			return -1;
		}else return 1;
	}else return 0;
}
void TextureManager::unloadTexture(const std::string& textureName){
	UnloadTexture(textures[textureName]);
	textures.erase(textureName);
	std::cout << textureName << std::endl;
}
void TextureManager::unloadAllTextures(){
	for(auto& texture : textures){
		UnloadTexture(texture.second);	
	}
	textures.clear();
	//std::cout << "Tere, T:samuli" << std::endl;
}
void TextureManager::drawTexture(const std::string& textureName, const float& posX, const float& posY){
	DrawTexture(textures[textureName], posX, posY, WHITE);
}
