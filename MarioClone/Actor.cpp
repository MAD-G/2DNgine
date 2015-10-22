#include "Actor.h"

Actor::Actor(sf::Vector2f pos, sf::Texture &tex)
{
	sprite.setPosition(pos);
	sprite.setTexture(tex);
	x_velocity = 0;
	y_velocity = 0;
	no_of_frames = 1;
	i = 1;
	Anim_Frames[0] = tex;
	jump_tex = tex;
}

void Actor::add_Frame(sf::Texture &tex)
{
	Anim_Frames[no_of_frames++] = tex;
}

void Actor::advance_Anim()
{
	if (i == no_of_frames)
	{
		i = 1;
	}
	sprite.setTexture(Anim_Frames[i]);
	i++;
}

void Actor::reset_Anim()
{
	i = 1;
	sprite.setTexture(Anim_Frames[0]);
}

void Actor::set_jump_texture(sf::Texture &tex)
{
	jump_tex = tex;
}

void Actor::invoke_jump_texture()
{
	sprite.setTexture(jump_tex);
}