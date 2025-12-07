#include <iostream>
#include <iomanip>
#include "storage/index_builder.h"
#include "query/search_engine.h"
#include "index/forward_index.h"

using namespace search_engine;

void printSearchResults(const std::vector<SearchResult>& results, 
                       const ForwardIndex& forward_index) {
    if (results.empty()) {
        std::cout << "未找到相关文档\n" << std::endl;
        return;
    }
    
    std::cout << "找到 " << results.size() << " 个相关文档:\n" << std::endl;
    
    for (size_t i = 0; i < results.size(); ++i) {
        const auto& result = results[i];
        auto doc = forward_index.getDocument(result.doc_id);
        
        std::cout << "[" << (i + 1) << "] 文档ID: " << result.doc_id 
                  << " | 分数: " << std::fixed << std::setprecision(4) << result.score << std::endl;
        
        // 显示文档内容（截取前100个字符）
        std::string content = doc.content;
        if (content.length() > 100) {
            content = content.substr(0, 100) + "...";
        }
        std::cout << "    内容: " << content << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   基础搜索引擎 Demo (C++17)" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    // 1. 创建索引构建器
    IndexBuilder builder;
    
    // 2. 添加示例文档
    std::cout << "正在构建索引..." << std::endl;
    
    builder.addDocument(Document(1, "政采云 技术 团队 欢迎 你"));
    builder.addDocument(Document(2, "原创 干货 技术 氛围 很好"));
    builder.addDocument(Document(3, "搜索引擎 技术 实现 倒排索引"));
    builder.addDocument(Document(4, "C++ 编程 语言 高性能"));
    builder.addDocument(Document(5, "腾讯 WXG 搜索 团队 图片搜一搜"));
    builder.addDocument(Document(6, "AI 大模型 生成式 搜索"));
    builder.addDocument(Document(7, "向量检索 倒排索引 混合搜索"));
    builder.addDocument(Document(8, "技术 分享 学习 成长"));
    
    std::cout << "索引构建完成！" << std::endl;
    std::cout << "总文档数: " << builder.getForwardIndex().size() << std::endl;
    std::cout << "总词数: " << builder.getInvertedIndex().getTermCount() << std::endl;
    std::cout << std::endl;
    
    // 3. 创建搜索引擎
    SearchEngine engine;
    engine.setInvertedIndex(&builder.getInvertedIndex());
    engine.setForwardIndex(&builder.getForwardIndex());
    
    // 4. 执行搜索
    std::vector<std::string> test_queries = {
        "技术",
        "搜索",
        "技术 团队",
        "AI 大模型",
        "C++ 编程"
    };
    
    for (const auto& query : test_queries) {
        std::cout << "========================================" << std::endl;
        std::cout << "查询: \"" << query << "\"" << std::endl;
        std::cout << "========================================" << std::endl;
        
        auto results = engine.search(query, 5);
        printSearchResults(results, builder.getForwardIndex());
    }
    
    // 5. 交互式搜索
    std::cout << "\n========================================" << std::endl;
    std::cout << "进入交互式搜索模式 (输入 'quit' 退出)" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    std::string user_query;
    while (true) {
        std::cout << "请输入查询: ";
        std::getline(std::cin, user_query);
        
        if (user_query == "quit" || user_query == "exit" || user_query == "q") {
            break;
        }
        
        if (user_query.empty()) {
            continue;
        }
        
        auto results = engine.search(user_query, 5);
        printSearchResults(results, builder.getForwardIndex());
    }
    
    std::cout << "\n感谢使用！" << std::endl;
    return 0;
}

