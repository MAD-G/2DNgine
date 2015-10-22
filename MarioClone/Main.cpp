#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Actor.h"
#include <iostream>
#include <vector>

#define WIDTH 640
#define HEIGHT 480

sf::Texture pipe,t,tree;
sf::Texture tex1, tex2, tex3, tex4, jump;

void startscreen(sf::RenderWindow &w)
{
	bool enter = false;
	sf::Font font;
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Could not load font\n";
	}
	sf::Text text;
	text.setFont(font);
	text.setPosition(sf::Vector2f(WIDTH/2-300,HEIGHT/2-15));
	text.setCharacterSize(24);
	text.setColor(sf::Color::White);
	text.setString("WELCOME\nUR OBJECTIVE IS TO TOUCH THE TREE OF\n HEAVENLY WISDOM\nPRESS ENTER TO BEGIN");
	w.draw(text);
	w.display();
	sf::Event event;
	while (w.isOpen() && !enter)
	{
		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				w.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					enter = true;
					break;
				}
			}
		}
	}
}
void showvictory(sf::RenderWindow &w)
{
		sf::Font font;
		if (!font.loadFromFile("font.ttf"))
		{
			std::cout << "Could not load font\n";
		}
		sf::Text text;
		text.setFont(font);
		text.setPosition(w.getView().getCenter()-sf::Vector2f(WIDTH/4,0));
		text.setCharacterSize(48);
		text.setColor(sf::Color::White);
		text.setString("Congratulations!\nYou win!");
		w.draw(text);
		w.display();
}
void load_objects(std::vector <Entity> &v)
{
	if (!pipe.loadFromFile("pipe.png") || !t.loadFromFile("t.png") || !tree.loadFromFile("tree.png"))
	{
		std::cout << "One or more textures could not be loaded" << std::endl;
	}
	Entity obj1(sf::Vector2f(100, HEIGHT - 100), pipe);
	Entity obj2(sf::Vector2f(200, HEIGHT - 200), pipe);
	Entity obj3(sf::Vector2f(300, HEIGHT - 300), pipe);
	Entity obj4(sf::Vector2f(200, HEIGHT - 400), pipe);
	Entity obj5(sf::Vector2f(100, HEIGHT - 500), pipe);
	Entity obj6(sf::Vector2f(200, HEIGHT - 600), pipe);
	Entity obj7(sf::Vector2f(300, HEIGHT - 700), pipe);
	Entity tree(sf::Vector2f(300, HEIGHT - 775), tree,1,1,1);
	Entity bottomframe(sf::Vector2f(0, HEIGHT), t);

	v.push_back(obj1);
	v.push_back(obj2);
	v.push_back(obj3);
	v.push_back(obj4);
	v.push_back(obj5);
	v.push_back(obj6);
	v.push_back(obj7);
	v.push_back(tree);
	v.push_back(bottomframe);
}

int main()
{
	std::vector <Entity> objects;
	load_objects(objects);
	if (!tex1.loadFromFile("frame0.png") || !tex2.loadFromFile("frameR1.png") || !tex3.loadFromFile("frameR2.png") || !tex4.loadFromFile("frameR3.png") || !jump.loadFromFile("jump.png"))
	{
		std::cout << "One or more textures could not be loaded" << std::endl;
	}
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mario");
	//sf::RectangleShape marioRect(sf::Vector2f(20.f,50.f));
	//sf::RectangleShape object(sf::Vector2f(30.f, 30.f));
	bool horizontaltouched = false;
	bool verticaltouched = false;
	Actor mario(sf::Vector2f(30, HEIGHT-50), tex1);
	mario.add_Frame(tex2);
	mario.add_Frame(tex3);
	mario.add_Frame(tex4);
	mario.set_jump_texture(jump);
	bool rightkey = false;
	bool leftkey = false;
	bool jumped = false;
	bool won = false;
	sf::View view1(window.getView());
	//float y_velocity = 0;
	sf::Clock timer;
	startscreen(window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					mario.faceright = false;
					leftkey = true;
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					mario.faceright = true;
					rightkey = true;
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					mario.move(sf::Vector2f(0, 10));
					bool collision = false;
					for (int i = 0; i < objects.size(); i++)
					{
						if (mario.check_collision(objects[i]))
							collision = true;
					}
					mario.move(sf::Vector2f(0, -10));
					if (jumped == false && collision==true)
					{
						jumped = true;
						mario.y_velocity = -9;
						mario.invoke_jump_texture();
					}
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					leftkey = false;
					if (!jumped)
					mario.reset_Anim();
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					rightkey = false;
					if (!jumped)
					mario.reset_Anim();
				}
			}
		}
		if (timer.getElapsedTime().asMilliseconds() > 25 && !won)
		{
			mario.move(sf::Vector2f(0, 10));
			bool collision = false;
			for (int i = 0; i < objects.size(); i++)
			{
				if (mario.check_collision(objects[i]))
					collision = true;
			}
			mario.move(sf::Vector2f(0, -10));
			mario.x_velocity = 0;
			bool right,up;
			if (rightkey == true)
			{
				right = true;
				mario.x_velocity = 4;
			}
			else if (leftkey == true)
			{
				right = false;
				mario.x_velocity = -4;
			}
			if ((rightkey || leftkey) && collision)
			{
				mario.advance_Anim();
			}
			mario.y_velocity += 0.3;
			if (mario.y_velocity >= 0)
			{
				up = false;
			}
			else
			{
				up = true;
			}
			mario.move(sf::Vector2f(mario.x_velocity, mario.y_velocity));
			for (int i = 0; i < objects.size(); i++)
			{
				float x_offset, y_offset;
				if (mario.check_collision(objects[i]))
				{
					if (objects[i].ret_id() == 1)
					{
						showvictory(window);
						won = true;
						break;
					}
					mario.move(sf::Vector2f(-mario.x_velocity, -mario.y_velocity));
					if (right)
						x_offset = objects[i].getposition().x - mario.getposition().x - mario.getSprite().getLocalBounds().width;
					else
						x_offset = objects[i].getposition().x - mario.getposition().x + objects[i].getSprite().getLocalBounds().width;
					if (up)
						y_offset = mario.getposition().y - objects[i].getposition().y - objects[i].getSprite().getLocalBounds().height;
					else
						y_offset = mario.getposition().y - objects[i].getposition().y + mario.getSprite().getLocalBounds().height;
					mario.move(sf::Vector2f(mario.x_velocity, 0));

					if (mario.check_collision(objects[i]))
					{
						mario.move(sf::Vector2f(-mario.x_velocity, 0));
						mario.move(sf::Vector2f(x_offset, 0));
						mario.move(sf::Vector2f(0, mario.y_velocity));
					}

					else
					{
						if (jumped == true)
						{
							jumped = false;
							mario.reset_Anim();
						}
						mario.y_velocity = 0;
						mario.move(sf::Vector2f(0, y_offset));

					}
				}
			}
			if (!won)
			{
				view1.setCenter(mario.getposition());
				window.setView(view1);
				window.clear();
				window.draw(mario.getSprite());
				for (int i = 0; i < objects.size(); i++)
					window.draw(objects[i].getSprite());
				window.display();
				timer.restart();
			}
		}
	}
	return 0;
}