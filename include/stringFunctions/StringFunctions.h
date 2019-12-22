#ifndef TASK_MANAGER_STRINGFUNCTIONS_H
#define TASK_MANAGER_STRINGFUNCTIONS_H

#include <iostream>
#include <string>

class StrFunc {
private:

public:
    static bool isEmpty(const std::string str);
    static void clearStartSpaces(std::string &command);
    static void clearEndSpaces(std::string &command);
    static void clearSpacesBoth(std::string &command);
    static void deleteFirstWord(std::string &command);
    static std::string getWordByPos(const std::string &command, int pos);
    static std::string getWordWithQuotes(const std::string &command, char quote = '\"');
    static std::string randWord(size_t minLen, size_t maxLen);
};


#endif //TASK_MANAGER_STRINGFUNCTIONS_H
