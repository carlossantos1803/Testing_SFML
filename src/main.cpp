//sfml-dev.org

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector> 
#include <cmath>
#include "Vec2.h"


struct Properties
{
	std::string name;
	int id;
	float mass;
	Vec2 oldPos;
	Vec2 pos;
	Vec2 velocity;
	int r,g,b;
	Properties(std::string _name,int _id, float _mass, Vec2 _pos, Vec2 _velocity, int _r, int _g, int _b) :
	name(_name), id(_id), mass(_mass), pos(_pos), velocity(_velocity), r(_r), g(_g), b(_b)
	{}
};

struct CircleObject : Properties
{
	sf::CircleShape circle;
	float radius;

	CircleObject(std::string _name, int _id, float _mass, Vec2 _pos, Vec2 _velocity, int _r, int _g, int _b, float _radius):
	Properties(_name, _id, _mass, _pos,_velocity, _r,_g, _b), radius(_radius) 
	{
		circle.setRadius(radius);
	}
};

class Game
{		
		int mWidth;
		int mHeigth;
		sf::RenderWindow window;
		std::string windowName;
		std::string font; 
		sf::Font myFont;	
		int fontSize, fontR, fontG, fontB;
		sf::FloatRect pos;
		sf::Text name;
		std::vector<CircleObject> circles;
				
		void loadFromFile(const std::string& filename);
		void init(const std::string& filename);

	public:
		//Game() = default;
		Game(const std::string& config);
		void play();
		void render();
		void addCircle(CircleObject& c);
		void energy();
} ;

int main(int argc, char* argv[])
{
	//game.loadFromFile("config.txt");
	Game game("../config.txt");
	//Game game("config.txt");
	//Game game;
	game.play();

	return 0;
}


Game::Game(const std::string& config)
{
	init(config);
}
		
void Game::init(const std::string& filename)
{
	loadFromFile(filename);
	window.create(sf::VideoMode(mWidth,mHeigth), windowName);
	window.setFramerateLimit(60);	

	if(!myFont.loadFromFile(font))//"../fonts/tech.ttf"))
	{
		std::cerr << "Couldn't load font";
		exit(-1);
	}

	name.setFont(myFont);
	name.setCharacterSize(fontSize);
	name.setStyle(sf::Text::Bold);
	name.setFillColor(sf::Color(fontR, fontG, fontB));
}

void Game::loadFromFile(const std::string& filename)
{
	std::ifstream fileIn(filename);
	std::string shape, name;
	Vec2 initialPos;
	Vec2 initialSpeed;
	int r,g,b;
	int id = 1;
	float mass;
	Vec2 size;
	float radius;

	std::cout << " good() = " << fileIn.good();
	std::cout << " eof() = " << fileIn.eof();
	std::cout << " fail() = " << fileIn.fail();
	std::cout << " bad() = " << fileIn.bad() ;
	std::cout << std::endl;
	
	while(fileIn >> shape) //fileIn.good())
	{
		// fileIn >> shape;
		std::cout << shape << std::endl;
		if(shape == "Window")
		{
			fileIn >> windowName;
			fileIn >> mWidth; //  = 800;
			fileIn >> mHeigth; // = 600;
		}

		else if(shape == "Font")
		{
			fileIn >> font >> fontSize >> fontR >> fontG >> fontB;

		}
		
		else if(shape == "Circle")
		{
			fileIn >> name;
			fileIn >> mass;
			fileIn >> initialPos.x >> initialPos.y >> initialSpeed.x >> initialSpeed.y;
			fileIn >> r >> g >> b;
			fileIn >> radius;

			CircleObject c(name, id++, mass, initialPos, initialSpeed, r, g, b, radius);
			addCircle(c);
		}
	}            
}
		
void Game::addCircle(CircleObject& c)
{
	circles.push_back(c);
}

