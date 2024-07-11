#pragma once
#include <type_traits>

/*
算法向迭代器提问时的中间层：用于萃取迭代器的类型信息
*/
namespace mystl {
	//助手类
	template<class T, T v>
	struct m_integral_constant
	{
		static constexpr T value = v;
	};

	template <bool b>
	using m_bool_constant = m_integral_constant<bool, b>;

	typedef m_bool_constant<true> m_true_type;
	typedef m_bool_constant<false> m_false_type;

	/*****************************************************************************************/
	// type traits

	// is_pair
	template<class T1, class T2>
	struct pair;
	// 在 pair 结构体中定义一个模板结构体 is_pair，接受一个类型参数 T
	template<class T>
	struct is_pair : mystl::m_false_type {};// 默认为 false 类型

	// 专门化 is_pair 用于 mystl::pair 类型
	template<class T1, class T2>
	struct is_pair<mystl::pair<T1, T2>> : mystl::m_true_type {};// 对于 mystl::pair 类型为 true 类型

	/*  使用场景：
		mystl::pair<int, double>::is_pair<mystl::pair<int, double>>::value  // 结果为 true
		mystl::pair<int, double>::is_pair<int>::value  // 结果为 false
	*/
}
