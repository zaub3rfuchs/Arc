#pragma once
#include <string>
#include <optional>
#include <filesystem>

namespace ArcEngine {

	class FileDialogs
	{
	public:
		// These return empty strings if cancelled
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
		static std::string getFileName(const std::filesystem::path& path);
	};

}
