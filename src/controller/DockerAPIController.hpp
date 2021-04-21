
#ifndef docker_api_swagger_DockerAPIController_hpp
#define docker_api_swagger_DockerAPIController_hpp

#include "dto/DTOs.hpp"
#include "utils/StatusUtils.hpp"
#include "utils/JSONUtils.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/protocol/http/outgoing/StreamingBody.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/core/data/stream/BufferStream.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <iostream>

using namespace std;

#include OATPP_CODEGEN_BEGIN(ApiController)

class DockerAPIController : public oatpp::web::server::api::ApiController
{
private:
    OATPP_COMPONENT(std::shared_ptr<utils::JSONUtils>, jsonUtils);
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::client::HttpRequestExecutor>, requestExecutor);

private:
    std::shared_ptr<OutgoingResponse> createErroeResponse(const Status& status, const String& message)
    {
        auto dto = ErrorResponseDto::createShared();
        dto->statusCode = status.code;
        dto->error = status.description;
        dto->message = message;
        return createDtoResponse(status, dto);
    }

    std::shared_ptr<OutgoingResponse> createSuccessResponse(const Status& status, const String& message)
    {
        auto dto = SuccessResponseDto::createShared();
        dto->message = message;
        return createDtoResponse(status, dto);
    }

    std::shared_ptr<OutgoingResponse> createJSONResponse(const Status& status, const oatpp::web::protocol::http::Headers& responseHeader, const String& json)
    {
        auto response = createResponse(status, json);
        for(auto& head : responseHeader.getAll()) {
            // OATPP_LOGD("head", " %s = %s", head.first.std_str().c_str(), head.second.getData());
            if (head.first.std_str() != Header::TRANSFER_ENCODING)
                response->putHeader(head.first.std_str().c_str(), head.second.std_str().c_str());
        }
        return response;
    }

public:
    DockerAPIController(const std::shared_ptr<ObjectMapper> &objectMapper)
     : oatpp::web::server::api::ApiController(objectMapper)
    {}

