#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <vector>

class ChessFigure :public sf::Drawable
{
	static int ChessNum;
	static sf::SoundBuffer m_moveBuf;
	static sf::SoundBuffer m_beatBuf;
	static void LoadFiles();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
protected:
	char m_color;
	char m_alived;
	bool m_firstTurn;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	static sf::Sound m_move;
	static sf::Sound m_beat;

	sf::Vector2i m_pos;
public:
	ChessFigure(sf::Vector2i&& pos, const char& color) noexcept;
	~ChessFigure();
	virtual bool Move();
	virtual std::vector<sf::Vector2i> CanMove() const = 0;
	char GetColor() const;
	void Kill();
	bool CheckAlived() const;
	char GetStatus() const;
	bool FirstTurn() const;

	bool operator==(const sf::Vector2i& other);
	sf::FloatRect getGlobalBounds() const;
	void setPosition(const float& x, const float& y);
	sf::Vector2i GetPosition() const;
};
