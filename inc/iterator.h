#pragma once

#include <cstddef>
#include "type_traits.h"
/*
迭代器，包含了一些模板结构体与全局函数，
*/

namespace mystl {
	//五种迭代器类型
	struct input_iterator_tag {}; //标识输入迭代器。
	struct output_iterator_tag {}; //标识输出迭代器。
	struct forward_iterator_tag : public input_iterator_tag {}; //标识前向迭代器。
	struct bidirectional_iterator_tag : public forward_iterator_tag {}; //标识双向迭代器。
	struct random_access_iterator_tag : public bidirectional_iterator_tag {}; //标识随机访问迭代器。

	// iterator 模板
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category	iterator_category;	//表示迭代器的类型标签（如 input_iterator_tag、output_iterator_tag 等）。
		typedef T			value_type;			//表示迭代器指向的值类型（即元素的类型）。
		typedef Pointer		pointer;			
		typedef Reference	reference;
		typedef Distance	difference_type;	//表示两个迭代器之间的距离类型，默认为 ptrdiff_t。ptrdiff_t 是一个有符号整数类型，用于表示指针之间的差值。
	};

	// iterator traits
	//has_iterator_cat 结构体用于检测类型 T 是否有 iterator_category 类型。
	template <class T>
	struct has_iterator_cat
	{
	private:
		struct two { char a; char b};
		template <class U> static two test(...);
		template <class U> static char test(typename U::iterator_category* = 0);
	public:
		static const bool value = sizeof(test<T>(0)) == sizeof(char);
	};

	template <class Iterator, bool>
	struct iterator_traits_impl {};

	template <class Iterator>
	struct iterator_traits_impl<Iterator, true>
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
		typedef typename Iterator::difference_type   difference_type;
	};

	//主模板（默认模板）当第二个模板参数 bool 为 false 时，这个模板是空的，没有任何特性提取。
	template <class Iterator, bool>
	struct iterator_traits_helper {};
	//特化模板 在第二个模板参数 bool 为 true 时启用
	template <class Iterator>
	struct iterator_traits_helper<Iterator, true> : public iterator_traits_impl<Iterator,
		//检查 Iterator::iterator_category 是否可以转换为 input_iterator_tag 或 output_iterator_tag：
		std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
		std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
	{
	};

	// 萃取迭代器的特性
	template <class Iterator>
	struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

	// 针对原生指针的偏特化版本
	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag           iterator_category;
		typedef T                                    value_type;
		typedef T*                                   pointer;
		typedef T&                                   reference;
		typedef ptrdiff_t                            difference_type;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag           iterator_category;
		typedef T                                    value_type;
		typedef const T*                             pointer;
		typedef const T&                             reference;
		typedef ptrdiff_t                            difference_type;
	};

	//has_iterator_cat_of 结构体用于进一步检测类型 T 的 iterator_category 是否可以转换为类型 U。
	template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
	struct has_iterator_cat_of
		: public m_bool_constant<std::is_convertible<typename iterator_traits<T>::iterator_category, U>::value>
	{
	};

	// 检测迭代器的iterator_category类型
	//检测T的iterator_category是否可以转换为类型 U，默认为false
	template <class T, class U>
	struct has_iterator_cat_of<T, U, false> : public m_false_type {};

	//检测Iter的iterator_category是否可以转换为input_iterator_tag
	template <class Iter>
	struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

	//检测Iter的iterator_category是否可以转换为output_iterator_tag
	template <class Iter>
	struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

	//检测Iter的iterator_category是否可以转换为forward_iterator_tag
	template <class Iter>
	struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

	//检测Iter的iterator_category是否可以转换为bidirectional_iterator_tag
	template <class Iter>
	struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

	//检测Iter的iterator_category是否可以转换为random_access_iterator_tag
	template <class Iter>
	struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

	//检测Iter的iterator_category是否为input_iterator_tag或output_iterator_tag
	template <class Iterator>
	struct is_iterator :
		public m_bool_constant<is_input_iterator<Iterator>::value || is_output_iterator<Iterator>::value>
	{
	};

	// 萃取迭代器的 iterator_category
	template <class Iterator>
	typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category Category;
		return Category();
	}
}