/////////////////////////////////////////////////////////////////////////////////////
/*                                                                                 */
/*   MirrorText.cpp                                                                */
/*   -----------------------                                                       */
/*   Author : Guit0x                                                               */
/*                                                                                 */
/*   Type            : Program (terminal)                                          */
/*   OS Dependencies : none                                                        */
/*   Library Used    : STL                                                         */
/*   Namespace       : gx                                                          */
/*                                                                                 */
/*   Date contains only one static function to get date (return string).           */
/*                                                                                 */
/////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <map>

namespace gx{

class TextMirror
{
public:
    TextMirror() = default;

public:
    std::string reverseText(const std::string& text) const;
    std::string computeMirrorVersion(const std::string& text) const;

private:
    std::map<char, std::string> m_lowerChars{
        {'a', "\u0250"},
        {'b', "\u0071"},
        {'c', "\u0254"},
        {'d', "\u0070"},
        {'e', "\u01DD"},
        {'f', "\u025F"},
        {'g', "\u0253"},
        {'h', "\u0265"},
        {'i', "\u1D09"},
        {'j', "\u027E"},
        {'k', "\u029E"},
        {'l', "\u006C"},
        {'m', "\u026F"},
        {'n', "\u0075"},
        {'o', "\u006F"},
        {'p', "\u0064"},
        {'q', "\u0062"},
        {'r', "\u0279"},
        {'s', "\u0073"},
        {'t', "\u0287"},
        {'u', "\u006E"},
        {'v', "\u028C"},
        {'w', "\u028D"},
        {'x', "\u0078"},
        {'y', "\u028E"},
        {'z', "\u007A"}
    };

    std::map<char, std::string> m_capitalChars{
        {'A', "\u2200"},
        {'B', "\u15FA"},
        {'C', "\u0186"},
        {'D', "\u15E1"},
        {'E', "\u018E"},
        {'F', "\u2132"},
        {'G', "\u2141"},
        {'H', "\u0048"},
        {'I', "\u0049"},
        {'J', "\u017F"},
        {'K', "\uA4D8"},
        {'L', "\u2142"},
        {'M', "\u0057"},
        {'N', "\u004E"},
        {'O', "\u004F"},
        {'P', "\u0500"},
        {'Q', "\u10E2"},
        {'R', "\u1D1A"},
        {'S', "\u0053"},
        {'T', "\u22A5"},
        {'U', "\u2229"},
        {'V', "\u039B"},
        {'W', "\u004D"},
        {'X', "\u0058"},
        {'Y', "\u2144"},
        {'Z', "\u007A"}
    };

    std::map<char, std::string> m_punctuation{
        {'&', "\u214B"},
        {'-', "\u203E"},
        {'?', "\u00BF"},
        {'!', "\u00A1"},
        {'"', "\u201E"},
        {'\'', "\u002C"},
        {'.', "\u02D9"},
        {',', "\u0027"},
        {';', "\u061B"}
    };

    std::map<unsigned short, std::string> m_numbers{
        {0, "\u0030"},
        {1, "\u21C2"},
        {2, "\u218A"},
        {3, "\u218B"},
        {4, "\u07C8"},
        {5, "\u03DA"},
        {6, "\u0039"},
        {7, "\u3125"},
        {8, "\u0038"},
        {9, "\u0036"}
    };
};

std::string TextMirror::reverseText(const std::string& text) const
{
    std::string tmp{};

    auto reverseIt = std::rbegin(text);
    while(reverseIt != std::rend(text)){
        tmp += *reverseIt;
        ++reverseIt;
    }

    return tmp;
}

std::string TextMirror::computeMirrorVersion(const std::string& text) const
{
    const std::string textReversed = reverseText(text);
    std::string mirrorVersion{};

    for(const auto& letter : textReversed) {
        if(std::isalpha(letter)) {
            auto it = (std::islower(letter)) ? m_lowerChars.find(letter) : m_capitalChars.find(letter);
            if(it != std::end(m_lowerChars)){
                mirrorVersion += it->second;
            } else {
                mirrorVersion += letter;
            }
        } else if(std::isdigit(letter)) {
            unsigned short number = static_cast<unsigned short>(std::stoi(std::string{letter}));
            auto it = m_numbers.find(number);
            if(it != std::end(m_numbers)){
                mirrorVersion += it->second;
            } else {
                mirrorVersion += letter;
            }
        } else if(std::ispunct(letter)) {
            auto it = m_punctuation.find(letter);
            if(it != std::end(m_punctuation)) {
                mirrorVersion += it->second;
            } else {
                mirrorVersion += letter;
            }
        } else {
            mirrorVersion += letter;
        }
    }

    return mirrorVersion;
}

}


int main()
{
    gx::TextMirror mirror{};

    const std::string text = "Hello World !\nHow are you today ?";
    const std::string reverseText = mirror.computeMirrorVersion(text);

    std::ofstream ofs{"C:/Users/Guit0x/Desktop/test.txt"};
    if(ofs){
        ofs << reverseText;
    }

    return 0;
}