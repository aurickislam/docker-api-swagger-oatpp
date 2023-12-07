cmake_minimum_required(VERSION 3.1)

set(project_name docker-api-swagger-oatpp)

project(${project_name})

set(CMAKE_CXX_STANDARD 20)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/SwaggerComponent.hpp
        src/controller/DockerAPIController.hpp
        src/controller/SwaggerController.hpp
        src/dto/DTOs.hpp
        # src/utils/JSONUtils.hpp
        src/utils/HttpStatusUtils.hpp
        src/utils/ColorUtils.hpp
        src/swagger/Resources.cpp
        src/swagger/Resources.hpp
        src/swagger/Types.cpp
        src/swagger/Types.hpp
)

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-curl     1.3.0 REQUIRED)

## include directories

target_include_directories(${project_name}-lib
        PUBLIC src
)

## link libs

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-curl
)

#################################################################
## add executables

add_executable(${project_name}
        src/App.cpp
)

target_link_libraries(${project_name} ${project_name}-lib)
add_dependencies(${project_name} ${project_name}-lib)

# add_executable(${project_name}-test
#         test/tests.cpp
# )

# target_link_libraries(${project_name}-test ${project_name}-lib)
# add_dependencies(${project_name}-test ${project_name}-lib)

# enable_testing()
# add_test(project-tests ${project_name}-test)
