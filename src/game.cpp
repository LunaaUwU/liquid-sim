#include "game.h"


void Game::update(const sf::Int32 deltaMS)
{
    // Split update behaviour depending on the menu
    if (m_isMainMenuActive)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_mainMenuSelection = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_mainMenuSelection = false;
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && canClickZ)
        {
	        if (m_mainMenuSelection)
	        {
                m_isMainMenuActive = false;
                m_isDifficultyMenuActive = true;
	        }
            else
            {
                closeGame = true;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_canQuit)
        {
            closeGame = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_canQuit = true;
        }
    }
    else if (m_isDifficultyMenuActive)
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && m_canMove)
        {
            m_difficultyMenuSelection++;
            if (m_difficultyMenuSelection >= 4)
                m_difficultyMenuSelection = 0;

            if (m_difficultyRow->getIsSelected())
                m_difficultyRow->select();
            else if (m_difficultyMenuSelection == 0)
                m_difficultyRow->select();

            if (m_difficultyColumn->getIsSelected())
                m_difficultyColumn->select();
            else if(m_difficultyMenuSelection == 1)
                m_difficultyColumn->select();

            if (m_difficultyBomb->getIsSelected())
                m_difficultyBomb->select();
            else if (m_difficultyMenuSelection == 2)
                m_difficultyBomb->select();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && m_canMove)
        {
            m_difficultyMenuSelection--;
            if (m_difficultyMenuSelection < 0)
                m_difficultyMenuSelection = 3;

            if (m_difficultyRow->getIsSelected())
                m_difficultyRow->select();
            else if (m_difficultyMenuSelection == 0)
                m_difficultyRow->select();

            if (m_difficultyColumn->getIsSelected())
                m_difficultyColumn->select();
            else if (m_difficultyMenuSelection == 1)
                m_difficultyColumn->select();

            if (m_difficultyBomb->getIsSelected())
                m_difficultyBomb->select();
            else if (m_difficultyMenuSelection == 2)
                m_difficultyBomb->select();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && m_canMove)
        {
            if (m_difficultyMenuSelection == 0)
            {
                m_rows++;
                if (m_rows >= 20)
                {
                    m_rows = 20;
                }
            }
            else if (m_difficultyMenuSelection == 1)
            {
                m_columns++;
                if (m_columns >= 25)
                {
                    m_columns = 25;
                }
            }
            else if (m_difficultyMenuSelection == 2)
            {
                m_numberOfBombs++;
                if (m_numberOfBombs >= 99)
                {
                    m_numberOfBombs = 99;
                }
            }
            updateDifficultyCounters();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && m_canMove)
        {
            if (m_difficultyMenuSelection == 0)
            {
                m_rows--;
                if (m_rows <= 5)
                {
                    m_rows = 5;
                }
            }
            else if (m_difficultyMenuSelection == 1)
            {
                m_columns--;
                if (m_columns <= 5)
                {
                    m_columns = 5;
                }
            }
            else if (m_difficultyMenuSelection == 2)
            {
                m_numberOfBombs--;
                if (m_numberOfBombs <= 5)
                {
                    m_numberOfBombs = 5;
                }
            }
            updateDifficultyCounters();
        }
	    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && canClickZ)
	    {
            m_isDifficultyMenuActive = false;
            m_menuMusic.stop();
            m_sogMusic.stop();
            m_isSogging = false;
            instantiate();
	    }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_canMove = true;
        }
        else
        {
            m_canMove = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_canQuit)
        {
            m_canQuit = false;
            m_isDifficultyMenuActive = false;
            m_isMainMenuActive = true;
            m_difficultyMenuSelection = 0;

            if (!m_difficultyColumn->getIsSelected())
                m_difficultyColumn->select();
            if (m_difficultyRow->getIsSelected())
                m_difficultyRow->select();
            if (m_difficultyBomb->getIsSelected())
                m_difficultyBomb->select();

        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_canQuit = true;
        }
    }
    else if (m_isPauseMenuActive)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_pauseMenuSelection = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_pauseMenuSelection = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
	        if (m_pauseMenuSelection)
	        {
                m_isPauseMenuActive = false;
                if (m_isSogging)
                {
                    m_sogMusic.play();
                    resumeSounds();
                }
                else
                    m_gameMusic.play();
	        }
            else
            {
                m_canQuit = false;
                restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_canQuit)
        {
            m_canQuit = false;
            restart();
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_canQuit = true;
        }
        m_canSog = false;
    }
    else
    {
        m_tileset->update(deltaMS);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_canQuit)
        {
            m_canQuit = false;
            m_isPauseMenuActive = true;
            m_gameMusic.pause();
            if (m_isSogging)
            {
                m_sogMusic.pause();
                pauseSounds();
            }
                
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_canQuit = true;
        }
    }

    if (gameOver)
    {
        restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::O) && sf::Keyboard::isKeyPressed(sf::Keyboard::G) && m_canSog)
    {
        m_canSog = false;
        m_isSogging = true;
        m_menuMusic.stop();
        m_gameMusic.stop();

        //      sz px py rot rf sxf syf sx sy rs
        spawnSog(0, 0, 0, -1, 0, 0, 0, 0, 0, 0); // random sog
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {
        m_canSog = true;
    }

    if (shouldSpawnSog)
    {
        // customm sog (mitosed)
        spawnSog(nextSogSize, nextSogPos.x, nextSogPos.y, nextSogRot,
            nextSogRotFact, nextSogSpeedFact.x, nextSogSpeedFact.y, nextSogSpeed.x, nextSogSpeed.y, nextSogRotSpeed);
        shouldSpawnSog = false;
    }
    if (shouldCheckSogs)
    {
        shouldCheckSogs = false;
        checkUnactiveSogs();
    }
    if (!m_isPauseMenuActive && m_isSogging)
    {
        for (Soggy* soggy : m_sogArray)
        {
            soggy->update(deltaMS);
        }
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        canClickZ = true;
    }
    else
    {
        canClickZ = false;
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        canClick = true;
    }
    else
    {
        canClick = false;
    }
}

