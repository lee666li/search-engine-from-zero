#include "index/forward_index.h"

namespace search_engine {

void ForwardIndex::addDocument(const Document& doc) {
    index_[doc.doc_id] = doc;
}

Document ForwardIndex::getDocument(int64_t doc_id) const {
    auto it = index_.find(doc_id);
    if (it != index_.end()) {
        return it->second;
    }
    return Document(); // 返回空文档
}

bool ForwardIndex::hasDocument(int64_t doc_id) const {
    return index_.find(doc_id) != index_.end();
}

void ForwardIndex::clear() {
    index_.clear();
}

} // namespace search_engine

