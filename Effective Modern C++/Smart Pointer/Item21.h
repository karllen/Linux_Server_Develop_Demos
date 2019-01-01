//Item 21:Prefer std::make_unique and std::make_shared to direct use of new

#include<memory>

template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&...params)
{
	return std::unique_ptr<T>(new T(std::forward<Ts>(params)...);
}
