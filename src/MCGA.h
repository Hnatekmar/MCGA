#ifndef MCGA_H
#define MCGA_H

#include <functional>
#include <iterator>

// Stream(col.cbegin(), col.cend()).map([](auto& foo) {return foo * foo;}).sum();
namespace MCGA
{
	template<typename Iterator>
	class Stream
	{
		Iterator m_current;
		Iterator m_end;

		template<typename FnType>
		class Aplicator
		{
			Iterator m_current;
			Iterator m_end;
			FnType m_fn;
			public:
				Aplicator(Iterator begin, Iterator end, FnType fn) :
													m_current(begin),
													m_end(end),
													m_fn(fn)
				{
				}

				Aplicator<FnType> operator++(int)
				{
					auto tmp = *this;
					operator++();
					return tmp;
				}

				Aplicator<FnType>& operator++()
				{
					m_current++;
					return *this;
				}

				bool operator==(const Aplicator& rhs)
				{
					return (m_current == rhs.m_current) && (m_end == rhs.m_end);
				}

				bool operator!=(const Aplicator& rhs)
				{
					return !(*this == rhs);
				}
				
				auto operator*()
				{
					return m_fn(*m_current);
				}

				Aplicator<FnType> begin()
				{
					return *this;
				}
			
				Aplicator<FnType> end()
				{
					return Aplicator<FnType>(m_end, m_end, m_fn);
				}
		};

		public:
			Stream(Iterator start, Iterator end) :
								m_current(start),
								m_end(end)
			{
			}

			size_t size()
			{
				size_t count = 0;
				while(m_current != m_end)
				{
					m_current++;
					count += 1;
				}
				return count;
			}

			template<typename Fn>
			void forEach(Fn f)
			{

				while(m_current != m_end)
				{
					f(*m_current);
					m_current++;
				}
			}

			template<typename Fn>
			Stream<Aplicator<Fn>> map(Fn fn)
			{
				auto it = Aplicator<Fn>(m_current, m_end, fn);
				return Stream<Aplicator<Fn>>(it.begin(), it.end());
			}
	};
}

#endif
