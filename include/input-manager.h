#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <functional>

class InputManager
{
public:

	using MouseScrollCallback = std::function<bool(float delta)>;
	using MouseButtonCallback = std::function<bool()>;

	static void onScroll(const MouseScrollCallback& callback);
	static void onLeftClick(const MouseButtonCallback& callback);
	static void onLeftClickRelease(const MouseButtonCallback& callback);
	static void onRightClick(const MouseButtonCallback& callback);
	static void onRightClickRelease(const MouseButtonCallback& callback);


	static void processEvent(const sf::Event& event);

private:
	static std::vector<MouseScrollCallback> m_scrollCallbacks;
	static std::vector<MouseButtonCallback> m_leftClickCallbacks;
	static std::vector<MouseButtonCallback> m_rightClickCallbacks;
	static std::vector<MouseButtonCallback> m_leftClickReleaseCallbacks;
	static std::vector<MouseButtonCallback> m_rightClickReleaseCallbacks;

};