#pragma once

#include "../common.hpp"

namespace Ethyme::Structures
{
	template<typename T>
	class Collection
	{
	public:
		const std::shared_ptr<T>& find(std::function<void(const std::shared_ptr<T>&)> predicate) const;
		const std::shared_ptr<T>& findById(const std::string& id) const;
		void remove(std::function<void(const std::shared_ptr<T>&)> predicate);
		void removeById(const std::string& id);

	private:
		std::vector<std::shared_ptr<T>> m_items;
	};
}