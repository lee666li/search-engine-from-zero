#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>
#include "common/document.h"

namespace search_engine {

/**
 * @brief 正排索引
 * 
 * 存储文档ID到文档内容的映射
 * 
 * 设计思路：
 * - 当前：内存中的unordered_map实现
 * - 后续可扩展：
 *   - 支持文档元数据（时间、作者等）
 *   - 支持mmap持久化
 *   - 支持文档压缩存储
 */
class ForwardIndex {
public:
    ForwardIndex() = default;
    ~ForwardIndex() = default;

    /**
     * @brief 添加文档
     * @param doc 文档对象
     */
    void addDocument(const Document& doc);

    /**
     * @brief 根据文档ID获取文档
     * @param doc_id 文档ID
     * @return 文档对象（如果不存在返回空文档）
     */
    Document getDocument(int64_t doc_id) const;

    /**
     * @brief 检查文档是否存在
     * @param doc_id 文档ID
     * @return 是否存在
     */
    bool hasDocument(int64_t doc_id) const;

    /**
     * @brief 获取文档总数
     * @return 文档总数
     */
    size_t size() const { return index_.size(); }

    /**
     * @brief 清空索引
     */
    void clear();

private:
    // doc_id -> Document 映射
    std::unordered_map<int64_t, Document> index_;
};

} // namespace search_engine

