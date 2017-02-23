#ifndef MCGA_H
#define MCGA_H

#include <functional>

// Stream(col.cbegin(), col.cend()).map([](auto& foo) {return foo * foo;}).sum();
namespace mcga
{
    template<typename Iterator>
    class _range
    {
        Iterator m_start;
        Iterator m_end;
    public:
            _range(Iterator start, Iterator end) :
                                                    m_start(start),
                                                    m_end(end)
            {
            }
            
            const typename std::iterator_traits<Iterator>::value_type& next()
            {
                return *(m_start++);
            }
            
            bool hasNext()
            {
                return m_start != m_end;
            }
    };
    
	template<typename T, typename Iterator>
	class _stream
	{
		template<typename To>
		class Aplicator
		{
			Iterator m_current;
			std::function<To(const T&)> m_fn;
			public:
				Aplicator(Iterator begin,
                          std::function<To(const T&)> fn) :
													m_current(begin),
													m_fn(fn)
				{
				}

                To next()
                {
                    return m_fn(m_current.next());
                }
                
                bool hasNext()
                {
                    return m_current.hasNext();
                }
		};
        
        Iterator m_current;
        
		public:
			size_t size()
			{
				size_t count = 0;
				while(m_current.hasNext())
				{
					m_current.next();
					count += 1;
				}
				return count;
			}

			template<typename F>
			void forEach(F f)
			{
				while(m_current.hasNext())
				{
					f(m_current.next());
				}
			}

			template<typename Val>
			_stream<Val, Aplicator<Val>> map(std::function<Val(const T&)> fn)
			{
				return _stream<Val, Aplicator<Val>>(Aplicator<Val>(m_current, fn));
			}
        
            _stream(Iterator current) : m_current(current)
            {
            }
	};

    template<typename It>
    _stream<typename std::iterator_traits<It>::value_type, _range<It>> stream(It begin, It end)
    {
        return _stream<typename std::iterator_traits<It>::value_type, _range<It>>(_range<It>(begin, end));
    }
}

#endif
