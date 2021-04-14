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
	template<typename T, bool ReferenceWrapper = false>
	class Collection
	{
	public:
		using type_t = std::conditional_t<ReferenceWrapper, std::reference_wrapper<T>, T>;

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
			Iterator(type_t* ptr) : m_ptr{ ptr } {}

			T& operator*() const { if constexpr (ReferenceWrapper) return m_ptr->get(); else return *m_ptr; }
			T* operator->() { if constexpr (ReferenceWrapper) return &m_ptr->get(); else return m_ptr; }
			Iterator& operator++() { ++m_ptr; return *this; }
			Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

			friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
			friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

		private:
			type_t* m_ptr;
		};

		Collection(Ethyme::Client const& client, std::string const& fetchEndpoint = "");
		virtual ~Collection() = default;

		constexpr Iterator begin();
		constexpr Iterator end();
		constexpr Iterator const cbegin() const;
		constexpr Iterator const cend() const;

		/**
		 * @brief Add a new item to the collection.
		 * @param item New item.
		*/
		T& Add(T item);
		/**
		 * @brief Fetch an item from Discord.
		 * @param endpoint Item to fetch, usually an ID.
		 * @return Returns end() if Item does not exist.
		*/
		cppcoro::task<Iterator> Fetch(std::string const& endpoint) const;
		/**
		 * @brief Find an item in the Collection.
		 * @param predicate Function which must return true when an item has the researched property.
		 * @return Item if found.
		*/
		constexpr Iterator Find(std::function<bool(T&)> predicate) const;
		/**
		 * @brief Find an item in the Collection with its ID.
		 * @param id ID of the item.
		 * @return Item if found.
		*/
		constexpr Iterator FindById(std::string const& id) const;
		/**
		 * @brief Remove an item in the Collection.
		 * @param predicate Function which must return true when an item has the researched property.
		*/
		void Remove(std::function<bool(T&)> predicate);
		/**
		 * @brief Remove an item in the Collection with its ID.
		 * @param id ID of the item.
		*/
		void RemoveById(std::string const& id);
		/**
		 * @brief Number of items in the Collection.
		*/
		size_t Size() const;

	private:
		Ethyme::Client const& m_client;
		std::string m_fetchEndpoint;
		std::vector<type_t> m_items;
	};

	template<typename T, bool ReferenceWrapper>
	inline Collection<T, ReferenceWrapper>::Collection(Ethyme::Client const& client, std::string const& fetchEndpoint)
		: m_client{ client }
		, m_fetchEndpoint{ fetchEndpoint }
	{}

	template<typename T, bool ReferenceWrapper> inline T& Collection<T, ReferenceWrapper>::Add(T item)
	{
		m_items.push_back(item);
		if constexpr (ReferenceWrapper)
			return m_items[m_items.size() - 1].get();
		else
			return m_items[m_items.size() - 1];
	}

#pragma region Iterators
	template<typename T, bool ReferenceWrapper> constexpr typename inline Collection<T, ReferenceWrapper>::Iterator Collection<T, ReferenceWrapper>::begin() { return m_items.begin()._Ptr; }
	template<typename T, bool ReferenceWrapper> constexpr typename inline Collection<T, ReferenceWrapper>::Iterator Collection<T, ReferenceWrapper>::end() { return m_items.end()._Ptr; }
	template<typename T, bool ReferenceWrapper> constexpr typename inline Collection<T, ReferenceWrapper>::Iterator const Collection<T, ReferenceWrapper>::cbegin() const { return m_items.cbegin()._Ptr; }
	template<typename T, bool ReferenceWrapper> constexpr typename inline Collection<T, ReferenceWrapper>::Iterator const Collection<T, ReferenceWrapper>::cend() const { return m_items.cend()._Ptr; }
#pragma endregion

	template<typename T, bool ReferenceWrapper> inline cppcoro::task<typename Collection<T, ReferenceWrapper>::Iterator> Collection<T, ReferenceWrapper>::Fetch(std::string const& endpoint) const
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

	template<typename T, bool ReferenceWrapper>
	constexpr typename inline Collection<T, ReferenceWrapper>::Iterator Collection<T, ReferenceWrapper>::Find(std::function<bool(T&)> predicate) const
	{
		if constexpr (ReferenceWrapper)
		{
			Iterator last(m_items.end()._Ptr);
			for (Iterator i(m_items.begin()._Ptr); i != last; ++i)
				if (predicate(*i))
					return i;
			return last;
		}
		else
		{
			Iterator last(m_items.end()._Ptr);
			for (Iterator i(m_items.begin()._Ptr); i != last; ++i)
				if (predicate(*i))
					return i;
			return last;
		}
	}

	template<typename T, bool ReferenceWrapper>
	constexpr typename inline Collection<T, ReferenceWrapper>::Iterator Collection<T, ReferenceWrapper>::FindById(const std::string& id) const { return Find([&](T& i) { return i.Id().ToString() == id; }); }
	template<typename T, bool ReferenceWrapper>
	inline void Collection<T, ReferenceWrapper>::Remove(std::function<bool(T&)> predicate) { m_items.erase(std::find_if(m_items.begin(), m_items.end(), predicate)); }
	template<typename T, bool ReferenceWrapper>
	inline void Collection<T, ReferenceWrapper>::RemoveById(const std::string& id) { remove([&](const T& item) { return id == item->Id().ToString(); }); }
	template<typename T, bool ReferenceWrapper>
	inline size_t Collection<T, ReferenceWrapper>::Size() const { return m_items.size(); }
}
