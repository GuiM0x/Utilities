#ifndef TOOLOX_H
#define TOOLOX_H

#include <iostream>
#include <random>
#include <time>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <map>


namespace Toolox {
	
	///// DICE ROLL GENERATOR
	rollTheDice(int valmin, int valmax);
	
	///// TEXT FILE TO STRING
    std::string textFileToString(const std::string& filePath);

    ///// TEXT FILE TO STRING
    std::string& textFileToString(const std::string& filePath, std::string& str);

    ///// STRING TO LOWER
    std::string& stringToLower(std::string& str);

    ///// ERASE PUNCTUATION
    std::string& erasePunctuation(std::string& str);

    ///// DISPLAY OCCUR IN STRING
    std::ostream& allOccurInString(std::ostream& os, std::string str, const bool& caseSensitive = true);

    ///// DISPLAY OCCU IN FILE
    std::ostream& allOccurInTextFile(std::ostream& os, const std::string& filePath, const bool& caseSensitive = true);
}

#endif // TOOLOX_H