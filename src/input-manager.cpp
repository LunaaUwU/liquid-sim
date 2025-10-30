#include "input-manager.h"

std::vector<InputManager::MouseScrollCallback> InputManager::m_scrollCallbacks;
std::vector<InputManager::MouseButtonCallback> InputManager::m_leftClickCallbacks;
std::vector<InputManager::MouseButtonCallback> InputManager::m_rightClickCallbacks;
std::vector<InputManager::MouseButtonCallback> InputManager::m_leftClickReleaseCallbacks;
std::vector<InputManager::MouseButtonCallback> InputManager::m_rightClickReleaseCallbacks;

void InputManager::onScroll(const MouseScrollCallback& callback)
{
    m_scrollCallbacks.push_back(callback);
}

void InputManager::onLeftClick(const MouseButtonCallback& callback)
{
    m_leftClickCallbacks.push_back(callback);
}

void InputManager::onRightClick(const MouseButtonCallback& callback)
{
    m_rightClickCallbacks.push_back(callback);
}

void InputManager::onLeftClickRelease(const MouseButtonCallback& callback)
{
    m_leftClickReleaseCallbacks.push_back(callback);
}

void InputManager::onRightClickRelease(const MouseButtonCallback& callback)
{
    m_rightClickReleaseCallbacks.push_back(callback);
}

void InputManager::processEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        for (auto& callback : m_scrollCallbacks)
            if (callback(event.mouseWheelScroll.delta)) break; // stop once handled
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (auto& callback : m_leftClickCallbacks)
                if (callback()) break; // stop once handled
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            for (auto& callback : m_rightClickCallbacks)
                if (callback()) break; // stop once handled
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (auto& callback : m_leftClickReleaseCallbacks)
                if (callback()) break; // stop once handled
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            for (auto& callback : m_rightClickReleaseCallbacks)
                if (callback()) break; // stop once handled
        }
    }
}