void Game::play()
{	
	for(auto& a : circles)
	{
		a.circle.setFillColor(sf::Color(a.r,a.g,a.b));
		a.circle.setOrigin(a.radius,a.radius);
		a.circle.setPosition(a.pos.x,a.pos.y);
		a.circle.setPointCount(30);
		a.circle.setOutlineThickness(0);
		
	}
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{	
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			if(event.type == sf::Event::KeyPressed)
			{
				std::cout << "Key pressed with code = " << event.key.code << "\n";
			
				if(event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

				if(event.key.code == sf::Keyboard::X)
				{
			
				}
				if(event.key.code == sf::Keyboard::Space)
				{
					render();
				}
			}
		}

		render();	
		
		
		// window.clear();
			
		// for(auto& a : circles)
		// {
		// 	a.pos = {a.pos.x + a.velocity.x, a.pos.y + a.velocity.y};
		// 	for(auto& b : circles)		
		// 	{	
		// 		if(a.id != b.id)
		// 		{
		// 			// std::cout << "a.id " << a.id << "   b.id " << b.id << std::endl;
		// 			float distance = a.pos.distance(b.pos);
		// 			std::cout << "distance: " << distance << std::endl;
		// 			if(distance <= (a.radius + b.radius))
		// 			{
		// 				float overlap = distance - (a.radius + b.radius);
		// 				std::cout << "Overlap: " << overlap << std::endl;
		// 				// Vec2 dist = a.pos - b.pos;
		// 				// dist.normalize(distance);
		// 				// dist *= overlap/2;
		// 				// a.pos -= dist;
		// 				// //b.pos += dist;

		// 				// distance = a.pos.distance(b.pos);
		// 				// dist = a.pos - b.pos;
		// 				// Vec2 Speed = a.velocity - b.velocity;
		// 				// float num = (2*a.mass)*(Speed.dot(dist));
		// 				// float den = (a.mass + b.mass)*(distance*distance);
		// 				// float result = num/den;

		// 				// b.velocity += dist;

		// 				// dist = (a.pos - b.pos);
		// 				// Speed *= -1;
		// 				// num = (2*b.mass)*(Speed.dot(dist));
		// 				// result = num/den;
		// 				// dist *= result;
		// 				// a.velocity += dist;
		// 				// energy();
		// 			}
				
				
		// 		}
		// 	}
		// 	// if((a.pos.x + a.radius) > mWidth)// || a.pos.x < a.radius) 
		// 	// {
		// 	// 	a.velocity.x *= -1;
		// 	// 	a.pos.x = mWidth - a.radius;
		// 	// }
		// 	// else if( a.pos.x < a.radius) 
		// 	// {
		// 	// 	a.velocity.x *= -1;
		// 	// 	a.pos.x = a.radius;
		// 	// }
		// 	// else if((a.pos.y + a.radius) > mHeigth)// || a.pos.y < a.radius)
		// 	// {
		// 	// 	a.velocity.y *= -1;
		// 	// 	a.pos.y = mHeigth - a.radius;
		// 	// }
		// 	// else if( a.pos.y < a.radius)
		// 	// {
		// 	// 	a.velocity.y *= -1;
		// 	// 	a.pos.y = a.radius;
		// 	// }
		// 	if(((int)a.circle.getPosition().x + 2*a.radius) >= mWidth || (int)a.circle.getPosition().x <= 0)
		// 	{ 
		// 		a.velocity.x*= -1.0f;	
		// 	}
		// 	else if(((int)a.circle.getPosition().y + 2*a.radius) >= mHeigth || (int)a.circle.getPosition().y <= 0)
		// 	{
		// 		a.velocity.y *= -1.0f;
		// 	}

		// 	a.circle.setPosition(a.pos.x + a.velocity.x, a.pos.y + a.velocity.y);
		// 	// a.circle.setPosition(a.circle.getPosition().x + a.velocity.x, a.circle.getPosition().y + a.velocity.y);
		// 	//name.setString(a.name);
		// 	//pos = name.getGlobalBounds();
		// 	//name.setPosition(a.circle.getPosition().x + a.velocity.x + a.radius - pos.width/2, a.circle.getPosition().y + a.velocity.y + a.radius - pos.height);

		// 	window.draw(a.circle);
		// 	//window.draw(name);
		// }
		// window.display();
	
	}	
		
}

void Game::energy()
{
  int32_t tmp, result = 0;
  for(auto& a: circles)
  {
    tmp = a.velocity.mag();
    tmp = a.mass*tmp*tmp*0.5;
    result += tmp;    
  }
  std::cout << "Energy: " << result << std::endl;
}

