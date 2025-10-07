#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <random>
#include "tileset.h"
#include "soggy.h"


class Game
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window) const;

    void init();

    void instantiate();

    void restart();

    void pauseSounds() const;

    void resumeSounds() const;

    inline static bool closeGame = false;

    inline static bool gameOver = false;

    inline static bool canClickZ = true;

    inline static bool canClick = true;

    // sog

    inline static bool shouldCheckSogs = false;

    inline static bool shouldSpawnSog = false;

    inline static int nextSogSize = 0;

    inline static sf::Vector2f nextSogPos = {0, 0};

    inline static float nextSogRot = 0;

    inline static float nextSogRotFact = 0;

    inline static sf::Vector2f nextSogSpeedFact = { 0, 0 };

    inline static sf::Vector2f nextSogSpeed = { 0, 0 };

    inline static float nextSogRotSpeed = 0;

private:

    void updateDifficultyCounters();

    void checkUnactiveSogs();

    int randomInt(int min, int max);

    void spawnSog(int sogSize, int posX, int posY, float rot,
        float rotFact, float speedXFact, float speedYFact, float speedX, float speedY, float rotSpeed);

    Tileset* m_tileset = new Tileset();

    bool m_isMainMenuActive = true;
    bool m_mainMenuSelection = true; // true = Play, false = Quit

    bool m_isPauseMenuActive = false;
    bool m_pauseMenuSelection = true; // true = Resume, false = Quit

    bool m_isDifficultyMenuActive = false;
    int m_difficultyMenuSelection = 0; // 0 = rows, 1 = cols, 2 = Bombs, 3 = Start

    int m_rows = 10;
    int m_columns = 15;

    int m_numberOfBombs = 30;

    int m_firstSpawnPosX = 0;
    int m_firstSpawnPosY = 0;

    int m_spawnPosX = 0;
    int m_spawnPosY = 0;

    int m_columnNumber = 0;

    int m_menuSongNum = 6;
    int m_gameSongNum = 10;

    sf::Sprite m_mainMenuPlaySprite;
    sf::Texture m_mainMenuPlayTexture;
    sf::Sprite m_mainMenuQuitSprite;
    sf::Texture m_mainMenuQuitTexture;

    sf::Sprite m_pauseMenuResumeSprite;
    sf::Texture m_pauseMenuResumeTexture;
    sf::Sprite m_pauseMenuQuitSprite;
    sf::Texture m_pauseMenuQuitTexture;

    sf::Sprite m_difficultyMenuSprite;
    sf::Texture m_difficultyMenuTexture;
    sf::Sprite m_difficultyMenuStartSprite;
    sf::Texture m_difficultyMenuStartTexture;

    sf::Texture m_sogTexture;

    sf::Music m_menuMusic;
    sf::Music m_gameMusic;
    sf::Music m_sogMusic;

    Tile* m_difficultyColumn = new Tile();
    Tile* m_difficultyRow = new Tile();
    Tile* m_difficultyBomb = new Tile();

    Tile* m_difficultyColumnNum1 = new Tile();
    Tile* m_difficultyColumnNum2 = new Tile();

    Tile* m_difficultyRowNum1 = new Tile();
    Tile* m_difficultyRowNum2 = new Tile();

    Tile* m_difficultyBombNum1 = new Tile();
    Tile* m_difficultyBombNum2 = new Tile();

    sf::Texture m_tileUnkwnownTexture;
    sf::Texture m_tile0Texture;
    sf::Texture m_tile1Texture;
    sf::Texture m_tile2Texture;
    sf::Texture m_tile3Texture;
    sf::Texture m_tile4Texture;
    sf::Texture m_tile5Texture;
    sf::Texture m_tile6Texture;
    sf::Texture m_tile7Texture;
    sf::Texture m_tile8Texture;
    sf::Texture m_tile9Texture;
    sf::Texture m_tileFlagTexture;
    sf::Texture m_tileWrongFlagTexture;
    sf::Texture m_tileMineTexture;
    sf::Texture m_tileRedMineTexture;
    sf::Texture m_tileColumnTexture;
    sf::Texture m_tileRowTexture;
    sf::Texture m_selectTexture;

    std::vector<Soggy*> m_sogArray;

    sf::Texture m_explosionTexture;
    sf::SoundBuffer m_explosionSoundBuffer;

    bool m_canQuit = true;
    bool m_canMove = true;
    bool m_canSog = true;
    bool m_isSogging = false;
    int m_sogRandomTime = 0;

    std::random_device rd;

};
