#pragma once
#include<iostream>
#include<string>
using namespace std;

////命名空间First--线性探测法
//namespace First
//{
//
//enum State
//{
//	EMPTY,
//	DELETE,
//	EXIST,
//};
//
//template<class T>
//class HashTable
//{
//public:
//	HashTable(size_t capacity = 10)
//		:_tables(new T[capacity]),
//		_states(new State[capacity]),
//		_size(0),
//		_capacity(capacity)	
//	{
//		for (size_t i = 0;i < _capacity;++i)
//		{
//			_states[i] = EMPTY;
//		}
//	}
//	~HashTable()
//	{
//		if (_tables)
//		{
//			delete []_tables;
//			delete []_states;
//		}
//	}
//	//拷贝构造函数
//	HashTable(const HashTable<T>& ht)
//		:_tables(NULL)
//		, _status(NULL)
//		,_size(0)
//		,_capacity(0)
//	{
//		HashTable<K> newTables(ht._capacity);
//		for (size_t i = 0; i < ht._capacity; ++i)
//		{
//			if (ht._status[i] == EXITS)
//			{
//				newTables.Insert(ht._tables[i]);
//			}
//		}
//
//		this->Swap(newTables);
//	}
//
//	//重载赋值运算符
//	HashTable<T>& operator=(HashTable<T> ht)
//	{
//		this->Swap(ht);
//
//		return *this;
//	}
//	bool Insert(const T& key)
//	{
//		_CheckCapacity();
//
//		/*if (_size == _capacity)
//		{
//			cout << "HashTable is Full" << endl;
//			return false;
//		}*/
//
//		size_t index = HashFunc(key);
//		//线性探测
//
//		while (_states[index] == EXIST)
//		{
//			if (_tables[index] == key)
//			{
//				return false;
//			}
//
//			++index;
//			if (index == _capacity)
//			{
//				index = 0;
//			}
//		}
//		_tables[index] = key;
//		_states[index] = EXIST;
//		_size++;
//	}
//
//
//
//
//	////改进版
//	//bool Insert(const T& key)
//	//{
//	//	_CheckCapacity();
//
//	//	/*if (_size == _capacity)
//	//	{
//	//	cout << "HashTable is Full" << endl;
//	//	return false;
//	//	}*/
//
//	//	size_t index = HashFunc0(key);
//	//	//线性探测
//
//	//	while (_states[index] == EXIST)
//	//	{
//	//		if (_tables[index] == key)
//	//		{
//	//			return false;
//	//		}
//
//	//		index = _HashFunci(index, i++);
//	//		index %= _capacity;
//	//	}
//	//	_tables[index] = key;
//	//	_states[index] = EXIST;
//	//	_size++;
//	//}
//
//
//
//
//
//
//
//	bool Find(const T& key)
//	{
//		size_t index = HashFunc(key);
//		size_t start = index;
//		bool find = false;
//
//		while (_states[index] != EMPTY)
//		{
//			if (_tables[index] == key )
//			{
//				if (_states[index] != DELETE)
//				{
//					return true;
//				}
//				return false;
//			}
//
//			++index;
//			if (index == _capacity)
//			{
//				index = 0;
//			}
//			if (index == start)
//			{
//				return false;
//			}
//		}
//		return false;
//	}
//
//	bool Remove(const T& key)
//	{
//		size_t index = HashFunc(key);
//		size_t start = index;
//
//		while (_states[index] != EMPTY)
//		{
//			if (_tables[index] == key)
//			{
//				_states[index] = DELETE;
//				_size--;
//				return true;
//			}
//
//			++index;
//			if (index == _capacity)
//			{
//				index = 0;
//			}
//			if (index == start)
//			{
//				return false;
//			}
//		}
//	}
//	void Print()
//	{
//		for (size_t i = 0;i < _capacity;++i)
//		{
//			printf("[%d : %d]--\n", _states[i], _tables[i]);
//		}
//		cout << endl;
//	}
//protected:
//	void Swap(HashTable<T> &tmp)
//	{
//		swap(_tables, tmp._tables);
//		swap(_states, tmp._states);
//		swap(_size, tmp._size);
//		swap(_capacity, tmp._capacity);
//	}
//	size_t HashFunc(const T& key)
//	{
//		return key%_capacity;
//	}
//	
//	void _CheckCapacity()
//	{
//		if (_size * 10 / _capacity == 7)
//		{
//			HashTable<T> tmp(2 * _capacity);
//			for (size_t i = 0;i < _capacity;++i)
//			{
//				if (_states[i] == EXIST)
//				{
//					tmp.Insert(_tables[i]);
//				}
//			}
//			this->Swap(tmp);
//		}
//	}
//
//
//protected:
//	T* _tables;			//哈希表
//	State* _states;	    //状态表
//	size_t _size;		//大小
//	size_t _capacity;		
//};
//}
//
//
////命名空间Second--闭散列的二次探测
//namespace Second
//{
//	enum State
//	{
//		EMPTY,
//		DELETE,
//		EXIST,
//	};
//
//	template<class T>
//	class HashTable
//	{
//	public:
//		HashTable(size_t capacity = 10)
//			:_tables(new T[capacity]),
//			_states(new State[capacity]),
//			_size(0),
//			_capacity(capacity)
//		{
//			for (size_t i = 0;i < _capacity;++i)
//			{
//				_states[i] = EMPTY;
//			}
//		}
//		~HashTable()
//		{
//			if (_tables)
//			{
//				delete[]_tables;
//				delete[]_states;
//			}
//		}
//		bool Insert(const T& key)
//		{
//			_CheckCapacity();
//			size_t index = HashFunc(key);
//			int i = 1;
//			while (_states[index] ==EXIST)
//			{
//				if (_tables[index] == key)
//				{
//					return false;
//				}
//
//				index = HashFunc(key) + i*i;
//				index %= _capacity;
//				++i;
//
//			}
//
//			_tables[index] = key;
//			_states[index] = EXIST;
//			_size++;
//		}
//		bool Find(const T& key)
//		{
//			
//		}
//
//		bool Remove(const T& key)
//		{
//			
//		}
//		size_t HashFunc(const T& key)
//		{
//			return key%_capacity;
//		}
//		void Print()
//		{
//			for (size_t i = 0;i < _capacity;++i)
//			{
//				printf("[%d : %d]--", _states[i], _tables[i]);
//			}
//			cout << endl;
//		}
//			
//		void _CheckCapacity()
//		{
//			if (_size * 10 / _capacity == 7)
//			{
//				//重新建表
//
//				HashTable<T> tmp(2 * _capacity);
//				for (size_t i = 0;i < _capacity;++i)
//				{
//					if (_states[i] == EXIST)
//					{
//						tmp.Insert(_tables[i]);
//					}
//				}
//				this->Swap(tmp);
//			}
//		}
//		void Swap(HashTable<T> &tmp)
//		{
//			swap(_tables, tmp._tables);
//			swap(_states, tmp._states);
//			swap(_size, tmp._size);
//			swap(_capacity, tmp._capacity);
//		}
//	protected:
//		T* _tables;			//哈希表
//		State* _states;	    //状态表
//		size_t _size;		//大小
//		size_t _capacity;
//	};
//}

