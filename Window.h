#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
class Ball;
class Player;
class Window
{
public:
	Window(const int screenWidth, const int screenHeight);
	~Window();

	//Getters
	SDL_Surface* getWindowSurface() const { return m_windowSurface; }
	SDL_Window* getWindow() const { return m_window; }
	SDL_Renderer* getRenderer() const { return m_renderer; }

	int getScreenHeight() const { return m_screenHeight; }
	int getScreenWidth() const { return m_screenWidth; }

private:
	SDL_Window* m_window = nullptr;
	SDL_Surface* m_windowSurface = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	void createWindow(); //Create SDL Window
	void createWindowSurface(); //Create window surface
	void createRenderer(); //Create SDL Renderer

						   //Size of screen
	int m_screenWidth;
	int m_screenHeight;
};

#endif // !WINDOW_H
