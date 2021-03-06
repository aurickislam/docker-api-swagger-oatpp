
#ifndef docker_api_swagger_Resources_hpp
#define docker_api_swagger_Resources_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/data/stream/ChunkedBuffer.hpp"
#include "oatpp/core/data/stream/FileStream.hpp"

#include <unordered_map>

namespace swagger
{
	/**
	 * This class is responsible for loading Swagger-UI resources.
	 */
	class Resources
	{
	private:
		oatpp::String m_resDir;
		std::unordered_map<oatpp::String, oatpp::String> m_resources;
		bool m_streaming;

	private:
		oatpp::String loadFromFile(const char *fileName);
		void cacheResource(const char *fileName);

		class ReadCallback : public oatpp::data::stream::ReadCallback
		{
		private:
			oatpp::String m_file;
			oatpp::data::stream::FileInputStream m_stream;

		public:
			ReadCallback(const oatpp::String &file);
			oatpp::v_io_size read(void *buffer, v_buff_size count, oatpp::async::Action &action) override;
		};

	public:
		/**
		 * Constructor.
		 * @param resDir - directory containing swagger-ui resources.
		 */
		Resources(const oatpp::String &resDir, bool streaming = false);

	public:
		/**
		 * Load and cache Swagger-UI resources.
		 * @param resDir - directory containing swagger-ui resources.
		 * @return - `std::shared_ptr` to Resources.
		 */
		static std::shared_ptr<Resources> loadResources(const oatpp::String &resDir)
		{
			const auto &res = std::make_shared<Resources>(resDir);

			res->cacheResource("favicon-16x16.png");
			res->cacheResource("favicon-32x32.png");
			res->cacheResource("index.html");
			res->cacheResource("swagger-ui.css");
			res->cacheResource("swagger-ui.css.map");
			res->cacheResource("swagger-ui-bundle.js");
			res->cacheResource("swagger-ui-bundle.js.map");
			/*res->cacheResource("oauth2-redirect.html");
			res->cacheResource("swagger-ui.js");
			res->cacheResource("swagger-ui.js.map");
			res->cacheResource("swagger-ui-es-bundle-core.js");
			res->cacheResource("swagger-ui-es-bundle-core.js.map");
			res->cacheResource("swagger-ui-es-bundle.js");
			res->cacheResource("swagger-ui-es-bundle.js.map");*/
			res->cacheResource("swagger-ui-standalone-preset.js");
			res->cacheResource("swagger-ui-standalone-preset.js.map");
			res->cacheResource("swagger.json");

			return res;
		}

		/**
		 * Stream Swagger-UI resources directly from disk.
		 * @param resDir - directory containing swagger-ui resources.
		 * @return - `std::shared_ptr` to Resources.
		 */
		static std::shared_ptr<Resources> streamResources(const oatpp::String &resDir)
		{
			return std::make_shared<Resources>(resDir, true);
		}

		/**
		 * Get cached resource by filename.
		 * @param filename - name of the resource file.
		 * @return -& id:oatpp::String; containing resource binary data.
		 */
		oatpp::String getResource(const oatpp::String &filename);

		/**
		 * Get streamed resource by filename.
		 * @param filename - name of the resource file.
		 * @return - `std::shared_ptr` to& id:oatpp::data::stream::ReadCallback; containing resource binary data stream."
		 */
		std::shared_ptr<ReadCallback> getResourceStream(const oatpp::String &filename);

		/**
		 * Returns true if this is a streaming ressource instance.
		 * @return
		 */
		bool isStreaming()
		{
			return m_streaming;
		}
	};
}

#endif /* docker_api_swagger_Resources_hpp */
