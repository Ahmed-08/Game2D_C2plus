#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

using namespace sf;


int width = 400;
int length = 400;
struct Point {
	int x;
	int y;
	Point(int a, int b) :x(a), y(b) {};
};

bool check(std::vector<Point> &v) {

	if (v[v.size() - 1].x < 0 || v[v.size() - 1].x >= 20 || 
		v[v.size() - 1].y < 0 || v[v.size() - 1].y >= 20)	
		return true;
	
	for (int i = 0; i < v.size(); ++i)
		for (int j = i + 1; j < v.size(); ++j)
			if (v[i].x == v[j].x && v[i].y == v[j].y)
				return true;	
	return false;
}

int main() {

	srand(time(0));

	std::vector<Point> snake;
	snake.push_back(Point(0, 0));
	snake.push_back(Point(1, 0));
	snake.push_back(Point(2, 0));

	int fruitX, fruitY;
	bool GameOver = false;
	fruitX = (rand() % 20) * 20;
	fruitY = (rand() % 20) * 20;
	

	RenderWindow window(VideoMode(length, width), "SFML Snake!");
	Texture body, fruit;
	body.loadFromFile("G:\\C++\\VS_project\\introduction_to_sfml\\image\\body.png");
	fruit.loadFromFile("G:\\C++\\VS_project\\introduction_to_sfml\\image\\fruit.jpg");

	Sprite body_sprite(body);
	Sprite fruit_sprite(fruit);

	float timer = 0, delay = 0.3;
	Clock clock;

	while (window.isOpen())
	{
		float itime = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += itime;

		int dx = 0, dy = 0;
		GameOver = check(snake);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Left)dx = -1;
				else if (event.key.code == Keyboard::Right)dx = 1;
				else if (event.key.code == Keyboard::Down)dy = 1;
				else if (event.key.code == Keyboard::Up)dy = -1;

				int i;
				for (i = 0; i < snake.size()-1; ++i)
				{ 
					snake[i].x = snake[i + 1].x;
					snake[i].y = snake[i + 1].y;
				}
				snake[i].x += dx;
				snake[i].y += dy;
			}
		}
		window.clear(Color::Black);
		for (int i = 0; i < snake.size(); i++)
		{
			body_sprite.setPosition(snake[i].x * 20, snake[i].y * 20);
			if (i == snake.size() - 1)
			{
				body_sprite.setColor(Color::Red);
				window.draw(body_sprite);
			}
			else
			{
				body_sprite.setColor(Color::Green);
				window.draw(body_sprite);
			}
		}
		dx = 0;
		dy = 0;
		fruit_sprite.setPosition(fruitX, fruitY);
		window.draw(fruit_sprite);
		
		if (snake[snake.size() - 1].x*20 == fruitX && snake[snake.size() - 1].y*20 == fruitY)
		{
			if(snake[snake.size() - 1].x - snake[snake.size() - 2].x == 1)
				snake.push_back(Point(snake[snake.size() - 1].x + 1, snake[snake.size() - 1].y));
			else if (snake[snake.size() - 1].x - snake[snake.size() - 2].x == -1)
				snake.push_back(Point(snake[snake.size() - 1].x - 1, snake[snake.size() - 1].y));

			else if (snake[snake.size() - 1].y - snake[snake.size() - 2].y == 1)
				snake.push_back(Point(snake[snake.size() - 1].x, snake[snake.size() - 1].y + 1));
			else if (snake[snake.size() - 1].y - snake[snake.size() - 2].y == -1)
				snake.push_back(Point(snake[snake.size() - 1].x, snake[snake.size() - 1].y - 1));

			fruitX = (rand() % 20) * 20;
			fruitY = (rand() % 20) * 20;
		}

		if (timer > delay)
		{
			if (snake[snake.size() - 1].x - snake[snake.size() - 2].x == 1)
			{
				int i;
				for (i = 0; i < snake.size() - 1; ++i)
				{
					snake[i].x = snake[i + 1].x;
					snake[i].y = snake[i + 1].y;
				}
				snake[i].x += 1;
				snake[i].y += 0;
				timer = 0;
			}
			else if (snake[snake.size() - 1].x - snake[snake.size() - 2].x == -1)
			{
				int i;
				for (i = 0; i < snake.size() - 1; ++i)
				{
					snake[i].x = snake[i + 1].x;
					snake[i].y = snake[i + 1].y;
				}
				snake[i].x += -1;
				snake[i].y += 0;
				timer = 0;
			}
			else if (snake[snake.size() - 1].y - snake[snake.size() - 2].y == 1)
			{
				int i;
				for (i = 0; i < snake.size() - 1; ++i)
				{
					snake[i].x = snake[i + 1].x;
					snake[i].y = snake[i + 1].y;
				}
				snake[i].x += 0;
				snake[i].y += 1;
				timer = 0;
			}
			else if (snake[snake.size() - 1].y - snake[snake.size() - 2].y == -1)
			{
				int i;
				for (i = 0; i < snake.size() - 1; ++i)
				{
					snake[i].x = snake[i + 1].x;
					snake[i].y = snake[i + 1].y;
				}
				snake[i].x += 0;
				snake[i].y += -1;
				timer = 0;
			}
		}
		if (GameOver)
			break;
		window.display();
	}
	return 0;
}