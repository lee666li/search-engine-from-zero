#pragma once

#include <vector>
#include <string>
#include "index/inverted_index.h"
#include "index/forward_index.h"
#include "common/tokenizer.h"
#include "common/document.h"

namespace search_engine {

/**
 * @brief 索引构建器
 * 
 * 负责构建倒排索引和正排索引
 * 
 * 设计思路：
 * - 可扩展的pipeline设计
 * - 支持批量构建
 * - 后续可扩展：多线程构建、增量更新、持久化等
 */
class IndexBuilder {
public:
    IndexBuilder();
    ~IndexBuilder() = default;

    /**
     * @brief 添加文档到索引
     * @param doc 文档对象
     */
    void addDocument(const Document& doc);

    /**
     * @brief 批量添加文档
     * @param docs 文档列表
     */
    void addDocuments(const std::vector<Document>& docs);

    /**
     * @brief 从文件加载文档并构建索引
     * @param filepath 文件路径
     * @param doc_id 文档ID（如果为-1则自动分配）
     * @return 是否成功
     */
    bool loadFromFile(const std::string& filepath, int64_t doc_id = -1);

    /**
     * @brief 构建索引（对文档进行分词并添加到索引）
     * @param doc 文档对象
     */
    void buildIndex(const Document& doc);

    /**
     * @brief 获取倒排索引
     * @return 倒排索引引用
     */
    InvertedIndex& getInvertedIndex() { return inverted_index_; }

    /**
     * @brief 获取正排索引
     * @return 正排索引引用
     */
    ForwardIndex& getForwardIndex() { return forward_index_; }

    /**
     * @brief 清空所有索引
     */
    void clear();

private:
    InvertedIndex inverted_index_;
    ForwardIndex forward_index_;
    Tokenizer tokenizer_;
    int64_t next_doc_id_;  // 自动分配的文档ID
};

} // namespace search_engine

