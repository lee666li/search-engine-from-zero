#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>

namespace search_engine {

/**
 * @brief Posting（倒排列表项）
 * 存储文档ID和该词在文档中的出现次数（TF）
 */
struct Posting {
    int64_t doc_id;      // 文档ID
    int32_t term_freq;   // 词频（Term Frequency）
    
    Posting(int64_t id, int32_t tf) : doc_id(id), term_freq(tf) {}
};

/**
 * @brief 倒排索引
 * 
 * 核心数据结构：
 * - term -> vector<Posting> 映射
 * 
 * 设计思路：
 * - 当前：内存中的unordered_map实现（MVP）
 * - 后续可扩展：
 *   - 支持按doc_id排序的posting list
 *   - 支持压缩存储（Delta编码、Varint）
 *   - 支持mmap持久化
 *   - 支持分片（Sharding）
 */
class InvertedIndex {
public:
    InvertedIndex() = default;
    ~InvertedIndex() = default;

    /**
     * @brief 添加文档到倒排索引
     * @param doc_id 文档ID
     * @param tokens 文档的token列表
     */
    void addDocument(int64_t doc_id, const std::vector<std::string>& tokens);

    /**
     * @brief 查询term对应的文档列表
     * @param term 查询词
     * @return posting列表（文档ID和词频）
     */
    std::vector<Posting> search(const std::string& term) const;

    /**
     * @brief 获取term的文档频率（DF）
     * @param term 查询词
     * @return 包含该词的文档数量
     */
    size_t getDocumentFrequency(const std::string& term) const;

    /**
     * @brief 获取索引中的总文档数
     * @return 文档总数
     */
    size_t getTotalDocuments() const { return total_docs_; }

    /**
     * @brief 清空索引
     */
    void clear();

    /**
     * @brief 获取索引统计信息
     */
    size_t getTermCount() const { return index_.size(); }

private:
    // term -> posting list 映射
    std::unordered_map<std::string, std::vector<Posting>> index_;
    
    // 总文档数（用于计算IDF）
    size_t total_docs_ = 0;
    
    // 文档集合（用于去重）
    std::unordered_map<int64_t, bool> doc_set_;
};

} // namespace search_engine

