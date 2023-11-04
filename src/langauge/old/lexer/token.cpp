#include "token.h"

TokenType lookup_ident (std::string ident)
{
	for (const auto& element : keywords)
	{
		if (element.first == ident)
			return element.second;
	}
		return IDENT;

}
