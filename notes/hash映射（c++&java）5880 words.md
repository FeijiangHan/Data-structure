# hash简介

  前面说了，map的key如果没有要求可比较性、规定map每次查找操作时间复杂度O(1)，则使用hash table去构建一个hashmap。

下面就介绍一下什么是hash。



## 前提需求-数组

​    使用数组存储数据，我们要得到此数据只需要用index访问即可，时间复杂度为O(1)。这是典型的空间换时间，比如下面这个例子，我们往数组中存放公司信息，把数组下标视为公司电话，这样我们就可以直接通过电话得到对应公司的信息了。虽然查询的时间复杂度O(1)，但是我们申请了1000000的空间，倘若公司的号码都是4开头的，那空间的浪费绝对是很大的。![image.png](https://s2.loli.net/2022/02/10/S3BkGxd1YZaPoeN.png)





  为了实现类似上面的那种操作且降低空间浪费，我们不能直接拿电话号当索引，而是需要对公司的电话进行加工（映射、取模、&运算），然后把加工后的值当做数组的index，如果电话号经过加工后均匀得到了1,2,3,4,5,6,7....,100这些数值，我们把这些数值当做开辟数组的下标，这样不仅可以申请更少的空间，这些空间的使用率也大大提高。

  我们依旧**需要一个数组**存放公司信息，这个数组的索引是连续的；我们还需要**一个函数**可以用来第一次加工公司的电话号码，但是首次加工后的数值可能超出了数组下标的范围，无法直接当做下标；然后电话号加工后的值再经过**第二次加工**，使得第二次加工后的值范围在开辟数组的索引范围之内。

#### 现在根据上面的描述得到hash有关的三个概念：

需要一个数组 ： 这个数组就是**哈希表、 hash table、 散列表**中的bucket数组。这个数组和链表等结构一起构成了哈希表。

一个函数第一次加工电话号： **哈希函数** hashfunction

第二次加工： **模运算 / &运算**

第一次加工的结果：**哈希值 hashcode**

如果第二次加工结果相同： **哈希冲突、equals方法**



 **寻找数据时：**一串电话号------哈希函数加工得到哈希值------哈希值和数组长度取模运算第二次加工------得到哈希表bucket数组的索引------用索引找到数组内数据

 **添加数据时：** 同时给出key和value，**hash_code(key) 计算出key对应的哈希值**，再通过模运算或&运算得到哈希表bucket数组的索引，在这个索引对应的数组单元处添加数据。如果出现哈希冲突，就使用分链表法，在对应数组单元上添加链表节点，每个节点内存放节点对应的key和value，**在最终添加前还会进行一步比较操作**，比较一下新添加的key是否已经存在于链表中，如果存在则仅仅覆盖这个key对应节点的value即可，不用再添加一个节点了。



##### <u>核心在于**hash_code(key)** 计算 和 添加前的 **比较操作** 。</u>







## 哈希表

put("Jack", 666);
put("Rose", 777);
put("Kate", 888);

![image.png](https://s2.loli.net/2022/02/10/LzMZanVUjF7HKDe.png)





## 哈希冲突

  hash函数设计不单调时，不同key生成的hashcode可能是相同的，因此对应数组的索引也相同，就发生了冲突。

open addressing法就是说，当发生冲突时，我继续往下找其他索引，直到找到一个不冲突的索引。这种方法一定可以使得每个数组单元内只对应一个key的数据。

rehash设计多个hash函数，冲突时再换个函数重新加工。

separate Chaining把每个数组单元对应不止一个数据，当发生冲突时两个key对应的数据可以利用链表或红黑树一起挂在一个索引对应的数组单元上。



![image.png](https://s2.loli.net/2022/02/10/A1uWMFgtP5vRm6s.png)



c++ 和 java使用的都是第三种方法，我更喜欢称其为“分链法”，因为看起来就像有很多条分离的链子。

下图是java的，当单链表长度太长时，java就会自动把链表转为红黑树，以便于搜索添加的时间复杂度降低。



![image.png](https://s2.loli.net/2022/02/10/HeoVGmZE4vLjJI6.png)

c++的做法是当链表长度太长（大于bucket长度）时，就打碎链表。具体做法就是给bucket扩容，然后利用新的bucket长度重新映射数组下标，这样就可以剪短一个数组单元上的长链了。





## 哈希函数

####  哈希表中哈希函数的实现步骤大概如下

1. 先生成 key 的哈希值（必须是整数）
2. 再让 key 的哈希值跟数组的大小进行相关运算，生成一个索引值



第一种方法可以用取模运算： 哈希表大小一般是质数

```c++
  bucket_index = hash_code(key) % bucket_size
```

第二种方法可以用&运算:  前提是哈希表大小必须设计为 2 的幂

```c++
  bucket_index = hash_code(key) & (bucket_size - 1)
```



#### ◼ key 的常见种类可能有

整数、浮点数、字符串、自定义对象
不同种类的 key，哈希值的生成方式不一样，但目标是一致的
✓ 尽量让每个 key 的哈希值是唯一的
✓ 尽量让 key 的所有信息参与运算





# c++的hash实现：

下面是我自己写的hashcode计算逻辑，这些代码是基于c++14/17的unorderedmap改编的，可读性更强，并在c++11新特性处做了注释。

```c++
// c++计算哈希值用的是FNV_1a，把各种类型数据都转化为unsigned char*类型，然后每次取8bits进行运算。
namespace FNV_1a {
	/*
	> **offset_basis：**初始的哈希值
	> **FNV_prime：**FNV用于散列的质数
	> **octet_of_data：**8位数据（即一个字节）

	 **FNV-1a描述：**
	hash = ***offset_basis
	for each octet_of_data to be hashed
	hash = hash xor octet_of_data
	hash = hash * FNV_prime
	return hash
	*/

	constexpr size_t offset_basis = 14695981039346656037ULL;  // 初始hash值
	constexpr size_t FNV_prime = 1099511628211ULL; // FNV用于散列的质数

	// accumulate range [_First, _First + _Count) into partial FNV-1a hash _Val
	_NODISCARD inline size_t fnv_64a_realize(const unsigned char* const Contents, const size_t _Count)
	{
		size_t hashVal = offset_basis;
		for (size_t _Idx = 0; _Idx < _Count; ++_Idx) {
			hashVal ^= static_cast<size_t>(Contents[_Idx]); // 8位数据（即一个字节）
			hashVal *= FNV_prime;
		}

		return hashVal;
	}


	template <class K>
	_NODISCARD size_t fnv_64a(const K& key) noexcept
	{
		return fnv_64a_realize(&reinterpret_cast<const unsigned char&>(key), sizeof(K));
	}  // 替代&reinterpret_cast<const unsigned char&>

}


// 下面是我实现的简易hash类，目的是提供仿函数接口。c++不用模板函数而用模板类，贯彻面向对象编程。
namespace MyHash {
	template <class K>
	struct myhash
	{
		size_t operator()(const K& key) const noexcept
		{
			return FNV_1a::fnv_64a(key);
		}
	};

	template <>
	struct myhash<float> {
		size_t operator()(const float K) const noexcept {
			return FNV_1a::fnv_64a(K == 0.0F ? 0.0F : K);
		}
	};

	template <>
	struct myhash<double> {
		size_t operator()(const double K) const noexcept {
			return FNV_1a::fnv_64a(K == 0.0 ? 0.0F : K);
		}
	};

	template <>
	struct myhash<long double> {
		size_t operator()(const long double K) const noexcept {
			return FNV_1a::fnv_64a(K == 0.0L ? 0.0L : K);
		}
	};

#include<cstddef>
	// nullptr_t 是一个基本数据类型，代表各种类型的空指针nullptr，可以作为模板参数且不会被识别为T*。必须需要头文件<cstddef>
	// noexcept 说明函数中没有异常，便于编译器优化
	// void* 泛指指针类型，各种数据类型的指针都可以用void* 表示。指针是_64ptr类型数据
	// {} 是初始化，c++11可以用{}直接初始化，相当于void* Null = nullptr
	// 模板元编程，全特化，偏特化
	/*
	如果特化版本中，所有的模板参数都被替换成了具体类型，那么就叫做全特化
template<>
struct Stack<int*, Array>
{
	...
};

	如果参数中还有非具体类型，那么就叫做部分特化或者偏特化，例如：
template<typename T>
struct Stack<T, Array>
{
	...
}；
	*/

	template <>
	struct myhash<nullptr_t> {
		size_t operator()(nullptr_t) const noexcept {
			void* Null{}; // 可以将C++11提供的大括号初始化作为统一的初始化方式
			return FNV_1a::fnv_64a(Null);
		}
	};

    
	//template <class _Elem, class _Traits, class _Alloc>
	//struct hash<basic_string<_Elem, _Traits, _Alloc>> {
	//	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef basic_string<_Elem, _Traits, _Alloc> _ARGUMENT_TYPE_NAME;
	//	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;

	//	_NODISCARD size_t operator()(const basic_string<_Elem, _Traits, _Alloc>& _Keyval) const noexcept {
	//		return _Hash_array_representation(_Keyval.c_str(), _Keyval.size());
	//	}
	//};
   /* c++17 实现了string 的hash ，下面是我自己的实现，有一些偏差*/
	template <>
	struct myhash<std::string> {
		size_t operator()(const std::string K) const noexcept {
			return FNV_1a::fnv_64a_realize(reinterpret_cast<const unsigned char*>(K.c_str()), K.size());
		}
	};
	

}


// 最终计算的函数
class HashVal
{
public:
	//计算种子数值
	template<typename T>
	inline void hash_combine(size_t& seed, const T& val)
	{
		seed ^= MyHash::myhash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	//递归调用出口
	template<typename T>
	inline void hash_value(size_t& seed, const T& val)
	{
		hash_combine(seed, val);
	}

	template<typename T, typename... Types>
	inline void hash_value(size_t& seed, const T& val, const Types&... args)
	{
		//重新计算种子值
		hash_combine(seed, val);
		//递归调用
		hash_value(seed, args...);
	}

	// unsigned __int64
	template<typename... Types>
	inline size_t hash_value(const Types&... args)
	{
		size_t seed = 0;
		hash_value(seed, args...);
		return seed;
	}
};
```



FNV-1和FNV-1a算法对于最终生成的哈希值（hash）有一定限制

　　1，hash是无符号整型

　　2，hash的位数（bits），应该是2的n次方（32，64，128，256，512，1024），一般32位的就够用了。

> **相关变量：**

> > **hash值：**一个n位的unsigned int型hash值
>
> > **offset_basis：**初始的哈希值
>
> > **FNV_prime：**FNV用于散列的质数
>
> > **octet_of_data：**8位数据（即一个字节）

> **FNV-1描述：**

> > hash = ***offset_basis\***

> > for each octet_of_data to be hashed

> > > hash = hash * ***FNV_prime\***
>
> > > hash = hash xor octet_of_data

> > return hash

> **FNV-1a描述：**

> > hash = ***offset_basis\*** 
> >
> > for each octet_of_data to be hashed

> > > hash = hash xor octet_of_data
> > >
> > > hash = hash * **FNV_prime**
> >
> > return hash

**FNV_prime的取值: 
**32 bit FNV_prime = 2^24 + 2^8 + 0x93 = 16777619
**64 bit FNV_prime = 2^40 + 2^8 + 0xb3 = 1099511628211**
128 bit FNV_prime = 2^88 + 2^8 + 0x3b = 309485009821345068724781371
256 bit FNV_prime = 2^168 + 2^8 + 0x63 =374144419156711147060143317175368453031918731002211
512 bit FNV_prime = 2^344 + 2^8 + 0x57 = 35835915874844867368919076489095108449946327955754392558399825615420669938882575
126094039892345713852759
1024 bit FNV_prime = 2^680 + 2^8 + 0x8d = 
50164565101131186554345988110352789550307653454047907443030175238311120551081474
51509157692220295382716162651878526895249385292291816524375083746691371804094271
873160484737966720260389217684476157468082573

**offset_basis的取值: 
**32 bit offset_basis = 2166136261
**64 bit offset_basis = 14695981039346656037**
128 bit offset_basis = 144066263297769815596495629667062367629
256 bit offset_basis = 100029257958052580907070968620625704837092796014241193945225284501741471925557
512 bit offset_basis = 96593031294966694980094354007163104660904187456726378961083743294344626579945829
32197716438449813051892206539805784495328239340083876191928701583869517785
1024 bit offset_basis = 14197795064947621068722070641403218320880622795441933960878474914617582723252296
73230371772215086409652120235554936562817466910857181476047101507614802975596980
40773201576924585630032153049571501574036444603635505054127112859663616102678680
82893823963790439336411086884584107735010676915



## hash函数

  我在c++中找到了三个hash函数：

```c++
int a = 123;
auto num1 = reinterpret_cast<const char& >(a);
cout << typeid(num1).name() << endl;
cout << typeid(num1).hash_code() << endl;

cout << typeid(123).hash_code() << endl;
cout << hash<char>()(123) << endl;
cout << hash_val(123) << endl;
```

![image.png](https://s2.loli.net/2022/02/10/YJnoZVsELbiqk6f.png)





### hash_val()

这个哈希值是在一定基础上进一步加工的：hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

0x9e3779b9是黄金分割比；

给定一个seed，让这个seed和hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2) 异或运算，运算结果是hashcode；

默认seed是0时，对异或运算结果没有影响；



[^Types ... args]: 这个名叫variadic template，cppreference上把这个归到了Parameter Pack[1]里，中文页面译名叫变参（类/函数）模板。名字上看上去是variadic arguments和variable template缝合出来的名字，实际的特性也确实结合了前者的可变（variadic）和后者的泛化（template），组合拳的功效超乎想象。传入的参数是一个pack，作用于普通函数参数列表时表示参数列表长度可以是任意的，作用于类型pack时代表这一块的每个类型都可以是任意的。一般用于递归调用。

传入多个参数时，其实就是递归调用，最终的出口是hash_combine函数。因此如果我们一次性传入多个不同类型的数据，每个数据都会参与最终seed的运算，雨露均沾正是我们想看到的。

```c++
//计算种子数值
template<typename T>
inline void hash_combine(size_t& seed, const T& val)
{
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// unsigned __int64
template<typename... Types>
inline size_t hash_val(const Types&... args)
{
	size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}


template<typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args)
{
	//重新计算种子值
	hash_combine(seed, val);
	//递归调用
	hash_val(seed, args...);
}


//递归调用出口
template<typename T>
inline void hash_val(size_t& seed, const T& val)
{
	hash_combine(seed, val);
}


int main()
{
    cout << hash<int>::_Do_hash(1) << endl;
	cout << hash<int*>()(nullptr) << endl;
	cout << hash<int>()(2) << endl;
	cout << hash<float>()(3.321) << endl;
	cout << hash<char>()('abc') << endl;
	cout << hash<string>()("abc") << endl;
    
    cout << hash_val(1) << endl;
	cout << hash_val(2) << endl;
	cout << hash_val(1.11) << endl;
	cout << hash_val('a') << endl;
    
    return 0;
}

```



要实现自定义数据类型的hash函数，需要自定义hash类和仿函数，以及重写equal_to类和仿函数。

下面是基本数据类型float自带的hash类及其仿函数，equal_to类及其仿函数，我们模仿这个写一下自定义数据类型的hash类和equal_to类。

```c++
template <>
struct hash<float> {
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef float _ARGUMENT_TYPE_NAME;
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;
	_NODISCARD size_t operator()(const float _Keyval) const noexcept {
		return _Hash_representation(_Keyval == 0.0F ? 0.0F : _Keyval); // map -0 to 0
	}
};


template <class _Ty = void>
struct equal_to {
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef _Ty _FIRST_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef _Ty _SECOND_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef bool _RESULT_TYPE_NAME;

    _NODISCARD constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const {
        return _Left == _Right;
    }
};
```



先自定义数据Man：

```c++
class Man
{
public:
	int year;
	string name;
	Man(int y, string n)
	{
		year = y;
		name = n;
	}
};
```



实现：

自定义类中可能有多个数据，此时一起传入hash_val函数即可，最终计算的seed和每个参数都有关。

```c++
template<>
struct hash<Man>
{
	std::size_t operator()(const Man& man) const
	{
		return hash_val(man.name,man.year);
	}
};


	template<>
	struct equal_to<Man>
	{
		bool operator()(const Man& c1, const Man& c2) const
		{
			return !c1.name.compare(c2.name) && c1.year == c2.year;
		}
	};
```



因为自带的equal_to仿函数中默认是 return _Left == _Right，所以我们重载==也可以使得自定义数据可比较。

```c++
bool operator==(Man m1, Man m2)
{
	return !m1.name.compare(m2.name) && m1.year == m2.year;
}
```



要实现上面的hash_value()函数，必须要实现hash类及其仿函数，接下来看看hash类的设计。

### hash< >( )(para) 

 这个是仿函数，源码可以看到有hash模板类，浮点数单独拿出来特化。本质就是把各种类型数据都转换为字符串，然后把字符串的每一位都进行一定的运算得到hash值。

```c++
template <class _Kty>
struct hash
    : _Conditionally_enabled_hash<_Kty,
          !is_const_v<_Kty> && !is_volatile_v<_Kty> && (is_enum_v<_Kty> || is_integral_v<_Kty> || is_pointer_v<_Kty>)> {
    // hash functor primary template (handles enums, integrals, and pointers)
    static size_t _Do_hash(const _Kty& _Keyval) noexcept {
        return _Hash_representation(_Keyval);
    }
};
 //这是hash的模板，如果传入整形或者string、char，都走这个hash类的仿函数，仿函数内调用_Do_hash(),再调用_Hash_representation()

——————————————————————————————————————————————————————————————————————————————————————————————————————————————————--————————————
   
    
_______________________________________________________________________________________________________________________________

 // 这是特化的模板，如果传入浮点数或者空指针就走这个仿函数，内部也是调用_Hash_representation()
     
template <>
struct hash<float> {
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef float _ARGUMENT_TYPE_NAME;
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;
	_NODISCARD size_t operator()(const float _Keyval) const noexcept {
		return _Hash_representation(_Keyval == 0.0F ? 0.0F : _Keyval); // map -0 to 0
	}
};

template <>
struct hash<double> {
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef double _ARGUMENT_TYPE_NAME;
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;
	_NODISCARD size_t operator()(const double _Keyval) const noexcept {
		return _Hash_representation(_Keyval == 0.0 ? 0.0 : _Keyval); // map -0 to 0
	}
};

template <>
struct hash<long double> {
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef long double _ARGUMENT_TYPE_NAME;
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;
	_NODISCARD size_t operator()(const long double _Keyval) const noexcept {
		return _Hash_representation(_Keyval == 0.0L ? 0.0L : _Keyval); // map -0 to 0
	}
};

template <>
struct hash<nullptr_t> {
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef nullptr_t _ARGUMENT_TYPE_NAME;
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;
	_NODISCARD size_t operator()(nullptr_t) const noexcept {
		void* _Null{};
		return _Hash_representation(_Null);
	}
};

___________________________________________________________________________________________________________________
    _Hash_representation()最后会调用_Fnv1a_append_bytes()函数，在这个函数内计算整形、浮点型、char、string的哈希code。
    --从前到后遍历这个传入的参数，对每一位，先转换为 size_t，然后和 _Val 进行异或（注意 _Val 传入就是 _FNV_offset_basis）
    --然后 _Val *= _FNV_prime;。也就是传入的是 string 的话，对每个字符，转换成 size_t（应该就是 ascii 码），异或，乘一个常量，循环。
    -- string 的 hash 值确实是这么计算的，字符也是这么处理，就相当于是长度为 1 的字符串。
    --reinterpret_cast<const unsigned char&>(_Keyval)把key强制转换为unsigned char&类型。如果是整型也会把整型转换为unsigned char*，总结来说就是各种类型都会转换为char*字符串类型，而这个字符串的长度和sizeof(_Kty)一致，比如int(123)转换为char*字符串，内存中占用是4字节
   
        
_INLINE_VAR constexpr size_t _FNV_offset_basis = 14695981039346656037ULL;
_INLINE_VAR constexpr size_t _FNV_prime        = 1099511628211ULL;


template <class _Kty>
_NODISCARD size_t _Hash_representation(const _Kty& _Keyval) noexcept { // bitwise hashes the representation of a key
    return _Fnv1a_append_value(_FNV_offset_basis, _Keyval);    注意 _Val 传入就是 _FNV_offset_basis
}


template <class _Kty>
_NODISCARD size_t _Fnv1a_append_value(
    const size_t _Val, const _Kty& _Keyval) noexcept { // accumulate _Keyval into partial FNV-1a hash _Val
    static_assert(is_trivial_v<_Kty>, "Only trivial types can be directly hashed.");
    return _Fnv1a_append_bytes(_Val, &reinterpret_cast<const unsigned char&>(_Keyval), sizeof(_Kty));
}  


_NODISCARD inline size_t _Fnv1a_append_bytes(size_t _Val, const unsigned char* const _First,
	const size_t _Count) noexcept { // accumulate range [_First, _First + _Count) into partial FNV-1a hash _Val
	for (size_t _Idx = 0; _Idx < _Count; ++_Idx) {
		_Val ^= static_cast<size_t>(_First[_Idx]);
		_Val *= _FNV_prime;
	}   注意 _Val 传入就是 _FNV_offset_basis
	return _Val;
}
```

下面是根据_Fnv1a_append_bytes设计的代码：arr数组可以看到字符串每一位的数值

```c++
int num = 127;
size_t _FNV_offset_basis = 14695981039346656037ULL;
size_t _FNV_prime = 1099511628211ULL;
char* _First = &reinterpret_cast<char&>(num);
size_t val = _FNV_offset_basis;

cout << sizeof(int) << endl;
size_t arr[sizeof(int)];
for (size_t _Idx = 0; _Idx < sizeof(int); ++_Idx) {
	arr[_Idx] = static_cast<size_t>(_First[_Idx]);
}
```

	float val1 = 1.2f;
	double val2 = 1.2;
	const unsigned char* a = &reinterpret_cast<const unsigned char&>(val1);
	const unsigned char* b = &reinterpret_cast<const unsigned char&>(val2);

double 和 float的不同，需要分别实现hash类，所以c++自带实现了三种浮点型的hash类。



### typeid(ele).hash_code()

typeid里面的hash_code() 可以生成唯一的哈希值。

```c++
int a = 123;
auto num1 = reinterpret_cast<const char& >(a);
cout << typeid(num1).name() << endl;

cout << typeid(num1).hash_code() << endl;
cout << typeid(123).hash_code() << endl;
```





# Java中hash实现



## key到哈希值

java对不同的数据类型有不同处理，而c++统一处理。



### int

整数值当做哈希值
比如 10 的哈希值就是 10

### float

将存储的二进制格式转为整数值,再当成哈希值。

### long、double

对于64位数据，让前32位和后32位做异或运算，把运算结果转换为int类型，再当成哈希值。

```c++
一般采用移位操作获取前32位： (int) a^(a>>32)
```

### string

string类型数据采用递推方式：类比10进制计算，目的是把string的每一位都利用上，确保数据的完全性。

123 = 1+0）* 10 + 2）*10 + 3

( ( (s1+0）* 31+s2）* 31 + s4 )*31.....

```java
int hash=0;
string s = 字符串;
for(int i = 0; i < 字符串长度;i++)
{
    hash = (int(s[i])+hash)*31;
}
```

之所以用31是因为：31=32-1=(1<<6) - 1，java会自动优化为移位运算，提高效率。

### 自定义数据类型

自定义数据类型无法比较，无法计算哈希值，因此要自己实现hash和equalto。

要注意：计算哈希值时选用哪几个参数进行计算，判断相等时就选哪几个参数一起判断，确保计算和比较的一致性。

例如：自定义类Person，成员变量是《名字》《年龄》《班级》，如果计算哈希值时只选取名字和年龄进行计算，那么比较时也仅判断名字和年龄是否同时相等即可。

自定义类型哈希值计算：因为可能有多个参数一起参与运算，为了保证每个参数都参与，依旧可以选择123 = 1+0）* 10 + 2）*10 + 3这样的拆分逻辑。首先分别算出各个参数的哈希值，再类比进制计算把每个哈希值加到一起。



## c++和java的实现比较

### 1.传入多个参数计算哈希值时：

c++ 采用varidic template+递归的方式，java采用递推+循环的模式，目的一致：**都是为了把每个参数都参与运算**。

### 2.哈希计算模式：

c++采用fnv算法，把各种数据都转换为一个个的8its char单元；java采用int转换法，各种非32_int数据（浮点型、64位整形、字符串）在机器码的层面的转为int，然后直接把int当做哈希值。**目的一致：因为各种数据都是以0101机器码储存的，哈希值的计算应该合理利用所有机器码。c++是8bits为一组全都利用，java是最终都转化为32bits INT类型。**我个人认为c++的做法更好，更科学。

### 3.计算和比较

c++ 和java都用类表示hash计算和比较逻辑。其内部自带一些基础数据类型的类，如果是自定义数据，要同时实现hash类和equal_to类。

之所以要这两步，是因为计算出hash值以后，还要利用比较逻辑判断是否hash冲突。

冲突后的逻辑：**都采用链地址法解决冲突**。

### 4.链地址法具体实现思路：

c++采用双向链表，如果链表过长就给bucket扩容并重新计算哈希值。

java采用单向链表和红黑树，如果链表长了就转换为红黑树。

**我个人认为java在这一步做的更好，因为单链表占用内存少，红黑树查找快。**





## 哈希值到bucket索引

前面仅仅是根据key计算出hash值，计算出以后要根据哈希值和bucket长度计算index。

下面介绍两种方法：

### 1.取模运算（bucket长度是质数/素数）

c++的旧版本采用取模运算，官方提供了一个质数/素数结构体用于bucket动态扩容。

```c
//List all the integer number no less than 57 total number is 28
//And each number is about half of its next number
static int prime[28] =
{
    57,        97,         193,        389,        769,
    1543,      3079,       6151,       12289,      24593,
    49157,     98317,      196613,     393241,     786433,
    1572869,   3145739,    6291469,    12582917,   25165843,
    50331653,  100663319,  201326611,  402653189,  805306457,
    1610612741
};
```

学过数学的就知道取模运算时，当模因子是素数时，得到的结果更为分散、独立。

比如0-9以内的 模5运算和模2运算的结果：

模5 ：0 1 2 3 4 0 1 2 3 4

模2：0 1 0 1 0 1 0 1 0 1

### 2.与运算（bucket长度是2的幂）

| hashCode                          | hashCode&00001111 |
| --------------------------------- | ----------------- |
| 0101100011010111 0011111010011011 | 11                |
| 0010000000000000 0011111010011011 | 11                |
| 0000000000000000 0011111010011011 | 11                |

看上面例子，我们得到三个哈希值，这三个值和00001111（2^4-1）做与运算，结果必定限制在0000到1111之间，保证了结果限定在一定范围内，可以当做数组的索引。

因此我们要保证bucket的容量是2的幂(1<<n)，然后计算索引时让 **哈希值 & （ (1<<n) - 1）**，即可保证最终结果的二进制值限定在00000（n个0）到1111（n个1）之间。



java和c++14的bucket长度都限定为2的幂，因此采用&运算。

### &运算相较于%运算的好处：

1.&运算是针对二进制代码的运算，不用考虑哈希值时负数

2.&运算时bucket数组动态扩容可以不用按照写死的素数值扩大，内存利用率更高。
