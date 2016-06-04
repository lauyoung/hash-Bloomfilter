#pragma once
#include <vector>
#include<iostream>
using namespace std;

namespace BUCKET
{
template<class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode<K, V>* _next;

	HashTableNode(const K& key, const V& value)
		:_key(key),
		_value(value),
		_next(NULL)
	{}
};

template<class K,class V>
class HashTable
{
	typedef HashTableNode<K, V> Node;
	typedef HashTable<K, V> Table;
public:
	
	HashTable()
		:_size(0)
	{}
	HashTable(size_t capacity)//capacity最好是素数，这样可以减少哈希冲突。
		:_size(0)
	{

 		_tables.resize(_GetNextPrime(capacity));//确保开辟素数大小空间
	}
	~HashTable()
	{
		for (size_t i = 0;i < _tables.size();++i)
		{
			Node* cur = _tables[i];
			while (cur)
			{
				Node*tmp = cur;
				cur = cur->_next;
				delete tmp;
				tmp = NULL;
			}
			_tables[i] = NULL;
		}
		_size = 0;
	}

	HashTable(const Table& other)
		:_size(0)
	{
		Table newTables(other._tables.size());
		newTables._size = other._size;

		for (size_t i = 0;i < other._tables.size();++i)
		{
			Node* cur = other._tables[i];
			Node*& head = newTables._tables[i];

			while (cur)
			{
				//newTables.Insert(cur->_key, cur->_value);

				Node* tmp= new Node(cur->_key, cur->_value);
				tmp->_next = head;
				head = tmp;
				
				cur = cur->_next;
			}
		}
		this->Swap(newTables);
	}

	/*Table& operator=(Table t)
	{
		_tables.swap(t);
		swap(_size, t._size);

		return _tables;
	}*/
	Table& operator=(Table& t)
	{
		if (this != &t)
		{
			Table tmp(t);
			_tables.swap(t);
			swap(_size, t._size);
		}
		

		return _tables;
	}
	
	bool Insert(const K& key, const V& value)
	{
		size_t index = _HashFunc(key,_tables.size());

		//检查是否存在
		Node* cur=_tables[index];
		while (cur)
		{
			if (cur->_key ==key)
			{
				return false;
			}
			cur = cur->_next;
		}

		//头插法
		Node* tmp = new Node(key, value);
		tmp->_next = _tables[index];
		_tables[index] = tmp;

		++_size;
		return true;
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key, _tables.size());

		Node* cur = _tables[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}
	bool Remove(const K& key)
	{
		size_t index = _HashFunc(key, _tables.size());
		
		Node* cur = _tables[index];
		if (cur == NULL)
		{
			return false;
		}
		if (cur->_key == key)
		{
			_tables[index] = cur->_next;
			delete cur;
			return true;
		}
		else
		{
			Node* prev = cur;
			cur = cur->_next;
			while (cur)
			{
				if (cur->_key==key)
				{
					prev->_next = cur->_next;
					delete cur;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}
	}
	void Print()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			printf("tables[%d]->", i);
			Node* cur =_tables[i];
			while (cur)
			{
				cout << "[" << cur->_key << ":" << cur->_value << "]" << "->";
				cur = cur->_next;
			}

			cout << "NULL" << endl;
		}

		cout << endl;
	}
protected:
	size_t _GetNextPrime(size_t size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};


		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}
		}

		return _PrimeList[_PrimeSize - 1];
	}
	size_t _HashFunc(const K& key,size_t capacity)
	{
		return key % capacity;
	}
	void _CheckCapacity()
	{
		//负载值为1时增容
		if (_size == _tables.size())
		{
			size_t nextPrime = _GetNextPrime(_size);

			vector<Node*> newTables;
			newTables.resize(nextPrime);

			for (size_t i = 0;i < _tables.size();++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* tmp = cur;
					cur = cur->_next;

					//头插
					size_t index = _HashFunc(tmp->_key, newTables.size());

					tmp->_next = newTables[index];
					newTables[index] = tmp;
				}

				_tables[i] = NULL;
			}

			_tables.swap(newTables);
		}
	}

	
	void Swap(Table &other)
	{
		_tables.swap(other._tables);
		swap(_size,other._size);
	}
private:
	vector<HashTableNode<K, V>*> _tables;
	size_t _size;//Node底下挂多少数据
};


void TestHashBucketTable()
{
	HashTable<int, int> ht(20);
	ht.Insert(1, 14);
	ht.Insert(2, 12);
	ht.Insert(3, 21);
	ht.Insert(4, 11);
	ht.Print();

	//删除remove
	/*ht.Remove(1);
	ht.Print();*/

	//测试拷贝构造
	HashTable<int, int> other(ht);
	other.Print();
	
	//find函数
	/*HashTableNode<int,int>* ret = ht.Find(1);
	if (ret)
	{
		cout<<"the key is exist: "<<ret->_key<<" "<<ret->_value<<endl;
	}
	else
	{
		cout<<"it is not exist"<<endl;
	}*/
}
}

namespace HASHBUCKET
{
	template<class K, class V>
	struct HashTableNode
	{
		K _key;
		V _value;
		HashTableNode<K, V>* _next;

		HashTableNode(const K& key, const V& value)
			:_key(key),
			_value(value),
			_next(NULL)
		{}
	};

