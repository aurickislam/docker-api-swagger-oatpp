#ifndef docker_api_swagger_ColorUtils_hpp
#define docker_api_swagger_ColorUtils_hpp

#include <string.h>

class ColorUtils
{
private:
	ColorUtils()
	{
	}
public:
	constexpr static const char *RESET = "\033[0m";
	
	constexpr static const char *BLACK = "\033[30m";
	constexpr static const char *RED = "\033[31m";
	constexpr static const char *GREEN = "\033[32m";
	constexpr static const char *YELLOW = "\033[33m";
	constexpr static const char *BLUE = "\033[34m";
	constexpr static const char *MAGENTA = "\033[35m";
	constexpr static const char *CYAN = "\033[36m";
	constexpr static const char *WHITE = "\033[37m";
	
	constexpr static const char *BOLD_BLACK = "\033[1m\033[30m";
	constexpr static const char *BOLD_RED = "\033[1m\033[31m";
	constexpr static const char *BOLD_GREEN = "\033[1m\033[31m";
	constexpr static const char *BOLD_YELLOW = "\033[1m\033[31m";
	constexpr static const char *BOLD_BLUE = "\033[1m\033[31m";
	constexpr static const char *BOLD_MAGENTA = "\033[1m\033[31m";
	constexpr static const char *BOLD_CYAN = "\033[1m\033[31m";
	constexpr static const char *BOLD_WHITE = "\033[1m\033[31m";

public:
	static std::string black(std::string text)
	{
		return BLACK + text + RESET;
	}

	static std::string red(std::string text)
	{
		return RED + text + RESET;
	}

	static std::string green(std::string text)
	{
		return GREEN + text + RESET;
	}

	static std::string yellow(std::string text)
	{
		return YELLOW + text + RESET;
	}

	static std::string blue(std::string text)
	{
		return BLUE + text + RESET;
	}

	static std::string magenta(std::string text)
	{
		return MAGENTA + text + RESET;
	}

	static std::string cyan(std::string text)
	{
		return CYAN + text.append(RESET);
	}

	static std::string white(std::string text)
	{
		return WHITE + text.append(RESET);
	}

};

#endif /* docker_api_swagger_ColorUtils_hpp */