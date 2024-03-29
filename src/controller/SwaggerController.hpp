
#ifndef docker_api_swagger_oatpp_SwaggerController_hpp
#define docker_api_swagger_oatpp_SwaggerController_hpp

#include "swagger/Types.hpp"
#include "swagger/Resources.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/protocol/http/outgoing/StreamingBody.hpp"

// #include "oatpp/core/data/stream/BufferStream.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

typedef oatpp::web::protocol::http::outgoing::StreamingBody StreamingBody;

#include OATPP_CODEGEN_BEGIN(ApiController)

class SwaggerController final : public oatpp::web::server::api::ApiController
{
private:
	constexpr static const char *TAG = "SwaggerController";
	OATPP_COMPONENT(std::shared_ptr<swagger::Resources>, m_resources);

	std::shared_ptr<OutgoingResponse> getFile(const oatpp::String &filename) const
	{
		if (m_resources->isStreaming())
		{
			const auto &body = std::make_shared<StreamingBody>(m_resources->getResourceStream(filename->c_str()));
			return OutgoingResponse::createShared(Status::CODE_200, body);
		}
		return createResponse(Status::CODE_200, m_resources->getResource(filename->c_str()));
	}

public:
	explicit SwaggerController(const std::shared_ptr<ObjectMapper> &objectMapper) : ApiController(objectMapper)
	{
	}

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

#endif /* docker_api_swagger_oatpp_SwaggerController_hpp */
