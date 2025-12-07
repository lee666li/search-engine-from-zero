#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "index/inverted_index.h"

namespace search_engine {

/**
 * @brief 搜索结果
 */
struct SearchResult {
    int64_t doc_id;      // 文档ID
    double score;        // 相关性分数
    std::string snippet; // 文档摘要（后续实现）
    
    SearchResult() : doc_id(-1), score(0.0) {}
    SearchResult(int64_t id, double s) : doc_id(id), score(s) {}
    
    // 用于排序
    bool operator<(const SearchResult& other) const {
        return score > other.score; // 降序排列
    }
};

/**
 * @brief 排序器基类
 * 
 * 设计思路：
 * - 当前实现：TF-IDF、简单词频统计
 * - 后续可扩展：BM25、学习排序（Learning to Rank）、向量相似度等
 */
class Scorer {
public:
    Scorer() = default;
    virtual ~Scorer() = default;

    /**
     * @brief 计算文档相关性分数
     * @param doc_id 文档ID
     * @param query_terms 查询词列表
     * @param inverted_index 倒排索引
     * @return 相关性分数
     */
    virtual double score(int64_t doc_id, 
                        const std::vector<std::string>& query_terms,
                        const InvertedIndex& inverted_index) const = 0;

    /**
     * @brief 对搜索结果进行排序
     * @param results 搜索结果列表
     */
    void sortResults(std::vector<SearchResult>& results) const;
};

/**
 * @brief TF-IDF排序器
 * 
 * TF-IDF = TF(term, doc) * IDF(term)
 * - TF: 词频（term在文档中的出现次数）
 * - IDF: 逆文档频率 log(N / DF)，N为总文档数，DF为包含该词的文档数
 */
class TfIdfScorer : public Scorer {
public:
    TfIdfScorer() = default;
    
    double score(int64_t doc_id,
                const std::vector<std::string>& query_terms,
                const InvertedIndex& inverted_index) const override;
};

/**
 * @brief 简单词频排序器（MVP版本）
 * 仅统计匹配的term数量
 */
class SimpleScorer : public Scorer {
public:
    SimpleScorer() = default;
    
    double score(int64_t doc_id,
                const std::vector<std::string>& query_terms,
                const InvertedIndex& inverted_index) const override;
};

} // namespace search_engine

