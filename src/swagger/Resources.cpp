
#include "Resources.hpp"
#include <stdio.h>
#include <fstream>

namespace swagger
{
	Resources::Resources(const oatpp::String &resDir, const bool streaming)
	{
		if (!resDir || resDir->size() == 0) {
			throw std::runtime_error("[oatpp::swagger::Resources::Resources()]: Invalid resDir path. Please specify full path to oatpp-swagger/res folder");
		}

		m_resDir = resDir;
		if (m_resDir->data()[m_resDir->size() - 1] != '/') {
			m_resDir = m_resDir + "/";
		}

		m_streaming = streaming;
	}

	void Resources::cacheResource(const char *fileName)
	{
		m_resources[fileName] = loadFromFile(fileName);
	}

	oatpp::String Resources::loadFromFile(const char *fileName)
	{
		const auto &fullFilename = m_resDir + fileName;

		// auto file = std::ifstream(fullFilename->c_str(), std::ios::in | std::ios::binary | std::ios::ate);
		std::ifstream file(fullFilename->c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		if (file.is_open())
		{
			const auto &result = oatpp::String((v_int32)file.tellg());
			file.seekg(0, std::ios::beg);
			file.read((char *)result->data(), result->size());
			file.close();
			return result;
		}

		OATPP_LOGE("swagger::Resources::loadFromFile()", "Can't load file '%s'", fullFilename->c_str());
		throw std::runtime_error("[swagger::Resources::loadFromFile(...)]: Can't load file. Please make sure you specified full path to docker-api-swagger-oatpp/res folder");
	}

	oatpp::String Resources::getResource(const oatpp::String &filename)
	{
		const auto &it = m_resources.find(filename);
		if (it != m_resources.end()) {
			return it->second;
		}

		throw std::runtime_error(
			"[swagger::Resources::getResource(...)]: Resource file not found. "
			"Please make sure: "
			"1. You are using correct version of oatpp-swagger."
			"2. docker-api-swagger-oatpp/res is not empty."
			"3. You specified correct full path to docker-api-swagger-oatpp/res folder");
	}

	std::shared_ptr<Resources::ReadCallback> Resources::getResourceStream(const oatpp::String &filename)
	{
		try
		{
			return std::make_shared<ReadCallback>(m_resDir + filename);
		}
		catch (std::runtime_error &e)
		{
			throw std::runtime_error(
				"[swagger::Resources::getResource(...)]: Resource file not found."
				"Please make sure:"
				"1. You are using correct version of oatpp-swagger."
				"2. docker-api-swagger-oatpp/res is not empty."
				"3. You specified correct full path to docker-api-swagger-oatpp/res folder");
		}
	}

	Resources::ReadCallback::ReadCallback(const oatpp::String &file) : m_file(file), m_stream(file->c_str())
	{
	}

	oatpp::v_io_size Resources::ReadCallback::read(void *buffer, v_buff_size count, oatpp::async::Action &action)
	{
		return m_stream.read(buffer, count, action);
	}

	bool Resources::hasEnding(std::string fullString, std::string const &ending) const {
		std::transform(fullString.begin(), fullString.end(), fullString.begin(),
					[](unsigned char c) { return std::tolower(c); });
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		} else {
			return false;
		}
	}

	std::string Resources::getMimeType(const std::string &filename) const {
		if (hasEnding(filename, ".html")) return "text/html";
		if (hasEnding(filename, ".jpg")) return "image/jpeg";
		if (hasEnding(filename, ".jpeg")) return "image/jpeg";
		if (hasEnding(filename, ".png")) return "image/png";
		if (hasEnding(filename, ".gif")) return "image/gif";
		if (hasEnding(filename, ".css")) return "text/css";
		if (hasEnding(filename, ".js")) return "text/javascript";
		if (hasEnding(filename, ".xml")) return "text/xml";
		return "text/plain";
	}

}
