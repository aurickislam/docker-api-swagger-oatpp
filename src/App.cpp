
#include <iostream>

#include "controller/DockerAPIController.hpp"
#include "controller/SwaggerController.hpp"
#include "./AppComponent.hpp"
#include "dto/DTOs.hpp"

#include "oatpp/network/Server.hpp"

#include <bits/stdc++.h>

void run(const oatpp::base::CommandLineArguments &args)
{
	AppComponent components(args);

	const auto &requestExecutor = components.requestExecutor.getObject();

	std::cout << "\n@trying to connect to DOCKER server\n\n";
	try
	{
		const auto &headers = oatpp::web::protocol::http::Headers();

		const auto &infoResponse = requestExecutor->executeOnce("GET", "info", headers, nullptr, requestExecutor->getConnection());

		if (infoResponse->getStatusCode() == 200)
		{
			const auto &apiObjectMapper = components.apiObjectMapper.getObject();

			const auto &infoResponseBody = infoResponse->readBodyToString();
			/*const auto& json = apiObjectMapper->readFromString<oatpp::Fields<oatpp::Any>>(infoResponseBody);
      		auto Name = json.getValueByKey("Name");
      		std::cout << Name->type << "\n";*/
			const auto &info = apiObjectMapper->readFromString<oatpp::Object<DockerInfo>>(infoResponseBody);

			const auto &versionResponse = requestExecutor->executeOnce("GET", "version", headers, nullptr, requestExecutor->getConnection());
			if (versionResponse->getStatusCode() == 200)
			{
				const auto &versionResponseBody = versionResponse->readBodyToString();

				const auto &version = apiObjectMapper->readFromString<oatpp::Object<DockerVersion>>(versionResponseBody);

				std::cout << "Server info:\n";
				std::cout << "Name: " << info->Name->std_str() << "\n";
				std::cout << "CPU core: " << info->NCPU << "\n";

				if (std::to_string(info->MemTotal).length() > 9)
					std::cout << "Memory: " << std::setprecision(3) << info->MemTotal / 1073753975.19 << " GB\n";
				else
					std::cout << "Memory: " << std::setprecision(0) << info->MemTotal / 1048584 << " MB\n";

				std::cout << "Operating System: " << info->OperatingSystem->std_str() << "\n";
				std::cout << "OS Version: " << info->OSVersion->std_str() << "\n";
				std::cout << "OS Type: " << info->OSType->std_str() << "\n";
				std::cout << "Kernel Version: " << info->KernelVersion->std_str() << "\n";
				std::cout << "Architecture: " << info->Architecture->std_str() << "\n";
				std::cout << "Arch: " << version->Arch->std_str() << "\n";
				std::cout << "Images: " << info->Images << "\n";
				std::cout << "Containers: " << info->Containers << "\n";
				std::cout << "Containers Running: " << info->ContainersRunning << "\n";

				std::cout << "\nDocker info:\n";
				std::cout << "Docker Version: " << version->Version->std_str() << "\n";
				std::cout << "Api Version: " << version->ApiVersion->std_str() << "\n";
				std::cout << "Min API Version: " << version->MinAPIVersion->std_str() << "\n";
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << "\n\n";
		std::cerr << "Shutting down the application\n";
		exit(1);
	}

	auto router = components.httpRouter.getObject();

	auto docEndpoints = SwaggerController::Endpoints::createShared();

	auto swaggerController = SwaggerController::createShared();
	swaggerController->addEndpointsToRouter(router);

	docEndpoints->pushBackAll(swaggerController->getEndpoints());

	auto dockerAPIController = DockerAPIController::createShared();
	dockerAPIController->addEndpointsToRouter(router);

	docEndpoints->pushBackAll(dockerAPIController->getEndpoints());

	/* create server */
	oatpp::network::Server server(components.serverConnectionProvider.getObject(), components.serverConnectionHandler.getObject());

	std::cout << "\n===============================\n";
	std::cout << "Server is running at port: " << components.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str();
	std::cout << "\n===============================\n\n";
	OATPP_LOGI("App", " Server started!\n");

	server.run();
}

/**
 *  main
 */
int main(int argc, const char *argv[])
{
	if (!std::getenv("DOCKER_SERVER_IP"))
	{
		std::cerr << "'DOCKER_SERVER_IP' is not provided through environment veriable\n";
		return 1;
	}

	if (!std::getenv("DOCKER_SERVER_PORT"))
	{
		std::cerr << "'DOCKER_SERVER_PORT' is not provided through environment veriable\n";
		return 1;
	}

	oatpp::base::Environment::init();

	run(oatpp::base::CommandLineArguments(argc, argv));

	/* Print how much objects were created during app running, and what have left-probably leaked */
	/* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
	std::cout << "\nEnvironment:\n";
	std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
	std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

	oatpp::base::Environment::destroy();

	return 0;
}
