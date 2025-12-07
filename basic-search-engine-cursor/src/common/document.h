#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace search_engine {

/**
 * @brief 文档结构体
 * 存储文档的基本信息：ID、内容、元数据
 */
struct Document {
    int64_t doc_id;              // 文档ID
    std::string content;          // 文档内容
    std::string title;            // 文档标题（可选）
    std::vector<std::string> tokens;  // 分词后的token列表
    
    Document() : doc_id(-1) {}
    Document(int64_t id, const std::string& text) 
        : doc_id(id), content(text) {}
};

} // namespace search_engine

