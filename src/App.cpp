
#include <iostream>

#include "controller/DockerAPIController.hpp"
#include "controller/SwaggerController.hpp"
#include "AppComponent.hpp"
#include "dto/DTOs.hpp"
#include "utils/ColorUtils.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

#include <bits/stdc++.h>

typedef oatpp::web::protocol::http::Status Status;

void run(const oatpp::base::CommandLineArguments &args)
{
	// std::cout << "\033[31m" << "Error!" << "\033[0m" << std::endl;

	AppComponent components(args);

	const auto &requestExecutor = components.requestExecutor.getObject();

	std::cout << ColorUtils::cyan("\n@trying to connect to DOCKER server\n\n");
	try
	{
		const auto &headers = oatpp::web::protocol::http::Headers();

		const auto &infoResponse = requestExecutor->executeOnce("GET", "info", headers, nullptr, requestExecutor->getConnection());
		if (infoResponse->getStatusCode() == Status::CODE_200.code)
		{
			const auto &apiObjectMapper = components.apiObjectMapper.getObject();

			const auto &infoResponseBody = infoResponse->readBodyToString();
			/*const auto& json = apiObjectMapper->readFromString<oatpp::Fields<oatpp::Any>>(infoResponseBody);
      		auto Name = json.getValueByKey("Name");
      		std::cout << Name->type << "\n";*/
			const auto &info = apiObjectMapper->readFromString<oatpp::Object<DockerInfo>>(infoResponseBody);


			const auto &versionResponse = requestExecutor->executeOnce("GET", "version", headers, nullptr, requestExecutor->getConnection());
			if (versionResponse->getStatusCode() == Status::CODE_200.code)
			{
				const auto &versionResponseBody = versionResponse->readBodyToString();

				const auto &version = apiObjectMapper->readFromString<oatpp::Object<DockerVersion>>(versionResponseBody);

				std::cout << ColorUtils::green("Server info:\n");
				std::cout << ColorUtils::blue("Name: ") << ColorUtils::red(info->Name->std_str()) << "\n";
				std::cout << ColorUtils::blue("CPU core: ") << ColorUtils::red(std::to_string(info->NCPU)) << "\n";

				if (std::to_string(info->MemTotal).length() > 9)
					std::cout << ColorUtils::blue("Memory: ") << std::setprecision(3) << ColorUtils::RED << info->MemTotal / 1073753975.19 << " GB\n" << ColorUtils::RESET;
				else
					std::cout << ColorUtils::blue("Memory: ") << std::setprecision(0) << ColorUtils::RED<< info->MemTotal / 1048584 << " MB\n" << ColorUtils::RESET;

				std::cout << ColorUtils::blue("Operating System: ") << ColorUtils::red(info->OperatingSystem->std_str()) << "\n";
				std::cout << ColorUtils::blue("OS Version: ") << ColorUtils::red(info->OSVersion->std_str()) << "\n";
				std::cout << ColorUtils::blue("OS Type: ") << ColorUtils::red(info->OSType->std_str()) << "\n";
				std::cout << ColorUtils::blue("Kernel Version: ") << ColorUtils::red(info->KernelVersion->std_str()) << "\n";
				std::cout << ColorUtils::blue("Architecture: ") << ColorUtils::red(info->Architecture->std_str()) << "\n";
				std::cout << ColorUtils::blue("Arch: ") << ColorUtils::red(version->Arch->std_str()) << "\n";
				std::cout << ColorUtils::blue("Images: ") << ColorUtils::red(std::to_string(info->Images)) << "\n";
				std::cout << ColorUtils::blue("Containers: ") << ColorUtils::red(std::to_string(info->Containers)) << "\n";
				std::cout << ColorUtils::blue("Containers Running: ") << ColorUtils::red(std::to_string(info->ContainersRunning)) << "\n";

				std::cout << ColorUtils::green("\nDocker info:\n");
				std::cout << ColorUtils::blue("Docker Version: ") << ColorUtils::red(version->Version->std_str()) << "\n";
				std::cout << ColorUtils::blue("Api Version: ") << ColorUtils::red(version->ApiVersion->std_str()) << "\n";
				std::cout << ColorUtils::blue("Min API Version: ") << ColorUtils::red(version->MinAPIVersion->std_str()) << "\n";
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << "\n\n";
		std::cout << "Shutting down the application\n";
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

	std::cout << ColorUtils::magenta("\n===============================\n");
	std::cout << ColorUtils::cyan("Server is running at port: ") << ColorUtils::red(components.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
	std::cout << ColorUtils::magenta("\n===============================\n\n");
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
		std::cerr << ColorUtils::RED << "'DOCKER_SERVER_IP' is not provided through environment variable\n" << ColorUtils::RESET;
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
