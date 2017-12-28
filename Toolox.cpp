#include "Toolox.h"

/////////// DICE ROLL GENERATOR
int Toolox::rollTheDice(int valmin, int valmax)
{
    static std::mt19937 generator{static_cast<unsigned>(time(nullptr))};
    std::uniform_int_distribution<> dist{valmin, valmax};
	
    return dist(generator);
}

/////////// TEXT FILE TO STRING
std::string Toolox::textFileToString(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::string line, text;

    if(file.is_open()){
        while(std::getline(file, line))
            text += (line + '\n');

        file.close();
    }

    return text;
}

/////////// TEXT FILE TO STRING
std::string& Toolox::textFileToString(const std::string& filePath, std::string& str)
{
    std::ifstream file(filePath);
    std::string line;

    if(file.is_open()){
        while(std::getline(file, line))
            str += (line + '\n');

        file.close();
    }

    return str;
}

/////////// STRING TO LOWER
std::string& Toolox::stringToLower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	
    return str;
}

/////////// ERASE PUNCTUATION
std::string& Toolox::erasePunctuation(std::string& str)
{
    str += ' '; // Avoid error in case of punctuation at the end of the string

    for(auto it = str.begin(); it != str.end(); ++it) {
		// Erase if : !alpha AND !space AND !eol
        if(!(std::isalpha(*it)) && *it != ' ' && *it != '\n')
            str.erase(it);
	}

    return str;
}

/////////// DISPLAY OCCUR IN STRING
std::ostream& Toolox::allOccurInString(std::ostream& os, std::string str, const bool& caseSensitive)
{
    if(!caseSensitive)
        stringToLower(str);

    erasePunctuation(str);

    std::map<std::string, size_t> word_count;
    std::string word;
    std::istringstream string_flux(str);

    while(string_flux >> word)
        ++word_count[word];

    for(const auto& w : word_count)
        os << "\'" << w.first << "\'" << " occurs " << w.second
                  << ((w.second > 1) ? " times." : " time.") << '\n';

    return os;
}

/////////// DISPLAY OCCUR IN FILE
std::ostream& Toolox::allOccurInTextFile(std::ostream& os, const std::string& filePath, const bool& caseSensitive)
{
    std::string text = textFileToString(filePath);
    allOccurInString(os, text, caseSensitive);

    return os;
}