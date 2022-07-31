#include "Game.h"
#include "Player.h"
#include "Human.h"
#include "AI.h"
#include "ChessFigure.h"

Game* Game::m_game = nullptr;

struct GameIMPL
{
	sf::Font m_font;
	sf::Texture m_t_board;
	sf::Sprite m_s_board;
	bool m_returnToMainMenu;
	bool m_MP;
	Player* m_playerOne;
	Player* m_playerTwo;

	GameIMPL();
};

GameIMPL::GameIMPL()
{
	m_font.loadFromFile("resourses/arial.ttf");
	m_t_board.loadFromFile("resourses/images/board.png");
	m_s_board.setTexture(m_t_board);
	m_returnToMainMenu = false;
	m_MP = false;
	
	m_playerOne = nullptr;
	m_playerTwo = nullptr;
}

Game::Game()
{
	m_pImpl = new GameIMPL;
	m_pImpl->m_font.loadFromFile("resourses/arial.ttf");
	m_window.create(sf::VideoMode(800, 800), "Checkers");
}

Game* Game::GetInstance()
{
	if (m_game == nullptr)
		m_game = new Game();
	return m_game;
}

Game::~Game()
{
	delete m_game;
	delete m_pImpl;
}

int Game::MainMenu()
{
	float centerPos = m_window.getSize().x / 2;

	sf::Text header("Chess", m_pImpl->m_font);
	header.setCharacterSize(102);
	header.setStyle(sf::Text::Bold);
	header.setPosition(centerPos - header.getGlobalBounds().width / 2, 0);

	sf::Text singleplayer("Singlelayer", m_pImpl->m_font);
	singleplayer.setCharacterSize(44);
	singleplayer.setPosition(centerPos - singleplayer.getGlobalBounds().width / 2, header.getPosition().y + 200);

	sf::Text onePC("Two on one PC", m_pImpl->m_font);
	onePC.setCharacterSize(44);
	onePC.setPosition(centerPos - onePC.getGlobalBounds().width / 2, singleplayer.getPosition().y + 120);

	sf::Text multiplayer("Multiplayer", m_pImpl->m_font);
	multiplayer.setCharacterSize(44);
	multiplayer.setPosition(centerPos - multiplayer.getGlobalBounds().width / 2, onePC.getPosition().y + 120);

	sf::Text exit("Exit", m_pImpl->m_font);
	exit.setCharacterSize(44);
	exit.setPosition(centerPos - exit.getGlobalBounds().width / 2, multiplayer.getPosition().y + 120);

	int menuNum = -1;

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
			if (m_event.type == sf::Event::MouseButtonReleased)
			{
				if (m_event.key.code == sf::Mouse::Left)
				{
					m_window.clear(sf::Color::White);
					return menuNum;
				}
			}
		}

		menuNum = 0;

		header.setFillColor(sf::Color::Black);
		singleplayer.setFillColor(sf::Color::Black);
		onePC.setFillColor(sf::Color::Black);
		multiplayer.setFillColor(sf::Color::Black);
		exit.setFillColor(sf::Color::Black);

		if (sf::IntRect(singleplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			singleplayer.setFillColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::IntRect(onePC.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			onePC.setFillColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::IntRect(multiplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			multiplayer.setFillColor(sf::Color::Blue);
			menuNum = 3;
		}
		if (sf::IntRect(exit.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			exit.setFillColor(sf::Color::Blue);
			menuNum = 4;
		}

		m_window.clear(sf::Color::White);
		m_window.draw(header);
		m_window.draw(singleplayer);
		m_window.draw(onePC);
		m_window.draw(multiplayer);
		m_window.draw(exit);
		m_window.display();
	}
	return -1;
}

void Game::DrawGame()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_pImpl->m_s_board);
	m_window.draw(*m_pImpl->m_playerOne);
	m_window.draw(*m_pImpl->m_playerTwo);
	m_window.display();
}

void Game::DrawPossibleMoves(const std::vector<sf::Vector2i>& pos, const char& player)
{	
	sf::CircleShape shape;
	shape.setRadius(15);
	shape.setOrigin(15, 15);
	shape.setFillColor(sf::Color(80, 80, 80, 85));

	sf::RectangleShape enemyShape;
	enemyShape.setSize(sf::Vector2f(90, 90));
	enemyShape.setOrigin(45, 45);
	enemyShape.setOutlineThickness(5);
	enemyShape.setFillColor(sf::Color(0, 0, 0, 0));
	enemyShape.setOutlineColor(sf::Color(0, 255, 0, 150));

	m_window.draw(m_pImpl->m_s_board);

	for (auto i : pos)
	{
		if (m_board[i.x][i.y] != nullptr)
		{
			enemyShape.setPosition(i.x * 100 + 50, i.y * 100 + 50);
			m_window.draw(enemyShape);
		}
		else
		{
			shape.setPosition(i.x * 100 + 50, i.y * 100 + 50);
			m_window.draw(shape);
		}
	}

	if (player == 'b')
	{
		m_window.draw(*m_pImpl->m_playerOne);
		m_window.draw(*m_pImpl->m_playerTwo);
	}
	else
	{
		m_window.draw(*m_pImpl->m_playerTwo);
		m_window.draw(*m_pImpl->m_playerOne);
	}

	m_window.display();
}

