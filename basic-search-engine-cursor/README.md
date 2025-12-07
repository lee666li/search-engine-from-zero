# 🚀 Basic Search Engine - 从0到1的工程级搜索引擎

一个用 **C++17** 实现的完整搜索引擎项目，旨在训练项目能力、工程规范和可扩展性设计。

## 📋 项目概述

本项目是一个**工程级搜索引擎**的MVP实现，采用模块化设计，完全符合大厂搜索团队的代码规范。未来可扩展为支持向量检索、AI大模型、生成式搜索的完整系统。

### ✨ 核心特性

- ✅ **倒排索引（Inverted Index）** - 核心检索数据结构
- ✅ **正排索引（Forward Index）** - 文档内容存储
- ✅ **TF-IDF排序** - 相关性评分算法
- ✅ **分词器（Tokenizer）** - 可扩展的分词接口
- ✅ **AND查询** - 多词查询支持
- ✅ **模块化设计** - 清晰的目录结构和依赖关系

### 🎯 设计目标

1. **工程规范** - 符合大厂代码规范，模块化、可维护
2. **可扩展性** - 易于添加新功能（BM25、向量检索、AI等）
3. **性能优化** - 为后续优化预留接口（mmap、压缩、并发等）
4. **学习价值** - 完整实现搜索引擎核心流程

## 🏗️ 项目结构

```
basic-search-engine/
├── CMakeLists.txt          # CMake构建配置
├── README.md               # 项目文档
├── data/                   # 数据目录
├── build/                  # 编译输出目录
└── src/                    # 源代码目录
    ├── common/             # 公共模块
    │   ├── document.h/cpp  # 文档数据结构
    │   ├── tokenizer.h/cpp # 分词器
    │   └── utils.h/cpp    # 工具函数
    ├── index/              # 索引模块
    │   ├── inverted_index.h/cpp  # 倒排索引
    │   └── forward_index.h/cpp   # 正排索引
    ├── query/              # 查询模块
    │   └── search_engine.h/cpp   # 搜索引擎主类
    ├── rank/               # 排序模块
    │   └── scorer.h/cpp    # 排序器（TF-IDF、Simple）
    ├── storage/            # 存储模块
    │   └── index_builder.h/cpp   # 索引构建器
    └── main.cpp            # 主程序入口
```

## 🚀 快速开始

### 编译

```bash
# 创建构建目录
mkdir -p build && cd build

# 配置CMake
cmake ..

# 编译
make -j4

# 运行demo
./bin/search_demo
```

### 使用示例

```cpp
#include "storage/index_builder.h"
#include "query/search_engine.h"

using namespace search_engine;

// 1. 创建索引构建器
IndexBuilder builder;

// 2. 添加文档
builder.addDocument(Document(1, "政采云 技术 团队 欢迎 你"));
builder.addDocument(Document(2, "原创 干货 技术 氛围 很好"));

// 3. 创建搜索引擎
SearchEngine engine;
engine.setInvertedIndex(&builder.getInvertedIndex());
engine.setForwardIndex(&builder.getForwardIndex());

// 4. 执行搜索
auto results = engine.search("技术", 10);
```

## 📚 核心模块说明

### 1. 倒排索引（InvertedIndex）

**功能**：实现 `term -> [doc_id, term_freq]` 的映射

**设计思路**：
- 当前：内存中的 `unordered_map` 实现
- 后续可扩展：
  - Posting List 压缩（Delta编码、Varint）
  - 按 doc_id 排序的 posting list
  - mmap 持久化存储
  - 分片（Sharding）支持

### 2. 正排索引（ForwardIndex）

**功能**：存储 `doc_id -> Document` 的映射

**设计思路**：
- 当前：内存中的 `unordered_map` 实现
- 后续可扩展：
  - 文档元数据（时间、作者等）
  - 文档压缩存储
  - mmap 持久化

### 3. 分词器（Tokenizer）

**功能**：将文档内容切分成token列表

**设计思路**：
- 当前：基于空格分词（MVP版本）
- 后续可扩展：
  - 集成 cppjieba（中文分词）
  - 停用词过滤
  - 同义词扩展
  - 词性标注

### 4. 排序器（Scorer）

**功能**：计算文档相关性分数

**当前实现**：
- `TfIdfScorer` - TF-IDF算法
- `SimpleScorer` - 简单词频统计

**后续可扩展**：
- BM25排序
- 学习排序（Learning to Rank）
- 向量相似度排序
- 混合排序（倒排+向量）

### 5. 搜索引擎（SearchEngine）

**功能**：整合索引、查询、排序功能

**当前实现**：
- AND查询（所有词都必须匹配）

**后续可扩展**：
- 布尔查询（AND/OR/NOT）
- 短语查询
- 模糊匹配
- 向量检索（ANN）
- 混合检索（倒排+向量）

## 🔄 数据流程

```
文档输入
  ↓
IndexBuilder（索引构建器）
  ↓
Tokenizer（分词）
  ↓
InvertedIndex（倒排索引） + ForwardIndex（正排索引）
  ↓
SearchEngine（查询引擎）
  ↓
Query Parser（查询解析）→ InvertedIndex（检索）
  ↓
Scorer（排序器）计算分数
  ↓
搜索结果返回
```

## 🎯 后续扩展方向

### 阶段2：工程化搜索引擎（1-2周）

- [ ] 停用词（StopWords）过滤
- [ ] 同义词（Synonym）扩展
- [ ] QueryParser（布尔表达式）
- [ ] BM25排序器
- [ ] Posting List排序优化

### 阶段3：生产级搜索服务（2-4周）

- [ ] HTTP API服务（cpp-httplib / Oat++）
- [ ] 文档批量加载
- [ ] 多线程索引构建
- [ ] mmap Segment存储
- [ ] 倒排索引分片
- [ ] 内存布局优化

### 阶段4：向量检索（图搜方向）

- [ ] 向量索引（HNSW / IVF / PQ）
- [ ] Embedding集成
- [ ] 混合检索（倒排+向量）
- [ ] Faiss集成

### 阶段5：AI大模型集成（生成式搜索）

- [ ] Query Rewrite（LLM改写查询）
- [ ] Rerank（LLM重排序）
- [ ] 摘要生成
- [ ] 生成式搜索（GenSearch）

## 🛠️ 技术栈

- **语言**：C++17
- **构建系统**：CMake 3.15+
- **编译器**：GCC 10+ / Clang 10+

## 📝 代码规范

- 使用 `namespace search_engine` 命名空间
- 头文件使用 `#pragma once`
- 类和方法都有详细的Doxygen注释
- 遵循RAII原则
- 使用智能指针管理资源

## 🤝 贡献

这是一个学习项目，欢迎提出改进建议和扩展方向！

## 📄 许可证

本项目用于学习和训练目的。

---

**目标**：通过这个项目，掌握搜索引擎的核心原理，培养工程化思维，为未来加入腾讯WXG搜索团队（图片搜一搜）打下坚实基础！

