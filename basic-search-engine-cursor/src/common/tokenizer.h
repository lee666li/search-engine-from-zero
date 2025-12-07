#pragma once

#include <string>
#include <vector>
#include "common/document.h"

namespace search_engine {

/**
 * @brief 分词器接口
 * 负责将文档内容切分成token列表
 * 
 * 设计思路：
 * - 当前实现：基于空格分词（MVP版本）
 * - 后续可扩展：集成cppjieba、支持停用词、同义词等
 */
class Tokenizer {
public:
    Tokenizer() = default;
    virtual ~Tokenizer() = default;

    /**
     * @brief 对文档进行分词
     * @param doc 待分词的文档
     * @return token列表
     */
    virtual std::vector<std::string> tokenize(const Document& doc) const;

    /**
     * @brief 对文本进行分词
     * @param text 待分词的文本
     * @return token列表
     */
    virtual std::vector<std::string> tokenize(const std::string& text) const;

    /**
     * @brief 标准化token（转小写、去除标点等）
     * @param token 原始token
     * @return 标准化后的token
     */
    virtual std::string normalize(const std::string& token) const;

private:
    /**
     * @brief 基于空格分词（简单实现）
     * @param text 输入文本
     * @return token列表
     */
    std::vector<std::string> splitBySpace(const std::string& text) const;
};

} // namespace search_engine

