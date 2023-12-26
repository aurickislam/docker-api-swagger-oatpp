
#ifndef docker_api_swagger_oatpp_Types_hpp
#define docker_api_swagger_oatpp_Types_hpp

#include "oatpp/core/data/mapping/type/Type.hpp"
#include "oatpp/core/Types.hpp"

namespace swagger
{
	namespace __class
	{
		/**
		 * Binary type class info.
		 */
		class Binary
		{
		private:
			static oatpp::Type *createType() {
				oatpp::Type::Info info;
				info.nameQualifier = "binary";
				return new oatpp::Type(CLASS_ID, info);
			}

		public:
			/**
			 * CLASS_NAME = `"string"`.
			 */
			static const oatpp::data::mapping::type::ClassId CLASS_ID;

			/**
			 * Get type information.
			 * @return - &id:oatpp::data::mapping::type::Type;.
			 */
			static oatpp::Type *getType() {
				return createType();
			}
		};

	}

	/**
	 * Typedef for Binary. It is used to indicate file upload in Swagger-UI. <br>
	 * Usage example: `info->addConsumes<oatpp::swagger::Binary>("application/octet-stream");`.<br>
	 * For more info see: [Endpoint Annotation And API Documentation](/docs/components/api-controller/#endpoint-annotation-and-api-documentation).
	 */
	typedef oatpp::data::mapping::type::ObjectWrapper<std::string, __class::Binary> Binary;

}

#endif /* docker_api_swagger_oatpp_Types_hpp */
