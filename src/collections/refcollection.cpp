#include "collections/refcollection.hpp"
#include "client.hpp"

namespace Ethyme::Collections
{
	template<typename T>
	class Collection<T, std::void_t<decltype(T::get())>>
}