	template<class K>
	struct DefaultHashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct DefaultHashFunc<string>
	{
		static size_t BKDRHash(const char * str)
		{
			unsigned int seed = 131; // 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash * seed + (*str++);
			}
			return (hash & 0x7FFFFFFF);
		}
		size_t operator() (const string& key)
		{
			return BKDRHash(key.c_str());
		}
	};
	template<class K, class V,class HashFunc=DefaultHashFunc<K>>
	class HashTable
	{
		typedef HashTableNode<K,V> Node;
		typedef HashTable<K,V,HashFunc> Table;
	public:

		HashTable()
			:_size(0)
		{}
		HashTable(size_t capacity)//capacity最好是素数，这样可以减少哈希冲突。
			:_size(0)
		{

			_tables.resize(_GetNextPrime(capacity));//确保开辟素数大小空间
		}
		~HashTable()
		{
			for (size_t i = 0;i < _tables.size();++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node*tmp = cur;
					cur = cur->_next;
					delete tmp;
					tmp = NULL;
				}
				_tables[i] = NULL;
			}
			_size = 0;
		}

		HashTable(const Table& other)
			:_size(0)
		{
			Table newTables(other._tables.size());
			newTables._size = other._size;

			for (size_t i = 0;i < other._tables.size();++i)
			{
				Node* cur = other._tables[i];
				Node*& head = newTables._tables[i];

				while (cur)
				{
					//newTables.Insert(cur->_key, cur->_value);

					Node* tmp = new Node(cur->_key, cur->_value);
					tmp->_next = head;
					head = tmp;

					cur = cur->_next;
				}
			}
			this->Swap(newTables);
		}

		/*Table& operator=(Table t)
		{
		_tables.swap(t);
		swap(_size, t._size);

		return _tables;
		}*/
		Table& operator=(Table& t)
		{
			if (this != &t)
			{
				Table tmp(t);
				_tables.swap(t);
				swap(_size, t._size);
			}


			return _tables;
		}

		bool Insert(const K& key, const V& value)
		{
			size_t index = _HashFunc(key, _tables.size());

			//检查是否存在
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_key == key)
				{
					return false;
				}
				cur = cur->_next;
			}

			//头插法
			Node* tmp = new Node(key, value);
			tmp->_next = _tables[index];
			_tables[index] = tmp;

			++_size;
			return true;
		}

		Node* Find(const K& key)
		{
			size_t index = _HashFunc(key, _tables.size());

			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_key == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return NULL;
		}
		bool Remove(const K& key)
		{
			size_t index = _HashFunc(key, _tables.size());

			Node* cur = _tables[index];
			if (cur == NULL)
			{
				return false;
			}
			if (cur->_key == key)
			{
				_tables[index] = cur->_next;
				delete cur;
				return true;
			}
			else
			{
				Node* prev = cur;
				cur = cur->_next;
				while (cur)
				{
					if (cur->_key == key)
					{
						prev->_next = cur->_next;
						delete cur;
						return true;
					}
					prev = cur;
					cur = cur->_next;
				}
				return false;
			}
		}
		void Print()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				printf("tables[%d]->", i);
				Node* cur = _tables[i];
				while (cur)
				{
					cout << "[" << cur->_key << ":" << cur->_value << "]" << "->";
					cur = cur->_next;
				}

				cout << "NULL" << endl;
			}

			cout << endl;
		}
	protected:
		size_t _GetNextPrime(size_t size)
		{
			const int _PrimeSize = 28;
			static const unsigned long _PrimeList[_PrimeSize] =
			{
				53ul,         97ul,         193ul,       389ul,       769ul,
				1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
				49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
				1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
				50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};


			for (size_t i = 0; i < _PrimeSize; ++i)
			{
				if (_PrimeList[i] > size)
				{
					return _PrimeList[i];
				}
			}

			return _PrimeList[_PrimeSize - 1];
		}
		size_t _HashFunc(const K& key, size_t capacity)
		{
			return HashFunc()(key) % capacity;
		}
		void _CheckCapacity()
		{
			//负载值为1时增容
			if (_size == _tables.size())
			{
				size_t nextPrime = _GetNextPrime(_size);

				vector<Node*> newTables;
				newTables.resize(nextPrime);

				for (size_t i = 0;i < _tables.size();++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* tmp = cur;
						cur = cur->_next;

						//头插
						size_t index = _HashFunc(tmp->_key, newTables.size());

						tmp->_next = newTables[index];
						newTables[index] = tmp;
					}

					_tables[i] = NULL;
				}

				_tables.swap(newTables);
			}
		}


		void Swap(Table &other)
		{
			_tables.swap(other._tables);
			swap(_size, other._size);
		}
	private:
		vector<HashTableNode<K, V>*> _tables;
		size_t _size;//Node底下挂多少数据
	};


	void TestHashBucketTable()
	{
		HashTable<string, string> dict(10);
		dict.Insert("字典", "dict");
		dict.Insert("插入", "Insert");
		dict.Insert("删除", "Remove");
		dict.Insert("查找", "Find,Search");
		dict.Print();

		//删除remove
		/*dict.Remove("字典");
		dict.Print();*/

		//测试拷贝构造
		//HashTable<int, int> other(ht);
		//other.Print();

		//find函数
		HashTableNode<string,string>* ret = dict.Find("插入");
		if (ret)
		{
		cout<<"the key is exist: "<<ret->_key<<" : "<<ret->_value<<endl;
		}
		else
		{
		cout<<"it is not exist"<<endl;
		}

	}
}
