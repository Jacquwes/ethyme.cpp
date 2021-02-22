#pragma once

#include "common.hpp"

namespace Ethyme::Structures
{
	/**
	 * @brief Collection manager class used by Ethyme.
	 * @tparam T Type of objects to manage.
	*/
	template<typename T>
	class Collection
	{
	public:
		/**
		 * @brief Add a new item to the collection.
		 * @param item New item.
		*/
		void Add(const T& item);
		/**
		 * @brief Useless
		*/
		const T* End() const;
		/**
		 * @brief Find an item in the Collection.
		 * @param predicate Function which must return true when an item has the researched property.
		 * @return Item if found.
		*/
		const T& Find(std::function<bool(const T&)> predicate) const;
		/**
		 * @brief Find an item in the Collection with its ID.
		 * @param id ID of the item.
		 * @return Item if found.
		*/
		const T& FindById(const std::string& id) const;
		/**
		 * @brief Remove an item in the Collection.
		 * @param predicate Function which must return true when an item has the researched property.
		*/
		void Remove(std::function<bool(const T&)> predicate);
		/**
		 * @brief Remove an item in the Collection with its ID.
		 * @param id ID of the item.
		*/
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
	inline const T* Collection<T>::End() const
	{
		return m_items.end();
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
