#ifndef TEXTUREMANAGERCLASS_H
#define TEXTUREMANAGERCLASS_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
public:
    static sf::Texture& getTexture(const std::string& filename) {
        auto& textures = getInstance().textures;
        auto it = textures.find(filename);
        if (it == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile(filename)) {
                throw std::runtime_error("Failed to load texture: " + filename);
            }
            it = textures.emplace(filename, std::move(texture)).first;
        }
        return it->second;
    }

private:
    TextureManager() = default;
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }
    std::unordered_map<std::string, sf::Texture> textures;
};

#endif // TEXTUREMANAGERCLASS_H
