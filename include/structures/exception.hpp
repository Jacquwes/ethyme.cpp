#pragma once

#include "../common.hpp"

namespace Ethyme
{
	class Exception : public std::exception
	{
	public:
		enum class ErrorCode
		{
			Null,
			InvalidToken
		};

		Exception(std::string const& message, ErrorCode code = ErrorCode::Null)
			: std::exception(message.c_str())
			, m_code{ code }
		{}

		ErrorCode const& Code() { return m_code; }

	private:
		ErrorCode m_code;
	};
}