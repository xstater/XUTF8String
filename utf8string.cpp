#include "utf8string.h"

//UTF8Char

UTF8Char::UTF8Char() = default;
UTF8Char::UTF8Char(const char *str)
	:m_data(str){}
UTF8Char::UTF8Char(const std::string &str)
	:m_data(str){}
UTF8Char::UTF8Char(std::string &&str)
	:m_data(std::move(str)){}
UTF8Char::UTF8Char(const UTF8Char &) = default;
UTF8Char::UTF8Char(UTF8Char &&) = default;
UTF8Char::~UTF8Char() = default;
		
UTF8Char::uint UTF8Char::size()const noexcept{
	return m_data.size();
}
		
std::string &UTF8Char::data()noexcept{
	return m_data;
}
UTF8Char::uint UTF8Char::unicode()const{
	uint ucode = 0;
	return ucode;
}

//UTF8String iterator

UTF8String::iterator::iterator(std::string::iterator itr)
	:m_itr(itr){}
UTF8String::iterator::iterator(const UTF8String::iterator&) = default;
UTF8String::iterator::~iterator() = default;
UTF8Char UTF8String::iterator::operator*()const{
	auto itr = m_itr;
	std::string str;
	int count = 0;
	str.push_back(*itr);
	if((*itr & 128) == 0)count = 0;
	else if((*itr & 224) == 192)count = 1;
	else if((*itr & 240) == 224)count = 2;
	else if((*itr & 248) == 240)count = 3;
	else if((*itr & 252) == 248)count = 4;
	else count = 5;
	for(int i=0;i<count;++i){
		++itr;
		if((*itr & 192) == 128)str.push_back(*itr);
		else throw std::runtime_error("UTF8 text error");
	}
	return UTF8Char(str);
}
UTF8String::iterator &UTF8String::iterator::operator++(){
	int offset = 0;
	if((*m_itr & 128) == 0)offset = 1;
	else if((*m_itr & 224) == 192)offset = 2;
	else if((*m_itr & 240) == 224)offset = 3;
	else if((*m_itr & 248) == 240)offset = 4;
	else if((*m_itr & 252) == 248)offset = 5;
	else offset = 6;
	m_itr += offset;
	return *this;
}
UTF8String::iterator UTF8String::iterator::operator++(int){
	auto tmp = *this;
	uint offset = 0;
	if((*m_itr & 128) == 0)offset = 1;
	else if((*m_itr & 224) == 192)offset = 2;
	else if((*m_itr & 240) == 224)offset = 3;
	else if((*m_itr & 248) == 240)offset = 4;
	else if((*m_itr & 252) == 248)offset = 5;
	else offset = 6;
	m_itr += offset;
	return tmp;
}
UTF8String::iterator &UTF8String::iterator::operator--(){
	--m_itr;
	while((*m_itr & 192) == 128)--m_itr;
	return *this;
}
UTF8String::iterator UTF8String::iterator::operator--(int){
	auto tmp = *this;
	--m_itr;
	while((*m_itr & 192) == 128)--m_itr;
	return tmp;
}
bool UTF8String::iterator::operator==(const UTF8String::iterator &itr)const{
	return m_itr == itr.m_itr;
}
bool UTF8String::iterator::operator!=(const UTF8String::iterator &itr)const{
	return m_itr != itr.m_itr;
}

//UTF8String

UTF8String::uint UTF8String::i_length(const char *str){
	uint count = 0;
	uint offset = 1;
	for(uint i = 0;str[i] != '\0';i+=offset){
		if((str[i] & 128) == 0)offset = 1;
		else if((str[i] & 224) == 192)offset = 2;
		else if((str[i] & 240) == 224)offset = 3;
		else if((str[i] & 248) == 240)offset = 4;
		else if((str[i] & 252) == 248)offset = 5;
		else offset = 6;
		++count;
	}
	return count;
}
UTF8String::uint UTF8String::i_length(const std::string &str){
	uint offset = 1;
	uint count = 0;
	for(auto itr = std::begin(str);itr!=std::end(str);itr+=offset){
		if((*itr & 128) == 0)offset = 1;
		else if((*itr & 224) == 192)offset = 2;
		else if((*itr & 240) == 224)offset = 3;
		else if((*itr & 248) == 240)offset = 4;
		else if((*itr & 252) == 248)offset = 5;
		else offset = 6;
		++count;
	}
	return count;
}

