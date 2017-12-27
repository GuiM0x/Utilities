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
    std::ifstream fichier(filePath);
    std::string line, text;

    if(fichier.is_open()){
        while(std::getline(fichier, line))
            text += (line + '\n');

        fichier.close();
    }

    return text;
}

/////////// TEXT FILE TO STRING
std::string& Toolox::textFileToString(const std::string& filePath, std::string& str)
{
    std::ifstream fichier(filePath);
    std::string line;

    if(fichier.is_open()){
        while(std::getline(fichier, line))
            str += (line + '\n');

        fichier.close();
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
    str += ' '; // Oblige sinon bug dans le cas où une ponctuation se trouverait en fin de chaine

    for(auto it = str.begin(); it != str.end(); ++it)
        if(!(std::isalpha(*it)) && *it != ' ' && *it != '\n') // On conserve espace et saut de ligne aussi
            str.erase(it);

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