void Game::render(sf::RenderWindow& window) const
{
    
    window.clear();

    if (closeGame)
    {
        window.close();
    }

    if (m_isMainMenuActive)
    {
	    if (m_mainMenuSelection)
	    {
            window.draw(m_mainMenuPlaySprite);
	    }
        else
        {
            window.draw(m_mainMenuQuitSprite);
        }
    }
    else if (m_isDifficultyMenuActive)
    {
	    if (m_difficultyMenuSelection == 3)
	    {
            window.draw(m_difficultyMenuStartSprite);
	    }
        else
        {
            window.draw(m_difficultyMenuSprite);
        }
        m_difficultyRow->render(window);
        m_difficultyRowNum1->render(window);
        m_difficultyRowNum2->render(window);
        m_difficultyColumn->render(window);
        m_difficultyColumnNum1->render(window);
        m_difficultyColumnNum2->render(window);
        m_difficultyBomb->render(window);
        m_difficultyBombNum1->render(window);
        m_difficultyBombNum2->render(window);
    }
    else if (m_isPauseMenuActive)
    {
	    if (m_pauseMenuSelection)
	    {
            window.draw(m_pauseMenuResumeSprite);
	    }
        else
        {
            window.draw(m_pauseMenuQuitSprite);
        }
    }
    else
    {
        m_tileset->render(window);
    }

    if (m_isSogging)
    {
        for (Soggy* soggy : m_sogArray)
        {
            soggy->render(window);
        }
    }

    window.display();
}

