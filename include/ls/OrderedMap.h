#ifndef LS_ORDEREDMAP_H
#define LS_ORDEREDMAP_H

#include "map"
#include "string"
#include "vector"
#include "ls/Exception.h"

namespace ls
{
	template<typename K, typename T>
	class OrderedMap
	{
		public:
			OrderedMap() = default;
			OrderedMap(OrderedMap &&om) = default;
			OrderedMap(const OrderedMap &om);
			OrderedMap &operator=(OrderedMap &&om) = default;
			OrderedMap &operator=(const OrderedMap &om);
			void push(const K &key, const T &value);
			void replace(const K &key, const T &value);
			T get(const K &key);
			std::vector<std::pair<const K, T>*> &getData();
			std::map<K, T> &getMapper();
			void clear();
			OrderedMap &merge(OrderedMap &o);
		protected:
			std::map<K, T> data;
			std::vector<std::pair<const K, T> *> v;

	};

	template<typename K , typename T>
	OrderedMap<K, T>::OrderedMap(const OrderedMap &om)
	{
		for(auto &vi : om.v)
			push(vi->first, vi->second);
	}

	template<typename K , typename T>
	OrderedMap<K, T> &OrderedMap<K, T>::operator=(const OrderedMap &om)
	{
		for(auto &vi : om.v)
			push(vi->first, vi->second);
	}

	template<typename K , typename T>
	void OrderedMap<K, T>::push(const K &key, const T &value)
	{
		auto p = data.emplace(key, value);
		if(p.second == false)
			throw Exception(Exception::LS_EEXIST);
		v.emplace_back(&*p.first);
	}

	template<typename K , typename T>
	void OrderedMap<K, T>::replace(const K &key, const T &value)
	{
		auto it = data.find(key);
		if(it == data.end())
			throw Exception(Exception::LS_ENOCONTENT);
		it -> second = value;
	}

	template<typename K , typename T>
	T OrderedMap<K, T>::get(const K &key)
	{
		auto it = data.find(key);
		if(it == data.end())
			throw Exception(Exception::LS_ENOCONTENT);
		return it -> second;
	}

	template<typename K , typename T>
	std::vector<std::pair<const K, T>*> &OrderedMap<K, T>::getData()
	{
		return v;
	}

	template<typename K , typename T>
	std::map<K, T> &OrderedMap<K, T>::getMapper()
	{
		return data;
	}

	template<typename K , typename T>
	void OrderedMap<K, T>::clear()
	{
		data.clear();
		v.clear();
	}

	template<typename K , typename T>
	OrderedMap<K, T> &OrderedMap<K, T>::merge(OrderedMap<K, T> &o)
	{
		auto &mapper = o.getMapper();
		for(auto &it : mapper)
			push(it.first, it.second) ||
			replace(it.first, it.second);
		return *this;
	}
}

#endif
