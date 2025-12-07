cmake_minimum_required(VERSION 3.15)
project(BasicSearchEngine VERSION 1.0.0 LANGUAGES CXX)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/src)

# 源文件
set(COMMON_SOURCES
    src/common/document.cpp
    src/common/tokenizer.cpp
    src/common/utils.cpp
)

set(INDEX_SOURCES
    src/index/inverted_index.cpp
    src/index/forward_index.cpp
)

set(QUERY_SOURCES
    src/query/search_engine.cpp
)

set(RANK_SOURCES
    src/rank/scorer.cpp
)

set(STORAGE_SOURCES
    src/storage/index_builder.cpp
)

# 创建库
add_library(search_common STATIC ${COMMON_SOURCES})
add_library(search_index STATIC ${INDEX_SOURCES})
add_library(search_query STATIC ${QUERY_SOURCES})
add_library(search_rank STATIC ${RANK_SOURCES})
add_library(search_storage STATIC ${STORAGE_SOURCES})

# 链接依赖
target_link_libraries(search_index search_common)
target_link_libraries(search_query search_index search_common)
target_link_libraries(search_rank search_index search_common)
target_link_libraries(search_storage search_index search_common)

# 主程序
add_executable(search_demo src/main.cpp)
target_link_libraries(search_demo 
    search_query 
    search_rank 
    search_storage 
    search_index 
    search_common
)

# 测试程序（后续添加）
# add_executable(search_test tests/test_main.cpp)
# target_link_libraries(search_test search_query search_rank search_storage search_index search_common)

