#include <iostream>
#include <string>
#include "expression_evaluator.h"

int main() {
    // 测试用例数组
    std::string testExpressions[] = {
        "5 + 3 * 2",          // 合法的表达式
        "1.2e3 + 5",          // 合法的带小数和科学计数法表达式
        "5 + ",               // 非法的表达式（缺少操作数）
        "(1 + 2",             // 非法的表达式（括号不匹配）
        "5 ++ 3",             // 非法的表达式（重复运算符）
        "10 / (2 + 3)",       // 合法的表达式（带括号）
        "*2.5 + 3.0 * 4",     // 合法的表达式（带负数）
        "2 / 0"               // 非法的表达式（除以零）
    };

    // 遍历每个表达式进行测试
    for (const auto& expr : testExpressions) {
        std::cout << "Testing expression: " << expr << std::endl;

        // 判断表达式是否合法
        if (isValidExpression(expr)) {
            try {
                // 计算并输出结果
                double result = evaluateExpression(expr);
                std::cout << "The result is: " << result << std::endl;
            } catch (const std::invalid_argument& e) {
                std::cout  << e.what() << std::endl;
            }
        } else {
            std::cout << "ILLEGAL" << std::endl;
        }

        std::cout << "-------------------------------------" << std::endl;
    }

    return 0;
}