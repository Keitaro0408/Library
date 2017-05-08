#include "HttpConnect.h"


HttpConnect::HttpConnect()
{
}

HttpConnect::~HttpConnect()
{
}

bool HttpConnect::Connect(METHOD _method, std::string _url, std::string* _pResultStr)
{
	*_pResultStr = std::string();

	if (_url.length() == 0)
	{
		OutputDebugString(TEXT("URLが入っていません"));
		return false;
	}

	switch (_method)
	{
	case GET_METHOD:

		break;
	case POST_METHOD:
		break;
	default:
		break;
	}

}
