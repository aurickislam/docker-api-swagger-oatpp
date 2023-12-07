
#ifndef docker_api_swagger_oatpp_DTOs_hpp
#define docker_api_swagger_oatpp_DTOs_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ErrorResponseDto : public oatpp::DTO
{
	DTO_INIT(ErrorResponseDto, DTO);

	DTO_FIELD_INFO(statusCode)
	{
		info->description = "Error status code"; //<-- Fields description is integrated with Swagger-UI.
	}
	DTO_FIELD(UInt32, statusCode);

	DTO_FIELD_INFO(error)
	{
		info->description = "Error"; //<-- Fields description is integrated with Swagger-UI.
	}
	DTO_FIELD(String, error);

	DTO_FIELD_INFO(message)
	{
		info->description = "Error message"; //<-- Fields description is integrated with Swagger-UI.
	}
	DTO_FIELD(String, message);
};

class DockerInfo : public oatpp::DTO
{
	DTO_INIT(DockerInfo, DTO);

	DTO_FIELD(String, Name);
	DTO_FIELD(UInt16, NCPU);
	DTO_FIELD(UInt32, MemTotal);
	DTO_FIELD(String, OperatingSystem);
	DTO_FIELD(String, OSVersion);
	DTO_FIELD(String, OSType);
	DTO_FIELD(String, KernelVersion);
	DTO_FIELD(String, Architecture);
	DTO_FIELD(UInt16, Images);
	DTO_FIELD(UInt16, Containers);
	DTO_FIELD(UInt16, ContainersRunning);
};

class DockerVersion : public oatpp::DTO
{
	DTO_INIT(DockerVersion, DTO);

	DTO_FIELD(String, Version);
	DTO_FIELD(String, ApiVersion);
	DTO_FIELD(String, MinAPIVersion);
	DTO_FIELD(String, Arch);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* docker_api_swagger_DTOs_hpp */