void Game::render()
{
	window.clear();
			
		for(auto& a : circles)
		{
			a.pos = {a.pos.x + a.velocity.x, a.pos.y + a.velocity.y};
			for(auto& b : circles)		
			{	
				if(a.id != b.id)
				{
					// std::cout << "a.id " << a.id << std::endl;
					// float distance = a.pos.distance(b.pos);
					float distance = a.pos.distance(b.pos);
					auto collision = [](CircleObject& c, CircleObject& d)
					{
						return abs(((c.pos.x-d.pos.x)*(c.pos.x-d.pos.x)+(c.pos.y-d.pos.y)*(c.pos.y-d.pos.y))) < ((c.radius+d.radius)*(d.radius+c.radius));
					};
					// std::cout << "distance: " << distance << std::endl;
					if(collision(a,b)) //distance <= (a.radius + b.radius))
					{
						std::cout << "a.id " << a.id << "   b.id " << b.id << std::endl;
						// std::cout << "distance: " << distance << std::endl;
						// std::cout << "(a.radius + b.radius): " << (a.radius + b.radius) << std::endl;
						float overlap = distance - (a.radius + b.radius);
						// std::cout << "Overlap: " << overlap << std::endl;
						// std::cout << "a.pos{" <<a.pos.x << ", " << a.pos.y << "}" << std::endl;
						// std::cout << "b.pos{" <<b.pos.x << ", " << b.pos.y << "}" << std::endl;	
						Vec2 dist = a.pos - b.pos;
						dist.normalize(distance);
						// std::cout << "dist.pos{" <<dist.x << ", " << dist.y << "}" << std::endl;	
						dist *= overlap/2;
						// std::cout << "dist.pos{" <<dist.x << ", " << dist.y << "}" << std::endl;	
						a.pos -= dist;
						b.pos += dist;
						// std::cout << "a.pos{" << a.pos.x << ", " << a.pos.y << "}" << std::endl;	
						// std::cout << "b.pos{" <<b.pos.x << ", " << b.pos.y << "}" << std::endl;	
						
						distance = a.pos.distance(b.pos);
						// std::cout << "distance: " << distance << std::endl;
						overlap = distance - (a.radius + b.radius);
						std::cout << "Overlap: " << overlap << std::endl;
						std::cout << "a.pos{" <<a.pos.x << ", " << a.pos.y << "}" << std::endl;
						std::cout << "b.pos{" <<b.pos.x << ", " << b.pos.y << "}" << std::endl;	
						dist = a.pos - b.pos;
						Vec2 Speed = a.velocity - b.velocity;
						float num = (2*a.mass)*(Speed.dot(dist));
						float den = (a.mass + b.mass)*(distance*distance);
						float result = num/den;
						dist*=result;
						std::cout << "dist.pos{" <<dist.x << ", " << dist.y << "}" << std::endl;	
						
						std::cout << "b.velocity{" <<b.velocity.x << ", " << b.velocity.y << "}" << std::endl;	
						
						b.velocity += dist;
						// std::cout << "a.velocity{" <<a.velocity.x << ", " << a.velocity.y << "}" << std::endl;	
						
						dist = b.pos - a.pos;
						Speed *= -1;
						num = (2*b.mass)*(Speed.dot(dist));
						result = num/den;
						dist *= result;
						std::cout << "dist.pos{" <<dist.x << ", " << dist.y << "}" << std::endl;	
						
						std::cout << "a.velocity{" <<a.velocity.x << ", " << a.velocity.y << "}" << std::endl;	
						
						a.velocity += dist;
						energy();
					}
				
				
				}
			}
			if((a.pos.x + a.radius) > mWidth)// || a.pos.x < a.radius) 
			{
				a.velocity.x *= -1;
				a.pos.x = mWidth - a.radius;
			}
			else if( a.pos.x < a.radius) 
			{
				a.velocity.x *= -1;
				a.pos.x = a.radius;
			}
			else if((a.pos.y + a.radius) > mHeigth)// || a.pos.y < a.radius)
			{
				a.velocity.y *= -1;
				a.pos.y = mHeigth - a.radius;
			}
			else if( a.pos.y < a.radius)
			{
				a.velocity.y *= -1;
				a.pos.y = a.radius;
			}
			// if(((int)a.circle.getPosition().x + 2*a.radius) >= mWidth || (int)a.circle.getPosition().x <= 0)
			// { 
			// 	a.velocity.x*= -1.0f;	
			// }
			// else if(((int)a.circle.getPosition().y + 2*a.radius) >= mHeigth || (int)a.circle.getPosition().y <= 0)
			// {
			// 	a.velocity.y *= -1.0f;
			// }

			a.circle.setPosition(a.pos.x + a.velocity.x, a.pos.y + a.velocity.y);
			
			window.draw(a.circle);
		}
		window.display();
}