bool Game::ReturnCheck(const char& color) const
{
	if (m_pImpl->m_playerOne->GetColor() == color)
	{
		return m_pImpl->m_playerTwo->CheckCheck(m_pImpl->m_playerOne->GetKingPos());
	}
	else
	{
		return m_pImpl->m_playerOne->CheckCheck(m_pImpl->m_playerTwo->GetKingPos());
	}	
}

void Game::AnnounceWinner(const char& color, const std::string name = "\0")
{
	sf::sleep(sf::seconds(1));
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2);

	sf::Text announce("",m_pImpl->m_font);
	announce.setFillColor(sf::Color::Black);
	announce.setCharacterSize(30);
	announce.setStyle(sf::Text::Style::Bold);

	if (name != "\0")
	{
		std::string sColor;
		color == 'w' ? sColor = " (white) " : sColor = " (black) ";
		announce.setString(name + sColor + "WIN!");
	}
	else if (color == 'w')
	{
		announce.setString("WHITE PLAYER WIN!");
	}
	else if (color == 'b')
	{
		announce.setString("BLACK PLAYER WIN!");
	}

	announce.setPosition(centerPos.x - announce.getGlobalBounds().width / 2, centerPos.y - announce.getGlobalBounds().height / 2 - 50);

	m_window.clear(sf::Color::White);
	m_window.draw(announce);
	m_window.display();
	sf::sleep(sf::seconds(3));

	GameEnd();
}

void Game::GameEnd()
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			m_board[i][j] = nullptr;
		}
	}
	delete m_pImpl->m_playerOne;
	delete m_pImpl->m_playerTwo;
	m_pImpl->m_playerOne = nullptr;
	m_pImpl->m_playerTwo = nullptr;
}

