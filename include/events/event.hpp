#pragma once

#include "../common.hpp"

namespace Ethyme::Events
{
	/**
	 * @brief Doll class inherited by events classes.
	*/
	class Event
	{
	public:
		virtual ~Event() = default;
	};
}