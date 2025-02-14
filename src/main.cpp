#include "Utility\Includes.hpp"
#include "Game.hpp"

void RaylibLogCallback(int logLevel, const char *text, va_list args) {
	char buffer[4096];
	vsnprintf(buffer, sizeof(buffer), text, args);
	switch (logLevel) {
		case LOG_ERROR:
			LOG.error("Raylib: {}", buffer);
			break;
		case LOG_WARNING:
			LOG.warning("Raylib: {}", buffer);
			break;
		case LOG_INFO:
			LOG.info("Raylib: {}", buffer);
			break;
		case LOG_FATAL:
			LOG.fatal("Raylib: {}", buffer);
			break;
		default:
			LOG.info("Raylib: {}", buffer);
			break;
	}
}

i32 main(int /* argc */, char ** /* argv */) {
	SetTraceLogCallback(RaylibLogCallback);

	Game game;
	return game.Run();
}