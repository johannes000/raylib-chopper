#include "Utility\Includes.hpp"
#include "Game.hpp"

void RaylibLogCallback(int logLevel, const char *text, va_list args) {
	auto log = spdlog::get("RAY");
	char buffer[4096];
	vsnprintf(buffer, sizeof(buffer), text, args);
	switch (logLevel) {
		case LOG_ERROR:
			log->error(buffer);
			break;
		case LOG_WARNING:
			log->warn(buffer);
			break;
		case LOG_INFO:
			log->info(buffer);
			break;
		case LOG_FATAL:
			log->critical(buffer);
			break;
		default:
			log->info(buffer);
			break;
	}
}

i32 main(int /* argc */, char ** /* argv */) {
	AddLogger("RAY");
	AddLogger("GAM");
	AddLogger("ENT");

	SetTraceLogCallback(RaylibLogCallback);

	Game game;
	return game.Run();
}