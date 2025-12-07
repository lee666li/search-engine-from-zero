#include "common/tokenizer.h"
#include <sstream>
#include <algorithm>
#include <cctype>

namespace search_engine {

std::vector<std::string> Tokenizer::tokenize(const Document& doc) const {
    return tokenize(doc.content);
}

std::vector<std::string> Tokenizer::tokenize(const std::string& text) const {
    auto tokens = splitBySpace(text);
    
    // 标准化每个token
    for (auto& token : tokens) {
        token = normalize(token);
    }
    
    // 过滤空token
    tokens.erase(
        std::remove_if(tokens.begin(), tokens.end(),
            [](const std::string& t) { return t.empty(); }),
        tokens.end()
    );
    
    return tokens;
}

std::string Tokenizer::normalize(const std::string& token) const {
    std::string normalized = token;
    
    // 转小写
    std::transform(normalized.begin(), normalized.end(), 
                   normalized.begin(), ::tolower);
    
    // 去除首尾空白字符
    normalized.erase(0, normalized.find_first_not_of(" \t\n\r"));
    normalized.erase(normalized.find_last_not_of(" \t\n\r") + 1);
    
    // TODO: 后续可扩展
    // - 去除标点符号
    // - 处理数字
    // - 处理特殊字符
    
    return normalized;
}

std::vector<std::string> Tokenizer::splitBySpace(const std::string& text) const {
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

} // namespace search_engine