bool Game::Exit()
{
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 100);

	sf::Text exit("Are you sure about that?", m_pImpl->m_font);
	exit.setFillColor(sf::Color::Black);
	exit.setCharacterSize(30);
	exit.setStyle(sf::Text::Style::Bold);
	exit.setPosition(centerPos.x - exit.getGlobalBounds().width / 2, centerPos.y - exit.getGlobalBounds().height);

	sf::Text yes("Yes", m_pImpl->m_font);
	sf::Text no("No", m_pImpl->m_font);

	yes.setPosition(centerPos.x - yes.getGlobalBounds().width / 2 - 50, centerPos.y - yes.getGlobalBounds().height / 2 + 50);
	no.setPosition(centerPos.x - no.getGlobalBounds().width / 2 + 50, centerPos.y - no.getGlobalBounds().height / 2 + 50);

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
			if (m_event.type == m_event.MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left)
			{
				if (sf::IntRect(yes.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
					return true;
				if (sf::IntRect(no.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					m_window.clear(sf::Color::White);
					return false;
				}
			}
		}

		yes.setFillColor(sf::Color::Black);
		no.setFillColor(sf::Color::Black);

		if (sf::IntRect(yes.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			yes.setFillColor(sf::Color::Blue);
		}
		if (sf::IntRect(no.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			no.setFillColor(sf::Color::Blue);
		}

		m_window.clear(sf::Color::White);
		m_window.draw(exit);
		m_window.draw(yes);
		m_window.draw(no);
		m_window.display();
	}
	return true;
}

void Game::SinglePlayer()
{
	m_pImpl->m_playerOne = new Human('b');
	m_pImpl->m_playerTwo = new AI('w');

	while (m_window.isOpen())
	{
		if (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
		}

		DrawGame();

	}
}

void Game::OnePC()
{
	m_pImpl->m_playerOne = new Human('w');
	m_pImpl->m_playerTwo = new Human('b');

	while (m_window.isOpen())
	{
		if (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
		}

		DrawGame();		

		if (m_pImpl->m_playerOne->Move())
		{
			if (m_pImpl->m_playerTwo->KingKilled())
			{
				AnnounceWinner(m_pImpl->m_playerOne->GetColor());
				delete m_pImpl->m_playerOne;
				delete m_pImpl->m_playerTwo;
				return;
			}
			m_pImpl->m_playerTwo->DeleteKilled();
		}

		if (m_pImpl->m_playerTwo->Move())
		{
			if (m_pImpl->m_playerOne->KingKilled())
			{
				AnnounceWinner(m_pImpl->m_playerTwo->GetColor());
				delete m_pImpl->m_playerOne;
				delete m_pImpl->m_playerTwo;
				return;
			}
			m_pImpl->m_playerOne->DeleteKilled();
		}
	}
}

void Game::Multiplayer()
{
	sf::TcpSocket socket;

	char turn;
	while (true)
	{
		turn = SearchGame(socket);
		if (turn == '\0')
			return;
		else if (turn == '\1')
			continue;
		else
			break;
	}

	if (turn == 'f')
	{
		m_pImpl->m_playerOne = new Human('w');
		m_pImpl->m_playerTwo = new Human('b');
	}
	else
	{
		m_pImpl->m_playerOne = new Human('b');
		m_pImpl->m_playerTwo = new Human('w');
	}

	m_pImpl->m_MP = true;
	sf::Packet packet;
	socket.setBlocking(false);

	while (m_window.isOpen())
	{
		if (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
		}

		DrawGame();

		if (turn == 'f')
		{
			DrawGame();

			if (socket.receive(packet) == sf::Socket::Disconnected)
			{
				ShutdownMes();
				AnnounceWinner(m_pImpl->m_playerOne->GetColor());
				socket.disconnect();
				return;
			}

			m_pImpl->m_playerOne->Move();

			packet << m_dataPacket;
			socket.send(packet);
			packet.clear();

			if (m_pImpl->m_playerTwo->KingKilled())
			{
				AnnounceWinner(m_pImpl->m_playerOne->GetColor());
				socket.disconnect();
				return;
			}
			m_pImpl->m_playerTwo->DeleteKilled();

			turn = 's';
		}
		else
		{

			if (static_cast<Human*>(m_pImpl->m_playerTwo)->MoveMP(socket))
			{
				if (m_pImpl->m_playerOne->KingKilled())
				{
					AnnounceWinner(m_pImpl->m_playerOne->GetColor());
					socket.disconnect();
					return;
				}
				m_pImpl->m_playerOne->DeleteKilled();
			}

			if (socket.receive(packet) == sf::Socket::Disconnected)
			{
				ShutdownMes();
				AnnounceWinner(m_pImpl->m_playerOne->GetColor());
				socket.disconnect();
				return;
			}

			turn = 'f';
		}
	}
	socket.disconnect();
}

char Game::SearchGame(sf::TcpSocket& socket)
{
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 40);

	sf::Text loading("   Loading . . .", m_pImpl->m_font);
	loading.setFillColor(sf::Color::Black);
	loading.setCharacterSize(30);
	loading.setStyle(sf::Text::Style::Bold);
	loading.setPosition(centerPos.x - loading.getGlobalBounds().width / 2, centerPos.y - loading.getGlobalBounds().height);

	m_window.clear(sf::Color::White);
	m_window.draw(loading);
	m_window.display();

	if (socket.connect("localhost", 55003, sf::seconds(3)) != sf::Socket::Status::Done)   //192.178.0.105 for example
	{
		loading.setString("       Failed connection\nCheck Ethernet connection");
		loading.setCharacterSize(24);
		loading.setPosition(centerPos.x - loading.getGlobalBounds().width / 2, centerPos.y - loading.getGlobalBounds().height);

		m_window.clear(sf::Color::White);
		m_window.draw(loading);
		m_window.display();
		sf::sleep(sf::seconds(3));

		return '\0';
	}

	sf::Packet packet;
	std::string turn;
	bool sound = false;

	socket.setBlocking(false);

	loading.setString("  Searching . . .");
	sf::Text back("Back", m_pImpl->m_font);
	back.setFillColor(sf::Color::Black);
	back.setCharacterSize(24);
	back.setPosition(35 - back.getGlobalBounds().width / 2, 475 - back.getGlobalBounds().height);

	while (m_window.isOpen())
	{
		if (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::MouseButtonReleased && m_event.key.code == sf::Mouse::Left)
			{
				if (sf::IntRect(back.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					m_window.clear(sf::Color::White);
					socket.setBlocking(true);
					socket.disconnect();
					return '\1';
				}
			}
		}
		sf::Socket::Status status = socket.receive(packet);
		if (status == sf::Socket::Done)
		{
			packet >> turn;
			packet.clear();

			packet << "none";
			socket.send(packet);
			packet.clear();

			m_window.clear(sf::Color::White);
			m_window.draw(loading);
			m_window.display();
			sf::sleep(sf::seconds(1));
			m_window.clear(sf::Color::White);

			return turn[0];
		}

		back.setFillColor(sf::Color::Black);
		if (sf::IntRect(back.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			back.setFillColor(sf::Color::Blue);
		}
		else
			sound = false;

		m_window.clear(sf::Color::White);
		m_window.draw(loading);
		m_window.draw(back);
		m_window.display();
	}
	return '\1';
}

void Game::ShutdownMes()
{
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 40);

	sf::Text shutdown("", m_pImpl->m_font);
	shutdown.setFillColor(sf::Color::Black);
	shutdown.setCharacterSize(30);
	shutdown.setStyle(sf::Text::Style::Bold);

	shutdown.setString("Enemy left from game");

	shutdown.setPosition(centerPos.x - shutdown.getGlobalBounds().width / 2, centerPos.y - shutdown.getGlobalBounds().height);

	sf::sleep(sf::seconds(1));
	m_window.clear(sf::Color::White);
	m_window.draw(shutdown);
	m_window.display();

	sf::sleep(sf::seconds(1));
}
