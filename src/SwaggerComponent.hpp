
#ifndef docker_api_swagger_SwaggerComponent_hpp
#define docker_api_swagger_SwaggerComponent_hpp

#include "swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

/**
 *  Swagger ui is served at
 *  http://host:port/
 */
class SwaggerComponent {
public:
  /**
   *  Swagger-Ui Resources (../res)
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<swagger::Resources>, swaggerResources)([] {
    // Make sure to specify correct full path to ../res folder !!!
    return swagger::Resources::loadResources("../res");
  }());
  
};

#endif /* docker_api_swagger_SwaggerComponent_hpp */
