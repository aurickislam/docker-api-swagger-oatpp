
#ifndef example_oatpp_mongo_DTOs_hpp
#define example_oatpp_mongo_DTOs_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class SuccessResponseDto : public oatpp::DTO {
  
  DTO_INIT(SuccessResponseDto, DTO)
  
  DTO_FIELD_INFO(message) {
    info->description = "Response message"; //<-- Fields description is integrated with Swagger-UI.
  }
  DTO_FIELD(String, message);
  
};

class ErrorResponseDto : public oatpp::DTO {
  
  DTO_INIT(ErrorResponseDto, DTO)
  
  DTO_FIELD_INFO(statusCode) {
    info->description = "Error status code"; //<-- Fields description is integrated with Swagger-UI.
  }
  DTO_FIELD(UInt32, statusCode);
  
  DTO_FIELD_INFO(error) {
    info->description = "Error"; //<-- Fields description is integrated with Swagger-UI.
  }
  DTO_FIELD(String, error);

  DTO_FIELD_INFO(message) {
    info->description = "Error message"; //<-- Fields description is integrated with Swagger-UI.
  }
  DTO_FIELD(String, message);
  
};

class MyRequestDto : public oatpp::DTO {
  
  DTO_INIT(MyRequestDto, DTO)
  
  DTO_FIELD(String, message);
  DTO_FIELD(Int32, code);
  
};

class HttpBinResponseDto : public oatpp::DTO {
  
  DTO_INIT(HttpBinResponseDto, DTO)
  
  DTO_FIELD(String, data);
  DTO_FIELD(Fields<String>::ObjectWrapper, headers);
  DTO_FIELD(String, method);
  DTO_FIELD(String, origin);
  DTO_FIELD(String, url);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* example_oatpp_mongo_DTOs_hpp */
