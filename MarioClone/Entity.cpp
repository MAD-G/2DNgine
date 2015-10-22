#include "Entity.h"

sf::Vector2f Entity::getposition()
{
	return sprite.getPosition();
}

void Entity::move(sf::Vector2f offset)
{
	sprite.setPosition(sprite.getPosition() + offset);
}

Entity::Entity(sf::Vector2f pos, sf::Texture &tex, float xh, float yh, int xid)
{
	id = xid;
	texture = tex;
	sprite.setPosition(pos);
	sprite.setTexture(tex);
	faceright = true;
	if (xh != 0 && yh != 0)
	{
		sprite.setScale(sf::Vector2f(xh, yh));
	}
}

Entity::Entity()
{
}

bool Entity::check_collision(Entity entity)
{
	return getSprite().getGlobalBounds().intersects(entity.getSprite().getGlobalBounds());
}

sf::Sprite Entity::getSprite()
{
	sf::Sprite drawer = sprite;

	if (!faceright)
	{
		drawer.setOrigin({ sprite.getLocalBounds().width, 0 });
		drawer.setScale({ -1, 1 });
	}
	return drawer;
}
int Entity::ret_id()
{
	return id;
}