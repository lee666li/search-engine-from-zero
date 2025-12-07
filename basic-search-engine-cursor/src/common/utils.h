#pragma once

#include <string>
#include <vector>

namespace search_engine {

/**
 * @brief 工具函数集合
 */
namespace utils {

/**
 * @brief 读取文件内容
 * @param filepath 文件路径
 * @return 文件内容
 */
std::string readFile(const std::string& filepath);

/**
 * @brief 分割字符串
 * @param str 输入字符串
 * @param delimiter 分隔符
 * @return 分割后的字符串列表
 */
std::vector<std::string> split(const std::string& str, char delimiter);

} // namespace utils

} // namespace search_engine

