
#include <iostream>
#include <iomanip>
// #include <bits/stdc++.h>

#include "controller/DockerAPIController.hpp"
#include "controller/SwaggerController.hpp"
#include "AppComponent.hpp"
#include "utils/ColorUtils.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

typedef oatpp::web::protocol::http::Status Status;

void run(const oatpp::base::CommandLineArguments &args)
{
	AppComponent components(args);

	const auto &requestExecutor = components.requestExecutor.getObject();

	std::cout << ColorUtils::yellow("\nTrying to connect to DOCKER server\n\n");
	try {
		const auto &headers = oatpp::web::protocol::http::Headers();

		const auto &infoResponse = requestExecutor->executeOnce("GET", "info", headers, nullptr, requestExecutor->getConnection());
		if (infoResponse->getStatusCode() == Status::CODE_200.code) {
			const auto &apiObjectMapper = components.apiObjectMapper.getObject();

			const auto &infoResponseBody = infoResponse->readBodyToString();
			/*const auto& json = apiObjectMapper->readFromString<oatpp::Fields<oatpp::Any>>(infoResponseBody);
      		auto Name = json.getValueByKey("Name");
      		std::cout << Name->type << "\n";*/
			const auto &info = apiObjectMapper->readFromString<oatpp::Object<DockerInfo>>(infoResponseBody);

			const auto &versionResponse = requestExecutor->executeOnce("GET", "version", headers, nullptr, requestExecutor->getConnection());
			if (versionResponse->getStatusCode() == Status::CODE_200.code) {
				const auto &versionResponseBody = versionResponse->readBodyToString();

				const auto &version = apiObjectMapper->readFromString<oatpp::Object<DockerVersion>>(versionResponseBody);

				std::cout << ColorUtils::green("Server info:\n");
				std::cout << ColorUtils::cyan("Name: ") << ColorUtils::red(info->Name) << "\n";
				std::cout << ColorUtils::cyan("CPU core: ") << ColorUtils::red(std::to_string(info->NCPU)) << "\n";

				if (std::to_string(info->MemTotal).length() > 9)
					std::cout << ColorUtils::cyan("Memory: ") << std::setprecision(3) << ColorUtils::RED << info->MemTotal / 1073753975.19 << " GB\n"
							  << ColorUtils::RESET;
				else
					std::cout << ColorUtils::cyan("Memory: ") << std::setprecision(0) << ColorUtils::RED << info->MemTotal / 1048584 << " MB\n"
							  << ColorUtils::RESET;

				std::cout << ColorUtils::cyan("Operating System: ") << ColorUtils::red(info->OperatingSystem) << "\n";
				std::cout << ColorUtils::cyan("OS Version: ") << ColorUtils::red(info->OSVersion) << "\n";
				std::cout << ColorUtils::cyan("OS Type: ") << ColorUtils::red(info->OSType) << "\n";
				std::cout << ColorUtils::cyan("Kernel Version: ") << ColorUtils::red(info->KernelVersion) << "\n";
				std::cout << ColorUtils::cyan("Architecture: ") << ColorUtils::red(info->Architecture) << "\n";
				std::cout << ColorUtils::cyan("Arch: ") << ColorUtils::red(version->Arch) << "\n";
				std::cout << ColorUtils::cyan("Images: ") << ColorUtils::red(std::to_string(info->Images)) << "\n";
				std::cout << ColorUtils::cyan("Containers: ") << ColorUtils::red(std::to_string(info->Containers)) << "\n";
				std::cout << ColorUtils::cyan("Containers Running: ") << ColorUtils::red(std::to_string(info->ContainersRunning)) << "\n";

				std::cout << ColorUtils::green("\nDocker info:\n");
				std::cout << ColorUtils::cyan("Docker Version: ") << ColorUtils::red(version->Version) << "\n";
				std::cout << ColorUtils::cyan("Api Version: ") << ColorUtils::red(version->ApiVersion) << "\n";
				std::cout << ColorUtils::cyan("Min API Version: ") << ColorUtils::red(version->MinAPIVersion) << "\n";
			}
		}
	} catch (const std::exception &e) {
		std::cerr << ColorUtils::RED << e.what() << "\n\n"
				<< "Shutting down the application\n" << ColorUtils::RESET;
		throw std::exception();
	}

	const auto router = components.httpRouter.getObject();

	// oatpp::web::server::api::Endpoints docEndpoints;

	// docEndpoints.append(router->addController(SwaggerController::createShared())->getEndpoints());

	router->addController(SwaggerController::createShared());
	router->addController(DockerAPIController::createShared());

	/* create server */
	oatpp::network::Server server(components.serverConnectionProvider.getObject(), components.serverConnectionHandler.getObject());

	std::cout << ColorUtils::magenta("\n===============================\n");
	std::cout << ColorUtils::green("Server is running at port: ") << ColorUtils::yellow(components.serverConnectionProvider.getObject()->getProperty("port").toString());
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
		std::cerr << ColorUtils::RED << "'DOCKER_SERVER_IP' is not provided through environment variable\n"
				  << ColorUtils::RESET;
		return 1;
	}

	oatpp::base::Environment::init();

	try
	{
		run(oatpp::base::CommandLineArguments(argc, argv));
	}
	catch (const std::exception &e)
	{
		/* Print how much objects were created during app running, and what have left-probably leaked */
		/* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
		std::cout << "\nEnvironment:\n";
		std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
		std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

		oatpp::base::Environment::destroy();
		return 1;
	}

	return 0;
}
