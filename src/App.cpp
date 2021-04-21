
#include "controller/DockerAPIController.hpp"
#include "controller/SwaggerController.hpp"
#include "./AppComponent.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run(const oatpp::base::CommandLineArguments& args) {

  AppComponent components(args);

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
  
  OATPP_LOGD("Server", "Running on port %s...", components.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
  
  server.run();

}

/**
 *  main
 */
int main(int argc, const char * argv[]) {

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
