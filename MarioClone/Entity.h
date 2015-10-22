#include <SFML/Graphics.hpp>

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
	int id;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	sf::Vector2f getposition();
	void move(sf::Vector2f offset);
	Entity(sf::Vector2f pos, sf::Texture &tex, float xh = 0, float yh = 0, int xid = 0);
	Entity();
	bool check_collision(Entity entity);
	sf::Sprite getSprite();
	bool faceright;
	int ret_id();
};

#endif ENTITY_H