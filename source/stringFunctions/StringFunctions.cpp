#include "stringFunctions/StringFunctions.h"


bool StrFunc::isEmpty(const std::string str) {
    auto it = str.begin();
    for (; it != str.end(); it++) {
        if (*it != ' ' && *it != '\n') return false;
    }
    return true;
}


void StrFunc::clearStartSpaces(std::string &command) {
    auto it = command.begin();
    while (*it == ' ') it++;
    command.replace(command.begin(), it, "");
}

void StrFunc::clearEndSpaces(std::string &command) {
    auto it = command.end() - 1;
    while (*it == ' ') it--;
    it++;
    command.replace(it, command.end(), "");
}

void StrFunc::clearSpacesBoth(std::string &command) {
    clearEndSpaces(command);
    clearStartSpaces(command);
}

std::string StrFunc::getWordByPos(const std::string &command, int pos) {
    std::string com = command;
    std::string posWord;
    clearStartSpaces(com);
    auto it = com.begin();

    for (int i = 0; i < pos; i++) {
        std::string temp = "";
        char quote = 0;
        if (*it == '\"') quote = '\"';
        else if (*it == '\'') quote = '\'';
        if (quote != 0) temp = getWordWithQuotes(com, quote);
        if (!isEmpty(temp)) {
            com.replace(com.begin(), com.begin() + temp.size() + 2, "");
            clearStartSpaces(com);
        }
        else {
            while (it != com.end() && *it != ' ') it++;
            com.replace(com.begin(), com.end(), it, com.end());
            clearStartSpaces(com);
            it = com.begin();
        }
    }

    while (it != com.end() && *it != ' ' ) {
        std::string temp = "";
        char quote = 0;
        if (*it == '\"') quote = '\"';
        else if (*it == '\'') quote = '\'';
        if (quote != 0) temp = getWordWithQuotes(com, quote);
        if (!isEmpty(temp)) {
            clearSpacesBoth(temp);
            return temp;
        }
        else {
            posWord.push_back(*it);
            it++;
        }
    }
    return posWord;
}

std::string StrFunc::getWordWithQuotes(const std::string &command, char quote) {
    auto it = command.begin();
    while (*it != quote && *it != 0) it++;
    if (it == command.end()) return std::string("");
    auto it2 = it + 1;
    while (*it2 != quote && *it2 != 0) it2++;
    if (it2 != command.end()) return std::string(it + 1, it2);
    else return std::string("");
}

std::string StrFunc::randWord(size_t minLen, size_t maxLen) {
    int len = rand() % (maxLen - minLen) + minLen;
    std::string str = "";
    size_t i = 0;
    if (rand() % 2 == 0 && len != 0) {
        str.push_back('A' + rand() % 26);
        i++;
    }
    for (; i < len; i++) {
        str.push_back('a' + rand() % 26);
    }
    return str;
}

std::string StrFunc::randPhrase(size_t minWordAmount, size_t maxWordAmount, size_t minWordLen, size_t maxWordLen,
                                size_t maxFullLen) {
    return std::string();
}