public:
    static std::shared_ptr<DockerAPIController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    {
        return std::make_shared<DockerAPIController>(objectMapper);
    }

    ENDPOINT("GET", "*", dockerGet, REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        OATPP_LOGI("GET", " dockerGet");

        const oatpp::web::protocol::http::Headers& requestHeader = request->getHeaders();

        OATPP_LOGI("pathVariables", " getPathTail: %s\n", request->getPathTail()->getData());

        try
        {
            auto response = requestExecutor->executeOnce("GET", request->getPathTail(), requestHeader, nullptr, requestExecutor->getConnection());
            
            const oatpp::web::protocol::http::Headers& responseHeader = response->getHeaders();
            
            auto responseBody = response->readBodyToString();
            // OATPP_LOGD("response", "%s", responseBody->c_str());
            
            return createJSONResponse(utils::StatusUtils::getStatus(response->getStatusCode()), responseHeader, responseBody);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            OATPP_LOGE("err", " %s", e.what());
            return createErroeResponse(Status::CODE_500, e.what());
        }
    }

    ENDPOINT("HEAD", "*", dockerHead, REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        OATPP_LOGI("HEAD", " dockerHead");

        try
        {
            const oatpp::web::protocol::http::Headers& requestHeader = request->getHeaders();

            OATPP_LOGI("pathVariables", " getPathTail: %s\n", request->getPathTail()->getData());

            auto response = requestExecutor->executeOnce("HEAD", request->getPathTail(), requestHeader, nullptr, requestExecutor->getConnection());
            
            const oatpp::web::protocol::http::Headers& responseHeader = response->getHeaders();
            
            return createJSONResponse(utils::StatusUtils::getStatus(response->getStatusCode()), responseHeader, "");
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            OATPP_LOGE("err", " %s", e.what());
            return createErroeResponse(Status::CODE_500, e.what());
        }
    }

    ENDPOINT("DELETE", "*", dockerDelete, REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        OATPP_LOGI("DELETE", " dockerDelete");

        const oatpp::web::protocol::http::Headers& requestHeader = request->getHeaders();

        OATPP_LOGI("pathVariables", " getPathTail: %s\n", request->getPathTail()->getData());

        try
        {
            auto response = requestExecutor->executeOnce("DELETE", request->getPathTail(), requestHeader, nullptr, requestExecutor->getConnection());
            
            const oatpp::web::protocol::http::Headers& responseHeader = response->getHeaders();
            
            auto responseBody = response->readBodyToString();
            // OATPP_LOGD("response", "%s", responseBody->c_str());
            
            return createJSONResponse(utils::StatusUtils::getStatus(response->getStatusCode()), responseHeader, responseBody);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            OATPP_LOGE("err", " %s", e.what());
            return createErroeResponse(Status::CODE_500, e.what());
        }
    }

    ENDPOINT("POST", "*", dockerPost, REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        OATPP_LOGI("POST", " dockerPost");

        const oatpp::web::protocol::http::Headers& requestHeader = request->getHeaders();

        OATPP_LOGI("pathVariables", " getPathTail: %s\n", request->getPathTail()->getData());

        String requestBody = request->readBodyToString();
        OATPP_LOGD("requestBody", " %s", requestBody->c_str());
        
        try
        {
            // auto body = oatpp::web::protocol::http::outgoing::BufferBody::createShared(requestBody, oatpp::data::share::StringKeyLabel("text/plain"));
            auto body = oatpp::web::protocol::http::outgoing::BufferBody::createShared(requestBody, oatpp::data::share::StringKeyLabel("application/json"));
            OATPP_LOGD("body", " created");

            auto response = requestExecutor->executeOnce("POST", request->getPathTail(), requestHeader, body, requestExecutor->getConnection());
            OATPP_LOGD("response", " status %d", response->getStatusCode());
            
            const oatpp::web::protocol::http::Headers& responseHeader = response->getHeaders();
            
            auto responseBody = response->readBodyToString();
            OATPP_LOGD("response", " %s", responseBody->c_str());
            
            return createJSONResponse(utils::StatusUtils::getStatus(response->getStatusCode()), responseHeader, responseBody);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            OATPP_LOGE("err", " %s", e.what());
            return createErroeResponse(Status::CODE_500, e.what());
        }
    }

    ENDPOINT("PUT", "*", dockerPut, REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        OATPP_LOGI("PUT", " dockerPut");

        const oatpp::web::protocol::http::Headers& requestHeader = request->getHeaders();

        OATPP_LOGI("pathVariables", " getPathTail: %s\n", request->getPathTail()->getData());

        String requestBody = request->readBodyToString();
        OATPP_LOGD("requestBody", " %s", requestBody->c_str());
        
        try
        {
            // auto body = oatpp::web::protocol::http::outgoing::BufferBody::createShared(requestBody, oatpp::data::share::StringKeyLabel("text/plain"));
            auto body = oatpp::web::protocol::http::outgoing::BufferBody::createShared(requestBody, oatpp::data::share::StringKeyLabel("application/json"));
            OATPP_LOGD("body", " created");

            auto response = requestExecutor->executeOnce("PUT", request->getPathTail(), requestHeader, body, requestExecutor->getConnection());
            OATPP_LOGD("response", " status %d", response->getStatusCode());
            
            const oatpp::web::protocol::http::Headers& responseHeader = response->getHeaders();
            
            auto responseBody = response->readBodyToString();
            OATPP_LOGD("response", " %s", responseBody->c_str());
            
            return createJSONResponse(utils::StatusUtils::getStatus(response->getStatusCode()), responseHeader, responseBody);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            OATPP_LOGE("err", " %s", e.what());
            return createErroeResponse(Status::CODE_500, e.what());
        }
    }

    /*ENDPOINT("GET", "*", dockerGet, REQUEST(std::shared_ptr<IncomingRequest>, request))
    {
        OATPP_LOGD("GET", " dockerGet");

        const oatpp::web::protocol::http::Headers& header = request->getHeaders();
        OATPP_LOGD("head", " user-agent='%s'\n", request->getHeader("user-agent")->getData());
        for(auto& head : header.getAll()) {
            OATPP_LOGD("head", " %s = %s", head.first.getData(), head.second.getData());
        }
        OATPP_LOGD("head", "\n");

        // const oatpp::web::url::mapping::Pattern::MatchMap& pathVariables = request->getPathVariables();
        // OATPP_LOGD("pathVariables", " getTail: %s", pathVariables.getTail()->getData());
        OATPP_LOGD("pathVariables", " getPathTail: %s\n", request->getPathTail()->getData());


        const QueryParams& queryParams = request->getQueryParameters();
        OATPP_LOGD("queryParams", " size: %d\n", queryParams.getSize());
        string newQuery = "?";
        for(auto& param : queryParams.getAll()) {
            OATPP_LOGD("queryParams", " %s = %s", param.first.getData(), param.second.getData());
            newQuery += param.first.std_str() + "=" + param.second.std_str() + "&";
            // newQuery = newQuery.append(param.first.std_str()).append("=").append(param.second.std_str()).append("&");
        }
        newQuery = newQuery.substr(0, newQuery.size() - 1);
        OATPP_LOGD("newQuery", " %s", newQuery.c_str());

        auto data = dockerAPIClient->getInfo()->readBodyToString();
        // OATPP_LOGD("getInfo", "[doGet] data='%s'", data->c_str());

        auto response = createResponse(Status::CODE_200, data);
        response->putHeader(Header::CONTENT_TYPE, "application/json");
        return response;
    }*/
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* docker_api_swagger_DockerAPIController_hpp */
