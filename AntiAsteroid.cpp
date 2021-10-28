#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int main() {

	srand(time(0));

	RenderWindow window(VideoMode(1000, 600), "Anti Asteroid");


	bool start = false;
	Texture f;
	f.loadFromFile("G:\\C++\\VS_project\\gamed2D\\AntiAsteroid\\images\\fon.png");
	Sprite fon[2];
	for (int i = 0; i < 2; i++) {
		fon[i].setTexture(f);
		fon[i].setPosition(0, 600 * i - 600);
	}
	fon[1].setTextureRect(IntRect(0, 600, 1000, -600));
	
	Texture player;
	player.loadFromFile("G:\\C++\\VS_project\\gamed2D\\AntiAsteroid\\images\\player.png");
	Sprite player_sprite(player);
	player_sprite.setTextureRect(IntRect(0, 0, 208, 145));
	player_sprite.setPosition(400, 450);
	float frame = 0;
	
	Texture as;
	as.loadFromFile("G:\\C++\\VS_project\\gamed2D\\AntiAsteroid\\images\\asteroid.png");
	Sprite asteroid[7];
	int ay[7] = { 0 };
	for (int i = 0; i < 7; i++) {
		asteroid[i].setTexture(as);
		ay[i] = rand() % 5;
		asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);
	}

	Texture pu;
	pu.loadFromFile("G:\\C++\\VS_project\\gamed2D\\AntiAsteroid\\images\\pula.png");
	Sprite pula(pu);
	pula.setPosition(-50, 0);
	
	Texture go;
	go.loadFromFile("G:\\C++\\VS_project\\gamed2D\\AntiAsteroid\\images\\gameover.png");
	Sprite gameover(go);
	gameover.setPosition(250, 200);

	Texture st;
	st.loadFromFile("G:\\C++\\VS_project\\gamed2D\\AntiAsteroid\\images\\start.png");
	Sprite start_sprite(st);
	start_sprite.setPosition(250, 300);
	

	while (window.isOpen())
	{
		Vector2f pl = player_sprite.getPosition();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{	
				if (event.key.code == Keyboard::P) start = true;
				if (start) {

				pula.setPosition(-50, 0);

				if (pl.x > 0 && event.key.code == Keyboard::Left || pl.x > 0 && event.key.code == Keyboard::A)
					player_sprite.move(-25, 0.);
				if (pl.x < 800 && event.key.code == Keyboard::Right || pl.x < 800 && event.key.code == Keyboard::D)
					player_sprite.move(25, 0.);
				if (pl.y > 10 && event.key.code == Keyboard::Up || pl.y > 10 && event.key.code == Keyboard::W)
					player_sprite.move(0., -25);
				if (pl.y < 450 && event.key.code == Keyboard::Down || pl.y < 450 && event.key.code == Keyboard::S)
					player_sprite.move(0., 25);
				if (event.key.code == Keyboard::Space)
					pula.setPosition(pl.x + 95, pl.y - 55);
				}
			}
		}

		if (start) {

			Vector2f fn[2];
			for (int i = 0; i < 2; i++) {
					fon[i].move(0, 0.5);

				fn[i] = fon[i].getPosition();
				if (fn[i].y > 590)
					fon[i].setPosition(0, -590);
			}

			Vector2f ad[7];
			for (int i = 0; i < 7; i++)
			{
				asteroid[i].move(0, 0.5);

				ad[i] = asteroid[i].getPosition();
				if (ad[i].y > 550) {
					ay[i] = rand() % 5;
					asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);
				}

				if (pula.getGlobalBounds().intersects(asteroid[i].getGlobalBounds())) {
					ay[i] = rand() % 5;
					asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);

					pula.setPosition(-50, 0);
				}
			

			}
			
			Vector2f pa = pula.getPosition();
			pula.move(0., - 3);
		}	

		frame += 0.01;
		if (frame < 1)
			player_sprite.setTextureRect(IntRect(0, 0, 208, 145));
		else if (frame > 1 && frame < 2)
		{
			player_sprite.setTextureRect(IntRect(214, 0, 208, 145));
		}
		else
			frame = 0;

		window.clear(Color::Black);
		for (int i = 0; i < 2; i++)
			window.draw(fon[i]);

		window.draw(player_sprite);

		if (start) 
		{
			for (int i = 0; i < 7; ++i)
				window.draw(asteroid[i]);
		}
		window.draw(pula);

		for (int i = 0; i < 7; ++i)
			if (player_sprite.getGlobalBounds().intersects(asteroid[i].getGlobalBounds()))
			{
				start = false;
				window.draw(gameover);
				break;
			}
		if (event.key.code == Keyboard::P) start = true;
		
		if (start == false) window.draw(start_sprite);
		window.display();
	}

	return 0;
}