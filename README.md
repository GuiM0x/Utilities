# Utilities

##### Classes

- Matrix
- Date

##### Tools (all functions)

```cpp
std::string textFileToString(const std::string& filePath);
std::string& textFileToString(const std::string& filePath, std::string& str);
std::string& stringToLower(std::string& str);
std::string& erasePunctuation(std::string& str);
std::ostream& allOccurInString(std::ostream& os, std::string str, const bool& caseSensitive = true);
std::ostream& allOccurInTextFile(std::ostream& os, const std::string& filePath, const bool& caseSensitive = true);
int rollTheDice(int valmin, int valmax);
```
