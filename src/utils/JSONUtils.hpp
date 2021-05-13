#ifndef docker_api_swagger_JSONUtils_hpp
#define docker_api_swagger_JSONUtils_hpp

#include "dto/DTOs.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

class JSONUtils
{
private:
	OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper);

public:
	const char* toJSON(const oatpp::Void& dto)
	{
		return apiObjectMapper->writeToString(dto)->c_str();
	}

	/*const char* toPrettyJSON(const oatpp::Void& dto)
	{
		return apiObjectMapper->writeToString(dto)->c_str();
	}*/
};

#endif /* docker_api_swagger_JSONUtils_hpp */