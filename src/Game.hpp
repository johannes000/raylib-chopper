#pragma once
#include "Utility\Includes.hpp"

class Game {
public:
	Game();
	~Game();

	i32 Run();
	void InitGame();
	void ProcessInput();
	void RenderGame();
	void UpdateGame();
	void Shutdown();

private:
	std::string mGametitle;

	raylib::Window mWindow;
	raylib::Camera2D mCamera;
};