//明名空间3--哈希表的key/value形式的二次探测
namespace Third
{
	enum State
	{
		EMPTY,
		DELETE,
		EXIST,
	};

	template<class K, class V>
	struct HashTableNode
	{
		HashTableNode()
		{}
		HashTableNode(const K& key, const V& value)
			:_key(key),
			_value(value)
		{}

		K _key;
		V _value;
	};

	static size_t StringHash(const char* str)
	{
		size_t sum = 0;
		while (*str != '\0')
		{
			sum += *str;
			str++;
		}
		return sum;
	}

	template<class K>
	struct __HashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	//模板特化
	template<>
	struct __HashFunc<string>
	{
		size_t operator()(const string& str)
		{
			return StringHash(str.c_str());
		}
	};


	template<class K, class V, class HashFunction = __HashFunc<K>>
	class HashTable
	{
		typedef HashTableNode<K, V> Node;
	public:
		HashTable()
			:_tables(NULL)
			, _size(0)
			, _capacity(0)
			, _status(0)
		{}
		HashTable(size_t capacity = 10)
			:_tables(new Node[capacity]),
			_states(new State[capacity]),
			_size(0),
			_capacity(capacity)
		{
			for (size_t i = 0;i < capacity;++i)
			{
				_states[i] = EMPTY;
			}
		}
		~HashTable()
		{
			if (_tables)
			{
				delete[]_tables;
				delete[]_states;
			}
		}

		bool Insert(const K& key, const V& value)
		{
			_CheckCapacity();

			size_t index = HashFunc(key);
			int i = 1;

			//基于二次探测
			while (_states[index] == EXIST)
			{
				if (_tables[index]._key == key)
				{
					return false;
				}

				index = HashFunc(key) + i*i;
				index %= _capacity;
				++i;
			}

			_tables[index] = Node(key, value);
			_states[index] = EXIST;
			++_size;

			return true;
		}
		Node* Find(const K& key)
		{
			size_t index = HashFunc(key);

			size_t start = index;
			int i = 1;
			while (_states[index] != EMPTY)
			{
				if (_tables[index]._key == key)
				{
					if (_states[index] == EXIST)
					{
						return &(_tables[index]);
					}
					return NULL;
				}
				index += i*i;

				if (index >=_capacity)
				{
					index %= _capacity;
				}
				if (index == start)
				{
					break;
				}
			}
			return NULL;
		}

		size_t HashFunc(const K& key)
		{
			HashFunction hf;
			return (hf(key)) % _capacity;
		}
		void Print()
		{
			for (size_t i = 0;i < _capacity;++i)
			{
				cout << "【" << _tables[i]._key<<" --- ";
				cout << _tables[i]._value << "】";
			}
			cout << endl;
		}

	protected:
		void _CheckCapacity()
		{
			if (_size < _capacity)
			{
				return;
			}

			HashTable<K,V,HashFunction> newTable(2 * _capacity);
			for (size_t index = 0;index < _capacity;++index)
			{
				if (_states[index] == EXIST)
				{
					newTable._tables[index] = _tables[index];
					newTable._states[index] = EXIST;
					newTable._size = _size;
				}
			}

			this->Swap(newTable);
		}
		void Swap(HashTable<K, V, HashFunction>& other)
		{
			swap(_tables, other._tables);
			swap(_states, other._states);
			swap(_size, other._size);
			swap(_capacity, other._capacity);
		}
	protected:
		Node* _tables;
		State* _states;
		size_t _size;
		size_t _capacity;
	};

	void TestHashTable()
	{
		HashTable<string, string> ht1(10);

		ht1.Insert("dict", "字典");
		ht1.Insert("hash", "哈希");
		ht1.Insert("function", "函数");
		ht1.Insert("lauyang", "刘阳阳");

		HashTableNode<string, string>* ret = ht1.Find("lauyg");

		if (ret)
		{
			cout << "hash的中文是： " << ret->_value << endl;
		}
		else
		{
			cout << "not exist" << endl;
		}
	}
}