
#ifndef docker_api_swagger_AppComponent_hpp
#define docker_api_swagger_AppComponent_hpp

#include "utils/JSONUtils.hpp"
#include "SwaggerComponent.hpp"

#include "oatpp-curl/RequestExecutor.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"

#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"
#include "oatpp/core/macro/component.hpp"

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent
{
private:
	constexpr static const char *TAG = "AppComponent";
	oatpp::base::CommandLineArguments m_cmdArgs;
	/**
	 *  Swagger component
	 */
	SwaggerComponent swaggerComponent;

public:
	AppComponent(const oatpp::base::CommandLineArguments &cmdArgs) : m_cmdArgs(cmdArgs)
	{
	}

public:
	/**
	 *  Create ConnectionProvider component which listens on the port
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)
	([] {
		return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8001, oatpp::network::Address::IP_4});
	}());

	/**
	 *  Create Router component
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
	([] {
		return oatpp::web::server::HttpRouter::createShared();
	}());

	/**
	 *  Create ConnectionHandler component which uses Router component to route requests
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
	([] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
		return oatpp::web::server::HttpConnectionHandler::createShared(router);
	}());

	/**
	 *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
	([] {
		const auto &objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
		// objectMapper->getDeserializer()->getConfig()->allowUnknownFields = false;
		objectMapper->getSerializer()->getConfig()->useBeautifier = true;
		return objectMapper;
	}());

	/**
	 *  Create JSONUtils component to serialize/deserialize DTOs
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<JSONUtils>, jsonUtils)
	([] {
		return std::make_shared<JSONUtils>();
	}());

	/**
	 *  Create DockerAPIClient component to make API calls
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::client::HttpRequestExecutor>, requestExecutor)
	([] {
		const oatpp::String &ip = std::getenv("DOCKER_SERVER_IP");
		std::cout << "\nDOCKER_SERVER_IP: " << ip->std_str() << "\n";

		const unsigned short port = atoi(std::getenv("DOCKER_SERVER_PORT"));
		std::cout << "DOCKER_SERVER_PORT: " << port << "\n";

		const auto &connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared({ip, port});

		return oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
	}());
};

#endif /* docker_api_swagger_AppComponent_hpp */
