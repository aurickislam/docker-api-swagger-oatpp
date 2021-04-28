
#ifndef docker_api_swagger_SwaggerController_hpp
#define docker_api_swagger_SwaggerController_hpp

#include "swagger/Types.hpp"
#include "swagger/Resources.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/protocol/http/outgoing/StreamingBody.hpp"

#include "oatpp/core/data/stream/BufferStream.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class SwaggerController : public oatpp::web::server::api::ApiController
{
private:
	constexpr static const char *TAG = "SwaggerController";
	OATPP_COMPONENT(std::shared_ptr<swagger::Resources>, m_resources);

private:
	std::shared_ptr<ApiController::OutgoingResponse> getFile(const String &filename)
	{
		if (m_resources->isStreaming())
		{
			auto body = std::make_shared<oatpp::web::protocol::http::outgoing::StreamingBody>(m_resources->getResourceStream(filename->c_str()));
			return OutgoingResponse::createShared(Status::CODE_200, body);
		}
		return createResponse(Status::CODE_200, m_resources->getResource(filename->c_str()));
	}

public:
	SwaggerController(const std::shared_ptr<ObjectMapper> &objectMapper) : oatpp::web::server::api::ApiController(objectMapper)
	{
	}

public:
	static std::shared_ptr<SwaggerController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
	{
		return std::make_shared<SwaggerController>(objectMapper);
	}

	ENDPOINT("GET", "/", root)
	{
		return getFile("index.html");
	}

	ENDPOINT("GET", "swagger/{filename}", getUIResource, PATH(String, filename))
	{
		return getFile(filename);
	}
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* docker_api_swagger_SwaggerController_hpp */
