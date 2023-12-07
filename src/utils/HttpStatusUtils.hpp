#ifndef docker_api_swagger_oatpp_HttpStatusUtils_hpp
#define docker_api_swagger_oatpp_HttpStatusUtils_hpp

#include "oatpp/web/protocol/http/Http.hpp"

typedef oatpp::web::protocol::http::Status Status;

class HttpStatusUtils
{
private:
	HttpStatusUtils()
	{
	}

public:
	const static Status getStatus(const int &code)
	{
		switch (code)
		{
		case 100:
			return Status::CODE_100;
		case 101:
			return Status::CODE_101;
		case 102:
			return Status::CODE_102;
		case 200:
			return Status::CODE_200;
		case 201:
			return Status::CODE_201;
		case 202:
			return Status::CODE_202;
		case 203:
			return Status::CODE_203;
		case 204:
			return Status::CODE_204;
		case 205:
			return Status::CODE_205;
		case 206:
			return Status::CODE_206;
		case 207:
			return Status::CODE_207;
		case 226:
			return Status::CODE_226;
		case 300:
			return Status::CODE_300;
		case 301:
			return Status::CODE_301;
		case 302:
			return Status::CODE_302;
		case 303:
			return Status::CODE_303;
		case 304:
			return Status::CODE_304;
		case 305:
			return Status::CODE_305;
		case 306:
			return Status::CODE_306;
		case 307:
			return Status::CODE_307;
		case 400:
			return Status::CODE_400;
		case 401:
			return Status::CODE_401;
		case 402:
			return Status::CODE_402;
		case 403:
			return Status::CODE_403;
		case 404:
			return Status::CODE_404;
		case 405:
			return Status::CODE_405;
		case 406:
			return Status::CODE_406;
		case 407:
			return Status::CODE_407;
		case 408:
			return Status::CODE_408;
		case 409:
			return Status::CODE_409;
		case 410:
			return Status::CODE_410;
		case 411:
			return Status::CODE_411;
		case 412:
			return Status::CODE_412;
		case 413:
			return Status::CODE_413;
		case 414:
			return Status::CODE_414;
		case 415:
			return Status::CODE_415;
		case 416:
			return Status::CODE_416;
		case 417:
			return Status::CODE_417;
		case 422:
			return Status::CODE_422;
		case 423:
			return Status::CODE_423;
		case 424:
			return Status::CODE_424;
		case 425:
			return Status::CODE_425;
		case 426:
			return Status::CODE_426;
		case 428:
			return Status::CODE_428;
		case 429:
			return Status::CODE_429;
		case 431:
			return Status::CODE_431;
		case 434:
			return Status::CODE_434;
		case 444:
			return Status::CODE_444;
		case 449:
			return Status::CODE_449;
		case 451:
			return Status::CODE_451;
		case 500:
			return Status::CODE_500;
		case 501:
			return Status::CODE_501;
		case 502:
			return Status::CODE_502;
		case 503:
			return Status::CODE_503;
		case 504:
			return Status::CODE_504;
		case 505:
			return Status::CODE_505;
		case 506:
			return Status::CODE_506;
		case 507:
			return Status::CODE_507;
		case 508:
			return Status::CODE_508;
		case 509:
			return Status::CODE_509;
		case 510:
			return Status::CODE_510;
		case 511:
			return Status::CODE_511;
		}
		return Status::CODE_500;
	}
};

#endif /* docker_api_swagger_HttpStatusUtils_hpp */