void Game::init()
{
    m_mainMenuPlayTexture.loadFromFile("../sprites/menu/main_menu_play.png");
    m_mainMenuPlaySprite.setTexture(m_mainMenuPlayTexture);
    m_mainMenuPlaySprite.setPosition(sf::Vector2f(0.f, 0.f));
    m_mainMenuQuitTexture.loadFromFile("../sprites/menu/main_menu_quit.png");
    m_mainMenuQuitSprite.setTexture(m_mainMenuQuitTexture);
    m_mainMenuQuitSprite.setPosition(sf::Vector2f(0.f, 0.f));

    m_pauseMenuResumeTexture.loadFromFile("../sprites/menu/pause_menu_resume.png");
    m_pauseMenuResumeSprite.setTexture(m_pauseMenuResumeTexture);
    m_pauseMenuResumeSprite.setPosition(sf::Vector2f(0.f, 0.f));
    m_pauseMenuQuitTexture.loadFromFile("../sprites/menu/pause_menu_quit.png");
    m_pauseMenuQuitSprite.setTexture(m_pauseMenuQuitTexture);
    m_pauseMenuQuitSprite.setPosition(sf::Vector2f(0.f, 0.f));

    m_difficultyMenuTexture.loadFromFile("../sprites/menu/difficulty_menu.png");
    m_difficultyMenuSprite.setTexture(m_difficultyMenuTexture);
    m_difficultyMenuSprite.setPosition(sf::Vector2f(0.f, 0.f));
    m_difficultyMenuStartTexture.loadFromFile("../sprites/menu/difficulty_menu_start.png");
    m_difficultyMenuStartSprite.setTexture(m_difficultyMenuStartTexture);
    m_difficultyMenuStartSprite.setPosition(sf::Vector2f(0.f, 0.f));

    m_sogTexture.loadFromFile("../sprites/soggycat.png");

    m_menuMusic.openFromFile("../audio/music/menu/menu_" + std::to_string(randomInt(1, m_menuSongNum)) + ".mp3");
    m_menuMusic.play();
    m_menuMusic.setLoop(true);
    m_menuMusic.setVolume(20.f);

    m_sogMusic.openFromFile("../audio/music/soggy.mp3");
    m_sogMusic.setLoop(true);
    m_sogMusic.setVolume(35.f);

    // TILES
    m_tileUnkwnownTexture.loadFromFile("../sprites/tiles/TileUnknown.png");
    m_tile0Texture.loadFromFile("../sprites/tiles/Tile0.png");
    m_tile1Texture.loadFromFile("../sprites/tiles/Tile1.png");
    m_tile2Texture.loadFromFile("../sprites/tiles/Tile2.png");
    m_tile3Texture.loadFromFile("../sprites/tiles/Tile3.png");
    m_tile4Texture.loadFromFile("../sprites/tiles/Tile4.png");
    m_tile5Texture.loadFromFile("../sprites/tiles/Tile5.png");
    m_tile6Texture.loadFromFile("../sprites/tiles/Tile6.png");
    m_tile7Texture.loadFromFile("../sprites/tiles/Tile7.png");
    m_tile8Texture.loadFromFile("../sprites/tiles/Tile8.png");
    m_tile9Texture.loadFromFile("../sprites/tiles/Tile9.png");
    m_tileFlagTexture.loadFromFile("../sprites/tiles/TileFlag.png");
    m_tileWrongFlagTexture.loadFromFile("../sprites/tiles/TileWrongFlag.png");
    m_tileMineTexture.loadFromFile("../sprites/tiles/TileMine.png");
    m_tileRedMineTexture.loadFromFile("../sprites/tiles/TileExploded.png");
    m_tileColumnTexture.loadFromFile("../sprites/tiles/TileColumn.png");
    m_tileRowTexture.loadFromFile("../sprites/tiles/TileRow.png");
    m_selectTexture.loadFromFile("../sprites/tiles/Select.png");

    m_difficultyRow->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyRowNum1->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyRowNum2->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyColumn->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyColumnNum1->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyColumnNum2->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyBomb->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyBombNum1->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
    m_difficultyBombNum2->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);

    m_difficultyRow->setPosition(896, 458);
    m_difficultyRowNum1->setPosition(960, 458);
    m_difficultyRowNum2->setPosition(992, 458);
    m_difficultyColumn->setPosition(896, 522);
    m_difficultyColumnNum1->setPosition(960, 522);
    m_difficultyColumnNum2->setPosition(992, 522);
    m_difficultyBomb->setPosition(896, 586);
    m_difficultyBombNum1->setPosition(960, 586);
    m_difficultyBombNum2->setPosition(992, 586);

    m_difficultyRow->setIsOnBoard(false);
    m_difficultyRowNum1->setIsOnBoard(false);
    m_difficultyRowNum2->setIsOnBoard(false);
    m_difficultyColumn->setIsOnBoard(false);
    m_difficultyColumnNum1->setIsOnBoard(false);
    m_difficultyColumnNum2->setIsOnBoard(false);
    m_difficultyBomb->setIsOnBoard(false);
    m_difficultyBombNum1->setIsOnBoard(false);
    m_difficultyBombNum2->setIsOnBoard(false);

    m_difficultyRow->setValue(14);
    m_difficultyRowNum1->setValue(1);
    m_difficultyRowNum2->setValue(0);
    m_difficultyColumn->setValue(13);
    m_difficultyColumnNum1->setValue(1);
    m_difficultyColumnNum2->setValue(5);
    m_difficultyBomb->setValue(-1);
    m_difficultyBombNum1->setValue(3);
    m_difficultyBombNum2->setValue(0);

    m_difficultyRow->openTile(false);
    m_difficultyRowNum1->openTile(false);
    m_difficultyRowNum2->openTile(false);
    m_difficultyColumn->openTile(false);
    m_difficultyColumnNum1->openTile(false);
    m_difficultyColumnNum2->openTile(false);
    m_difficultyBomb->openTile(false);
    m_difficultyBombNum1->openTile(false);
    m_difficultyBombNum2->openTile(false);

    m_difficultyRow->setActive(true);
    m_difficultyRowNum1->setActive(true);
    m_difficultyRowNum2->setActive(true);
    m_difficultyColumn->setActive(true);
    m_difficultyColumnNum1->setActive(true);
    m_difficultyColumnNum2->setActive(true);
    m_difficultyBomb->setActive(true);
    m_difficultyBombNum1->setActive(true);
    m_difficultyBombNum2->setActive(true);

    m_difficultyRow->select();

    m_explosionTexture.loadFromFile("../sprites/explosion.png");
    m_explosionSoundBuffer.loadFromFile("../audio/sounds/explosion.ogg");
}

