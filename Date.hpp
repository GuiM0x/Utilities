#ifndef DATE_HPP_INCLUDED
#define DATE_HPP_INCLUDED

#include <iostream>
#include <ctime>
#include <chrono>

namespace tox {

enum date_format{
	EN,
	FR,
	FORMAT_MAX
};

class Date
{
public:
	Date() = default;

	static std::string get(int format = tox::date_format::EN);
};

std::string Date::get(int format)
{
	// Returning a time point representing the current point in time
	auto now = std::chrono::system_clock::now();
	// Convert this point to a timestamp
	std::time_t now_t = std::chrono::system_clock::to_time_t(now);
	
	// EN Format
	if(format == tox::date_format::EN){
		return std::string{std::ctime(&now_t)};
	}
	
	// FR Format
	if(format == tox::date_format::FR){
		char tmp_date[100];
		std::strftime(tmp_date, sizeof(tmp_date), "%a %d %b %Y %T", std::localtime(&now_t));
		return std::string{tmp_date};
	}
	
	return std::string{};
}

} // End of namespace!

#endif // DATE_HPP_INCLUDED
