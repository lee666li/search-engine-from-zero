#pragma once

#include <vector>
#include <string>
#include <memory>
#include "index/inverted_index.h"
#include "index/forward_index.h"
#include "rank/scorer.h"
#include "common/tokenizer.h"

namespace search_engine {

/**
 * @brief 搜索引擎主类
 * 
 * 整合索引、查询、排序等功能
 * 
 * 设计思路：
 * - 当前：简单的AND查询（所有词都必须匹配）
 * - 后续可扩展：
 *   - 布尔查询（AND/OR/NOT）
 *   - 短语查询
 *   - 模糊匹配
 *   - 向量检索（ANN）
 *   - 混合检索（倒排+向量）
 */
class SearchEngine {
public:
    SearchEngine();
    ~SearchEngine() = default;

    /**
     * @brief 设置排序器
     * @param scorer 排序器指针（SearchEngine会持有所有权）
     */
    void setScorer(std::unique_ptr<Scorer> scorer);

    /**
     * @brief 执行搜索
     * @param query 查询字符串
     * @param top_k 返回前K个结果
     * @return 搜索结果列表（按分数降序）
     */
    std::vector<SearchResult> search(const std::string& query, size_t top_k = 10) const;

    /**
     * @brief 设置倒排索引
     * @param index 倒排索引引用
     */
    void setInvertedIndex(InvertedIndex* index) { inverted_index_ = index; }

    /**
     * @brief 设置正排索引
     * @param index 正排索引引用
     */
    void setForwardIndex(ForwardIndex* index) { forward_index_ = index; }

private:
    /**
     * @brief 执行AND查询（所有词都必须匹配）
     * @param query_terms 查询词列表
     * @return 匹配的文档ID集合
     */
    std::vector<int64_t> executeAndQuery(const std::vector<std::string>& query_terms) const;

    InvertedIndex* inverted_index_ = nullptr;
    ForwardIndex* forward_index_ = nullptr;
    std::unique_ptr<Scorer> scorer_;
    Tokenizer tokenizer_;
};

} // namespace search_engine

