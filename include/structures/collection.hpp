#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	template<typename T>
	class Collection
	{
	public:
		void Add(const T& item);
		const T& Find(std::function<bool(const T&)> predicate) const;
		const T& FindById(const std::string& id) const;
		void Remove(std::function<bool(const T&)> predicate);
		void RemoveById(const std::string& id);

	private:
		std::vector<T> m_items;
	};

		template<typename T>
		inline void Collection<T>::Add(const T& item)
		{
			m_items.push_back(item);
		}

		template<typename T>
		inline const T& Collection<T>::Find(std::function<bool(const T&)> predicate) const
		{
			for (const T& item : m_items)
				if (predicate(item))
					return item;
			throw std::exception("item not found");
		}

		template<typename T>
		inline const T& Collection<T>::FindById(const std::string& id) const
		{
			return Find([&](const T& i) { return i.Id().ToString() == id; });
		}

		template<typename T>
		inline void Collection<T>::Remove(std::function<bool(const T&)> predicate)
		{
			m_items.erase(std::find_if(m_items.begin(), m_items.end(), predicate));
		}

		template<typename T>
		inline void Collection<T>::RemoveById(const std::string& id)
		{
			remove([&](const T& item) { return id == item->Id().ToString(); });
		}
	}
