#include "Entity.h"
#include <SFML\Graphics.hpp>

#ifndef ACTOR_H
#define ACTOR_H

class Actor :public Entity
{
	sf::Texture Anim_Frames[10];
	int no_of_frames;
	int i;
	sf::Texture jump_tex;
public:
	float x_velocity;
	float y_velocity;
	Actor(sf::Vector2f pos, sf::Texture &tex);
	void add_Frame(sf::Texture &tex);
	void advance_Anim();
	void reset_Anim();
	void set_jump_texture(sf::Texture &tex);
	void invoke_jump_texture();
};

#endif ACTOR_H