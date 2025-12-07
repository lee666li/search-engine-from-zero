#include "index/inverted_index.h"
#include <algorithm>

namespace search_engine {

void InvertedIndex::addDocument(int64_t doc_id, const std::vector<std::string>& tokens) {
    // 统计每个term在文档中的词频
    std::unordered_map<std::string, int32_t> term_freq;
    
    for (const auto& token : tokens) {
        if (!token.empty()) {
            term_freq[token]++;
        }
    }
    
    // 添加到倒排索引
    for (const auto& [term, freq] : term_freq) {
        index_[term].emplace_back(doc_id, freq);
    }
    
    // 更新文档计数（去重）
    if (doc_set_.find(doc_id) == doc_set_.end()) {
        doc_set_[doc_id] = true;
        total_docs_++;
    }
}

std::vector<Posting> InvertedIndex::search(const std::string& term) const {
    auto it = index_.find(term);
    if (it != index_.end()) {
        return it->second;
    }
    return {};
}

size_t InvertedIndex::getDocumentFrequency(const std::string& term) const {
    auto it = index_.find(term);
    if (it != index_.end()) {
        return it->second.size();
    }
    return 0;
}

void InvertedIndex::clear() {
    index_.clear();
    doc_set_.clear();
    total_docs_ = 0;
}

} // namespace search_engine

