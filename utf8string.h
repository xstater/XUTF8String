#ifndef _UTF8_STRING_
#define _UTF8_STRING_

#include <string>

class UTF8Char{
	public:
		using uint = unsigned int;

		UTF8Char();
		UTF8Char(const char *);
		UTF8Char(const std::string &);
		UTF8Char(std::string &&);
		UTF8Char(const UTF8Char &);
		UTF8Char(UTF8Char &&);
		~UTF8Char();
		
		uint size()const noexcept;
		
		std::string &data()noexcept;
		uint unicode()const;
	protected:
	private:
		std::string m_data;
};

class UTF8String{
	public:
		using uint = unsigned int;
		
		static uint i_length(const char *);
		static uint i_length(const std::string &);
	
		//a simple iterator
		//all iterators are READ ONLY
		class iterator{
			public:
				iterator(std::string::iterator);
				iterator(const iterator&);
				~iterator();
				
				UTF8Char operator*()const;
				iterator &operator++();
				iterator operator++(int);
				iterator &operator--();
				iterator operator--(int);
				
				bool operator==(const iterator &)const;
				bool operator!=(const iterator &)const;
			protected:
			private:
				std::string::iterator m_itr;
		};
		
		UTF8String();
		UTF8String(const char *);
		UTF8String(const std::string &);
		UTF8String(std::string &&);
		UTF8String(const UTF8String &);
		UTF8String(UTF8String &&);
		template<class IteratorType>
		UTF8String(IteratorType,IteratorType);
		~UTF8String();
		
		UTF8String &operator=(const char *);
		UTF8String &operator=(const std::string &);
		UTF8String &operator=(std::string &&);
		UTF8String &operator=(const UTF8String &);
		UTF8String &operator=(UTF8String &&);
		
		uint size()const noexcept;
		uint length()const noexcept;
		
		const char *data()const noexcept;
		const char *c_str()const noexcept;
		
		void pop_back();
		void push_back(UTF8Char);
		
		UTF8String &append(const char *);
		UTF8String &append(const std::string &);
		UTF8String &append(const UTF8String &);
		template<class IteratorType>
		UTF8String &append(IteratorType,IteratorType);
		
		UTF8String &operator+=(const char *);
		UTF8String &operator+=(const std::string &);
		UTF8String &operator+=(const UTF8String &);
		
		void clear();
		bool empty()const noexcept;
		
		iterator begin()noexcept;
		iterator end()noexcept;
	protected:
	private:
		std::string m_data;
		uint m_length;
};

#endif
