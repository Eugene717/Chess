#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "GameDataPacket.h"

struct GameIMPL;
class ChessFigure;

class Game
{
	GameIMPL* m_pImpl;
	static Game* m_game;

	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void AnnounceWinner(const char& color, const std::string name);
	void GameEnd();
	char SearchGame(sf::TcpSocket& socket);
	void ShutdownMes();
public:
	ChessFigure* m_board[8][8];
	GameDataPacket m_dataPacket;  //для игрока(костыль?)

	sf::RenderWindow m_window;
	sf::Event m_event;
	static Game* GetInstance();
	~Game();

	int MainMenu();
	void DrawGame();
	void DrawPossibleMoves(const std::vector<sf::Vector2i>& pos, const char& player);
	bool ReturnCheck(const char& color) const;
	bool Exit();

	void SinglePlayer();
	void OnePC();
	void Multiplayer();
};

#endif // !GAME_H