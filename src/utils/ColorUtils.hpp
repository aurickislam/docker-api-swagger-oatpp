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
	constexpr static const char* RESET = "\033[0m";

	constexpr static const char* BLACK = "\033[30m";
	constexpr static const char* RED = "\033[31m";
	constexpr static const char* GREEN = "\033[32m";
	constexpr static const char* YELLOW = "\033[33m";
	constexpr static const char* BLUE = "\033[34m";
	constexpr static const char* MAGENTA = "\033[35m";
	constexpr static const char* CYAN = "\033[36m";
	constexpr static const char* WHITE = "\033[37m";

	/*constexpr static const char* BOLD_BLACK = "\033[1m\033[30m";
	constexpr static const char* BOLD_RED = "\033[1m\033[31m";
	constexpr static const char* BOLD_GREEN = "\033[1m\033[32m";
	constexpr static const char* BOLD_YELLOW = "\033[1m\033[33m";
	constexpr static const char* BOLD_BLUE = "\033[1m\033[34m";
	constexpr static const char* BOLD_MAGENTA = "\033[1m\033[35m";
	constexpr static const char* BOLD_CYAN = "\033[1m\033[36m";
	constexpr static const char* BOLD_WHITE = "\033[1m\033[37m";*/

public:
	static const std::string black(const std::string& text)
	{
		return BLACK + text + RESET;
	}

	static const std::string red(const std::string& text)
	{
		return RED + text + RESET;
	}

	static const std::string green(const std::string& text)
	{
		return GREEN + text + RESET;
	}

	static const std::string yellow(const std::string& text)
	{
		return YELLOW + text + RESET;
	}

	static const std::string blue(const std::string& text)
	{
		return BLUE + text + RESET;
	}

	static const std::string magenta(const std::string& text)
	{
		return MAGENTA + text + RESET;
	}

	static const std::string cyan(const std::string& text)
	{
		return CYAN + text + RESET;
	}

	static const std::string white(const std::string& text)
	{
		return WHITE + text + RESET;
	}

};

#endif /* docker_api_swagger_ColorUtils_hpp */