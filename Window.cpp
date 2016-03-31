#include "Window.h"

#include <assert.h>


Window::Window(const int screenWidth, const int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	createWindow();
	createWindowSurface();
	createRenderer();
}

Window::~Window()
{
	//Destroy window
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	//Free window surface
	//SDL_FreeSurface(m_windowSurface);
	m_windowSurface = nullptr;

	//Destroy renderer
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

void Window::createWindow()
{
	m_window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);
	assert(m_window != nullptr);
}

void Window::createWindowSurface()
{
	m_windowSurface = SDL_GetWindowSurface(m_window);
	assert(m_windowSurface != nullptr);
}

void Window::createRenderer()
{
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	assert(m_renderer != nullptr);
}



