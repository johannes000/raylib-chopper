#pragma once

#include <iostream>
#include <string>
#include <format>
#include <chrono>
#include <iomanip>
#include <sstream>

/*
 * TODO: In Files Loggen
 * TODO: Threadsafe
 */

// Log-Level
enum struct LogLevel {
	DEBUG,
	INFO,
	WARNING,
	ERROR
};

// Logger-Klasse
struct Logger {
	Logger(const Logger &) = delete;
	Logger &operator=(const Logger &) = delete;

	static Logger &getInstance() {
		static Logger instance;
		return instance;
	}
	// Log-Funktion mit variadischen Argumenten
	template <typename... Args>
	constexpr void log(LogLevel level, std::string_view format, Args &&...args) const {
		// Formatierte Nachricht erstellen
		std::string message = std::vformat(format, std::make_format_args(args...));

		// Zeitstempel erstellen
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		std::tm tm = *std::localtime(&time);

		// Log-Level als String
		std::string levelStr;
		switch (level) {
			case LogLevel::DEBUG:
				levelStr = "DEBUG";
				break;
			case LogLevel::INFO:
				levelStr = "INFO";
				break;
			case LogLevel::WARNING:
				levelStr = "WARNING";
				break;
			case LogLevel::ERROR:
				levelStr = "ERROR";
				break;
		}

		// Ausgabeformat erstellen
		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [" << levelStr << "] " << message;

		// Ausgabe in die Konsole
		std::cout << oss.str() << std::endl;
	}

	// Hilfsfunktionen für verschiedene Log-Level
	template <typename... Args>
	constexpr void debug(std::string_view format, Args &&...args) const {
		log(LogLevel::DEBUG, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	constexpr void info(std::string_view format, Args &&...args) const {
		log(LogLevel::INFO, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	constexpr void warning(std::string_view format, Args &&...args) const {
		log(LogLevel::WARNING, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	constexpr void error(std::string_view format, Args &&...args) const {
		log(LogLevel::ERROR, format, std::forward<Args>(args)...);
	}

private:
	Logger() = default;
};

#define LOG Logger::getInstance()