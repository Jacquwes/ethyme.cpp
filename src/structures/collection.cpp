#include "structures/collection.hpp"

namespace Ethyme::Structures
{
	template<typename T>
	const std::shared_ptr<T>& Structures::Collection<T>::find(std::function<void(const std::shared_ptr<T>&)> predicate) const
	{
		for (const std::shared_ptr<T>& item : m_items)
			if (predicate(item))
				return item;
		return std::make_shared<T>(nullptr);
	}

	template<typename T>
	const std::shared_ptr<T>& Collection<T>::findById(const std::string& id) const
	{
		return find([&id](const std::shared_ptr<T>& item) { return id == item->Id(); });
	}
	
	template<typename T>
	void Collection<T>::remove(std::function<void(const std::shared_ptr<T>&)> predicate)
	{
		m_items.erase(std::find_if(m_items.begin(), m_items.end(), predicate));
	}
	
	template<typename T>
	void Collection<T>::removeById(const std::string& id)
	{
		remove([&id](const std::shared_ptr<T>& item) { return id == item->Id(); });
	}
}