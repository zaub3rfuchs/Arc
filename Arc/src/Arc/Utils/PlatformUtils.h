#pragma once
#include <string>
#include <optional>
#include <filesystem>

namespace ArcEngine {

	class FileDialogs
	{
	public:
		// These return empty strings if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
		static std::string getFileName(const std::filesystem::path& path);
	};

	class Time
	{
	public:
		static float GetTime();
	};
}