UTF8String::UTF8String() = default;
UTF8String::UTF8String(const char *str)
	:m_data(str),m_length(i_length(str)){}
UTF8String::UTF8String(const std::string &str)
	:m_data(str),m_length(i_length(str)){}
UTF8String::UTF8String(std::string &&str)
	:m_data(std::move(str)),m_length(i_length(m_data)){}
UTF8String::UTF8String(const UTF8String &) = default;
UTF8String::UTF8String(UTF8String &&) = default;
template<class IteratorType>
UTF8String::UTF8String(IteratorType begin,IteratorType end)
	:m_data(begin,end),m_length(i_length(m_data)){}
UTF8String::~UTF8String() = default;
		
UTF8String &UTF8String::operator=(const char *str){
	m_data = str;
	m_length = i_length(str);
	return *this;
}
UTF8String &UTF8String::operator=(const std::string &str){
	m_data = str;
	m_length = i_length(str);
	return *this;
}
UTF8String &UTF8String::operator=(std::string &&str){
	m_data = std::move(str);
	m_length = i_length(m_data);
	return *this;
}
UTF8String &UTF8String::operator=(const UTF8String &) = default;
UTF8String &UTF8String::operator=(UTF8String &&) = default;
		
UTF8String::uint UTF8String::size()const noexcept{
	return m_data.size();
}
UTF8String::uint UTF8String::length()const noexcept{
	return m_length;
}
		
const char *UTF8String::data()const noexcept{
	return m_data.data();
}
const char *UTF8String::c_str()const noexcept{
	return m_data.c_str();
}

void UTF8String::pop_back(){
	--m_length;
	auto itr = m_data.rbegin();
	while((*itr & 192) == 128){
		//10xx xxxx
		m_data.pop_back();
		itr = m_data.rbegin();
	}
	m_data.pop_back();//not 10xx xxxx
}
void UTF8String::push_back(UTF8Char chr){
	++m_length;
	for(auto itr = chr.data().cbegin();itr!=chr.data().cend();++itr){
		m_data.push_back(*itr);
	}
}

UTF8String &UTF8String::append(const char *str){
	m_length += i_length(str);
	m_data.append(str);
	return *this;
}
UTF8String &UTF8String::append(const std::string &str){
	m_length += i_length(str);
	m_data.append(str);
	return *this;
}
UTF8String &UTF8String::append(const UTF8String &str){
	m_length += str.m_length;
	m_data.append(str.m_data);
	return *this;
}
template<class IteratorType>
UTF8String &UTF8String::append(IteratorType begin,IteratorType end){
	for(;begin!=end;++begin){
		push_back(*begin);
	}
	return *this;
}

UTF8String &UTF8String::operator+=(const char *str){
	m_length += i_length(str);
	m_data.append(str);
	return *this;
}
UTF8String &UTF8String::operator+=(const std::string &str){
	m_length += i_length(str);
	m_data.append(str);
	return *this;
}
UTF8String &UTF8String::operator+=(const UTF8String &str){
	m_length += str.m_length;
	m_data.append(str.m_data);
	return *this;
}

void UTF8String::clear(){
	m_data.clear();
}
bool UTF8String::empty()const noexcept{
	return m_data.empty();
}

UTF8String::iterator UTF8String::begin()noexcept{
	return iterator(m_data.begin());
}
UTF8String::iterator UTF8String::end()noexcept{
	return iterator(m_data.end());
}