void Game::instantiate()
{
    m_gameMusic.openFromFile("../audio/music/game/game_" + std::to_string(randomInt(1, m_gameSongNum)) + ".mp3");
    m_gameMusic.setLoop(true);
    m_gameMusic.setVolume(20.f);
    m_gameMusic.play();

    for (Soggy* soggy : m_sogArray)
    {
        delete soggy;
    }

    m_sogArray.clear();

    if (m_numberOfBombs >= m_rows * m_columns)
    {
        m_numberOfBombs = (m_rows * m_columns) - 9;
    }
    m_tileset->init(m_rows, m_columns, m_numberOfBombs, m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
        m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);

    m_firstSpawnPosX = 960 - (m_columns * 16);

    //                 540
    m_firstSpawnPosY = 636 - (m_rows * 16);

    m_spawnPosX = m_firstSpawnPosX;
    m_spawnPosY = m_firstSpawnPosY;

    for (int i = 0; i < m_rows * m_columns; i++)
    {
        m_tileset->activate(m_spawnPosX, m_spawnPosY);
        if (m_columnNumber + 1 == m_columns)
        {
            m_spawnPosX = m_firstSpawnPosX;
            m_spawnPosY += 32;
            m_columnNumber = -1;
        }
        else
        {
            m_spawnPosX += 32;
        }
        m_columnNumber++;
    }

    m_tileset->getTileArray()[0][0]->select();

    // Bomb counter

    m_tileset->spawnBombCounter(896, m_firstSpawnPosY - 96);
}

void Game::restart()
{
    updateDifficultyCounters();
    m_isMainMenuActive = true;
    m_mainMenuSelection = true;
    m_isPauseMenuActive = false;
    m_pauseMenuSelection = true;
    m_isDifficultyMenuActive = false;
    m_isSogging = false;
    m_difficultyMenuSelection = 0;
    gameOver = false;
    m_tileset->restart();
    if (!m_difficultyRow->getIsSelected())
        m_difficultyRow->select();
    else if(m_difficultyColumn->getIsSelected())
        m_difficultyColumn->select();
    else if (m_difficultyBomb->getIsSelected())
        m_difficultyBomb->select();
    m_gameMusic.stop();
    m_menuMusic.openFromFile("../audio/music/menu/menu_" + std::to_string(randomInt(1, m_menuSongNum)) + ".mp3");
    m_menuMusic.play();
    m_sogMusic.stop();

    for (Soggy* soggy : m_sogArray)
    {
        delete soggy;
    }

    m_sogArray.clear();
}

void Game::pauseSounds() const
{
    for (Soggy* soggy : m_sogArray)
    {
        soggy->pauseSound();
    }
}

void Game::resumeSounds() const
{
    for (Soggy* soggy : m_sogArray)
    {
        soggy->resumeSound();
    }
}

void Game::spawnSog(int sogSize, int posX, int posY, float rot,
    float rotFact, float speedXFact, float speedYFact, float speedX, float speedY, float rotSpeed)
{
    m_sogMusic.play();
    Soggy* soggy = new Soggy;
    m_sogArray.push_back(soggy);
    soggy->init(m_sogTexture, m_explosionTexture, m_explosionSoundBuffer, sogSize, posX, posY, rot, rotFact, speedXFact, speedYFact, speedX, speedY, rotSpeed);
}

void Game::checkUnactiveSogs()
{
    std::vector<int> positions;
    for (int i = 0; i < m_sogArray.size(); i++)
    {
        if (!m_sogArray[i]->getActive())
        {
            positions.push_back(i);
            delete m_sogArray[i];
        }
    }

    for (int i = 0; i < positions.size(); i++)
    {
        m_sogArray.erase(m_sogArray.begin() + positions[i] - i);
    }
}

void Game::updateDifficultyCounters()
{
    m_difficultyRowNum1->setValue(m_rows / 10);
    m_difficultyRowNum1->changeTile(m_difficultyRowNum1->getValue());
    m_difficultyRowNum2->setValue(m_rows - (m_rows / 10 * 10));
    m_difficultyRowNum2->changeTile(m_difficultyRowNum2->getValue());

    m_difficultyColumnNum1->setValue(m_columns / 10);
    m_difficultyColumnNum1->changeTile(m_difficultyColumnNum1->getValue());
    m_difficultyColumnNum2->setValue(m_columns - (m_columns / 10 * 10));
    m_difficultyColumnNum2->changeTile(m_difficultyColumnNum2->getValue());

    m_difficultyBombNum1->setValue(m_numberOfBombs / 10);
    m_difficultyBombNum1->changeTile(m_difficultyBombNum1->getValue());
    m_difficultyBombNum2->setValue(m_numberOfBombs - (m_numberOfBombs / 10 * 10));
    m_difficultyBombNum2->changeTile(m_difficultyBombNum2->getValue());
}

int Game::randomInt(int min, int max)
{
    if (min > max)
    {
        int old = min;
        min = max;
        max = old;
    }
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}