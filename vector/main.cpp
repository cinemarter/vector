#include "vector.h"
#include <vector>

int main()
{
	//std::vector<int> s_vec;
	m_vector<int> s_vec;
	s_vec.push_back(1);
	s_vec.push_back(2);
	s_vec.push_back(3);
	s_vec.push_back(4);
	s_vec.push_back(5);
	std::vector<int> vect = { 1,2,3,4,5 };
	std::vector<int>::iterator itr = vect.begin();
	(itr++)++;
	++(++itr);
	
	std::cout << *itr;
	/*std::vector<int>::iterator s_itStart = s_vec.begin();
	std::vector<int>::iterator s_itEnd = ++(++s_itStart);
	std::vector<int> s_vec2(s_vec.begin(), s_itEnd);*/
	m_vector<int>::iterator s_itStart = s_vec.begin();
	m_vector<int>::iterator s_itEnd = s_itStart+2;
	m_vector<int> s_vec2(s_vec.begin(), s_itEnd);
	//(s_itStart++)++;
	std::cout << s_vec2[0] << " " << s_vec2[1];
	
	
	std::vector<int> s_vec_1;
	std::vector<int>::iterator s_vec_1_it = s_vec_1.begin();
	std::vector<int>::iterator s_vec_1_it2 = s_vec_1_it - 4;
	s_vec_1_it - 4 = s_vec_1.end();
	
	////std::vector<int>::iterator itr = --s_itEnd;
	////std::vector<int>::iterator itr1 = s_itEnd--;
	//m_vector<int>::iterator itr = --s_itEnd;
	//m_vector<int>::iterator itr1 = s_itEnd--;
	//for (; s_itStart != s_itEnd; ++s_itStart)
	//{
	//	int x1 = *s_itStart;
	//	std::cout << *s_itStart << std::endl;
	//}


	
    m_vector<int> vec(4);
	//func(4);
	m_vector<int> vec1(vec);
	m_vector<int> vec2(std::move(vec));
	
	vec2.push_back(8);
	int x = vec2[4];
	vec2.emplace_back(9);
	int y = vec2[5];
	vec1.push_back(4);
	vec1.emplace_back(6);
	
	m_vector<int>::iterator itStart = vec1.begin();
	m_vector<int>::iterator itEnd = vec1.end();
	itStart++;
	++itStart;
	for (; itStart != itEnd; ++itStart)
	{
		std::cout << *itStart << std::endl;
	}


	return 0;
}
