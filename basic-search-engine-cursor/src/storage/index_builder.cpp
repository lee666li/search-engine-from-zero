#include "storage/index_builder.h"
#include "common/utils.h"
#include <algorithm>

namespace search_engine {

IndexBuilder::IndexBuilder() : next_doc_id_(1) {
}

void IndexBuilder::addDocument(const Document& doc) {
    buildIndex(doc);
}

void IndexBuilder::addDocuments(const std::vector<Document>& docs) {
    for (const auto& doc : docs) {
        buildIndex(doc);
    }
}

bool IndexBuilder::loadFromFile(const std::string& filepath, int64_t doc_id) {
    std::string content = utils::readFile(filepath);
    if (content.empty()) {
        return false;
    }
    
    if (doc_id == -1) {
        doc_id = next_doc_id_++;
    }
    
    Document doc(doc_id, content);
    buildIndex(doc);
    
    return true;
}

void IndexBuilder::buildIndex(const Document& doc) {
    // 1. 分词
    auto tokens = tokenizer_.tokenize(doc);
    
    // 2. 创建文档副本并保存tokens
    Document doc_with_tokens = doc;
    doc_with_tokens.tokens = tokens;
    
    // 3. 添加到正排索引
    forward_index_.addDocument(doc_with_tokens);
    
    // 4. 添加到倒排索引
    inverted_index_.addDocument(doc.doc_id, tokens);
}

void IndexBuilder::clear() {
    inverted_index_.clear();
    forward_index_.clear();
    next_doc_id_ = 1;
}

} // namespace search_engine

