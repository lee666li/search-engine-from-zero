#include "query/search_engine.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

namespace search_engine {

SearchEngine::SearchEngine() {
    // 默认使用TF-IDF排序器
    scorer_ = std::make_unique<TfIdfScorer>();
}

void SearchEngine::setScorer(std::unique_ptr<Scorer> scorer) {
    scorer_ = std::move(scorer);
}

std::vector<SearchResult> SearchEngine::search(const std::string& query, size_t top_k) const {
    if (!inverted_index_ || !scorer_) {
        return {};
    }
    
    // 1. 分词
    auto query_terms = tokenizer_.tokenize(query);
    if (query_terms.empty()) {
        return {};
    }
    
    // 2. 执行查询（当前实现：AND查询）
    auto doc_ids = executeAndQuery(query_terms);
    if (doc_ids.empty()) {
        return {};
    }
    
    // 3. 计算分数并排序
    std::vector<SearchResult> results;
    for (int64_t doc_id : doc_ids) {
        double score = scorer_->score(doc_id, query_terms, *inverted_index_);
        results.emplace_back(doc_id, score);
    }
    
    scorer_->sortResults(results);
    
    // 4. 返回top_k
    if (results.size() > top_k) {
        results.resize(top_k);
    }
    
    return results;
}

std::vector<int64_t> SearchEngine::executeAndQuery(const std::vector<std::string>& query_terms) const {
    if (query_terms.empty()) {
        return {};
    }
    
    // 获取每个term的posting list
    std::vector<std::vector<Posting>> posting_lists;
    for (const auto& term : query_terms) {
        auto postings = inverted_index_->search(term);
        if (postings.empty()) {
            // 如果某个term没有匹配，AND查询返回空
            return {};
        }
        posting_lists.push_back(postings);
    }
    
    // 找到所有term都包含的文档（交集）
    // 使用第一个term的posting list作为基准
    std::unordered_set<int64_t> candidate_docs;
    for (const auto& posting : posting_lists[0]) {
        candidate_docs.insert(posting.doc_id);
    }
    
    // 与其他term的posting list求交集
    for (size_t i = 1; i < posting_lists.size(); ++i) {
        std::unordered_set<int64_t> term_docs;
        for (const auto& posting : posting_lists[i]) {
            term_docs.insert(posting.doc_id);
        }
        
        // 求交集
        std::vector<int64_t> intersection;
        for (int64_t doc_id : candidate_docs) {
            if (term_docs.find(doc_id) != term_docs.end()) {
                intersection.push_back(doc_id);
            }
        }
        candidate_docs = std::unordered_set<int64_t>(intersection.begin(), intersection.end());
    }
    
    return std::vector<int64_t>(candidate_docs.begin(), candidate_docs.end());
}

} // namespace search_engine

