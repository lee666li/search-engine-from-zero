#include "rank/scorer.h"
#include <algorithm>

namespace search_engine {

void Scorer::sortResults(std::vector<SearchResult>& results) const {
    std::sort(results.begin(), results.end());
}

double TfIdfScorer::score(int64_t doc_id,
                         const std::vector<std::string>& query_terms,
                         const InvertedIndex& inverted_index) const {
    double total_score = 0.0;
    size_t total_docs = inverted_index.getTotalDocuments();
    
    if (total_docs == 0) {
        return 0.0;
    }
    
    for (const auto& term : query_terms) {
        auto postings = inverted_index.search(term);
        
        // 找到该文档的posting
        for (const auto& posting : postings) {
            if (posting.doc_id == doc_id) {
                // 计算TF
                double tf = static_cast<double>(posting.term_freq);
                
                // 计算IDF
                size_t df = inverted_index.getDocumentFrequency(term);
                if (df > 0) {
                    double idf = std::log(static_cast<double>(total_docs) / df);
                    total_score += tf * idf;
                }
                break;
            }
        }
    }
    
    return total_score;
}

double SimpleScorer::score(int64_t doc_id,
                          const std::vector<std::string>& query_terms,
                          const InvertedIndex& inverted_index) const {
    int match_count = 0;
    
    for (const auto& term : query_terms) {
        auto postings = inverted_index.search(term);
        for (const auto& posting : postings) {
            if (posting.doc_id == doc_id) {
                match_count++;
                break;
            }
        }
    }
    
    return static_cast<double>(match_count);
}

} // namespace search_engine

