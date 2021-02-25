#pragma once

#include "common.hpp"

namespace Ethyme
{
	class Client;
}

namespace Ethyme::Collections
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
		 * @brief Simple iterator
		*/
		class Iterator
		{
			// yes, copied from https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp hahaha
		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			Iterator() = default;
			Iterator(Iterator const& i) : m_ptr{ i.m_ptr } {}
			Iterator(T* ptr) : m_ptr{ ptr } {}

			T& operator*() const { return *m_ptr; }
			T* operator->() { return m_ptr; }
			Iterator& operator++() { ++m_ptr; return *this; }
			Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

			friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
			friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

		private:
			T* m_ptr;
		};

		Collection(Ethyme::Client const& client, std::string const& fetchEndpoint = "");
		virtual ~Collection() = default;

		constexpr Iterator begin();
		constexpr Iterator end();

		/**
		 * @brief Add a new item to the collection.
		 * @param item New item.
		*/
		void Add(const T& item);
		/**
		 * @brief Fetch an item from Discord.
		 * @param endpoint Item to fetch, usually an ID.
		 * @return Returns end() if Item does not exist.
		*/
		cppcoro::task<Iterator> Fetch(std::string const& endpoint);
		/**
		 * @brief Find an item in the Collection.
		 * @param predicate Function which must return true when an item has the researched property.
		 * @return Item if found.
		*/
		constexpr Iterator Find(std::function<bool(const T&)> predicate) const;
		/**
		 * @brief Find an item in the Collection with its ID.
		 * @param id ID of the item.
		 * @return Item if found.
		*/
		constexpr Iterator FindById(const std::string& id) const;
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
		Ethyme::Client const& m_client;
		std::string m_fetchEndpoint;
		std::vector<T> m_items;
	};

	template<typename T>
	inline Collection<T>::Collection(Ethyme::Client const& client, std::string const& fetchEndpoint)
		: m_client{ client }
		, m_fetchEndpoint { fetchEndpoint }
	{}

	template<typename T>
	inline void Collection<T>::Add(const T& item)
	{
		m_items.push_back(item);
	}

	template<typename T>
	constexpr typename inline Collection<T>::Iterator Collection<T>::begin()
	{
		return m_items.begin();
	}

	template<typename T>
	constexpr typename inline Collection<T>::Iterator Collection<T>::end()
	{
		return m_items.end();
	}

	template<typename T>
	inline cppcoro::task<typename Collection<T>::Iterator> Collection<T>::Fetch(std::string const& endpoint)
	{
		auto response = cpr::Get(
			cpr::Url{ m_fetchEndpoint + endpoint },
			cpr::Header{
				{ "Authorization", m_client.Token() },
				{ "Content-Type", "application/json" }
			}
		);

		if (response.error)
			co_return end();

		T item{ nlohmann::json::parse(response.text), m_client };
		Add(item);

		co_return Iterator(&T);
	}

	template<typename T>
	constexpr typename inline Collection<T>::Iterator Collection<T>::Find(std::function<bool(const T&)> predicate) const
	{
		Iterator last( m_items.end()._Ptr );
		for (Iterator i( m_items.begin()._Ptr ); i != last; ++i)
			if (predicate(*i))
				return i;
		return last;
	}

	template<typename T>
	constexpr typename inline Collection<T>::Iterator Collection<T>::FindById(const std::string& id) const
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
