#ifndef __SET_FUNCTIONS__
#define __SET_FUNCTIONS__

#include <vector>

inline void set_intersection_nt(std::vector<int>::const_iterator a_begin, 
                         std::vector<int>::const_iterator a_end, 
                         std::vector<int>::const_iterator b_begin, 
                         std::vector<int>::const_iterator b_end,
                         std::back_insert_iterator<std::vector<int>> c_begin)
{
	for(auto it = a_begin; it != a_end; it++)
	{
		if(std::find(b_begin, b_end, *it) != b_end)
		{
			*c_begin.operator++() = *it;
		}
	}
}


inline void set_union_nt(std::vector<int>::const_iterator a_begin, 
                  std::vector<int>::const_iterator a_end, 
                  std::vector<int>::const_iterator b_begin, 
                  std::vector<int>::const_iterator b_end,
                  std::back_insert_iterator<std::vector<int>> c_begin)
{
	for(auto it = a_begin; it != a_end; it++)
	{
		*c_begin.operator++() = *it;
	}
	for(auto it = b_begin; it != b_end; it++)
	{
		if(std::find(a_begin, a_end, *it) == a_end)
		{
			*c_begin.operator++() = *it;
		}
	}
}

template<class It1, class It2, class ItOut>
void set_intersection_t(It1 a_begin, It1 a_end, It2 b_begin, It2 b_end, ItOut c_begin)
{
    for (auto it = a_begin; it != a_end; it++)
	{
		if (std::find(b_begin, b_end, *it) != b_end)
		{
			*c_begin.operator++() = *it;
		}
	}
}

template<class It1, class It2, class ItOut>
void set_union_t(It1 a_begin, It1 a_end, It2 b_begin, It2 b_end, ItOut c_begin)
{
    for(auto it = b_begin; it != b_end; it++)
	{
		*c_begin.operator++() = *it;
	}
	for(auto it = a_begin; it != a_end; it++)
	{
		if(std::find(b_begin, b_end, *it) == b_end)
		{
			*c_begin.operator++() = *it;
		}
	}
}


template<class It1, class It2, class ItOut, class F>
void set_intersection_t(It1 a_begin, It1 a_end, It2 b_begin, It2 b_end, ItOut c_begin, F fun)
{
    for (auto it = a_begin; it != a_end; it++)
	{
		if (fun())
		{
			*c_begin.operator++() = *it;
		}
	}
}

#endif
