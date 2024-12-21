#include <string>
#include <cctype>
#include <stack>
#include <stdexcept>
#include <cmath>

// 判断表达式是否合法
bool isValidExpression(const std::string& expr) {
    int balance = 0;  // 用来检查括号的平衡
    bool lastWasOperator = true;  // 用来检查运算符是否合法
    bool lastWasLeftParen = false;  // 用来检查左括号位置是否合法
    bool hasDigit = false;  // 用来检查是否出现过数字
    bool hasOperator = false;  // 用来检查是否出现过运算符
    bool hasDecimalPoint = false; // 用来标识是否已经遇到过小数点

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        // 跳过空格
        if (isspace(c)) {
            continue;
        }

        // 1. 如果是数字
        if (isdigit(c)) {
            lastWasOperator = false;  // 紧跟数字后不能是运算符
            hasDigit = true;
            hasDecimalPoint = false;  // 重置小数点标志
        }
        // 2. 如果是小数点
        else if (c == '.') {
            if (lastWasOperator || hasDecimalPoint || i == 0 || !isdigit(expr[i - 1]) || i == expr.size() - 1 || !isdigit(expr[i + 1])) {
                return false;  // 小数点不合法，必须紧接数字，且不能重复出现
            }
            hasDecimalPoint = true;
        }
        // 3. 如果是运算符
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (lastWasOperator || i == 0 || i == expr.size() - 1 || expr[i + 1] == ')') {
                return false; // 运算符不合法（连续运算符，或出现在开头结尾等）
            }
            lastWasOperator = true;
            hasOperator = true;
        }
        // 4. 如果是左括号
        else if (c == '(') {
            if (i != 0 && (isdigit(expr[i - 1]) || expr[i - 1] == ')')) {
                return false;  // 左括号前面不能是数字或右括号
            }
            balance++;
            lastWasLeftParen = true;
            lastWasOperator = true;  // 左括号前可以有运算符，如3 + (2 * 5)
        }
        // 5. 如果是右括号
        else if (c == ')') {
            if (lastWasOperator || balance == 0) {
                return false;  // 右括号前不能是运算符，且括号必须匹配
            }
            balance--;
            lastWasLeftParen = false;
        }
        // 6. 科学计数法支持
        else if (c == 'e' || c == 'E') {
            // 科学计数法（e或E）要求前面是数字，后面是可选的符号和数字
            if (!hasDigit || i == expr.size() - 1 || !isdigit(expr[i + 1])) {
                return false;
            }
            // 处理科学计数法符号后可能出现的+或-
            if (i + 1 < expr.size() && (expr[i + 1] == '+' || expr[i + 1] == '-')) {
                i++;  // 跳过符号
            }
        }
        // 7. 如果是非法字符
        else {
            return false;  // 非法字符
        }
    }

    // 最后检查是否有未关闭的括号，并且有数字和运算符
    return balance == 0 && hasDigit && hasOperator && !lastWasOperator; // 末尾不能是运算符
}

// 优先级映射
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 计算两数运算
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw std::invalid_argument("ILLEGAL");
            return a / b;
        default: return 0;
    }
}

// 计算表达式
double evaluateExpression(const std::string& expr) {
    std::stack<double> values;  // 用于存储操作数
    std::stack<char> ops;  // 用于存储运算符

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        // 跳过空格
        if (isspace(c)) continue;

        // 如果是数字，读取数字并加入值栈
        if (isdigit(c) || c == '.') {
            std::string numStr;
            bool hasExponent = false;  // 是否遇到科学计数法的指数部分
            bool hasDot = false;  // 是否遇到小数点

            // 处理数字部分，直到遇到非数字字符或非有效的小数点
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'e' || expr[i] == 'E')) {
                if (expr[i] == '.' && !hasDot) {
                    hasDot = true;
                    numStr.push_back(expr[i]);
                }
                else if ((expr[i] == 'e' || expr[i] == 'E') && !hasExponent) {
                    // 处理科学计数法符号
                    hasExponent = true;
                    numStr.push_back(expr[i]);
                }
                else if (isdigit(expr[i])) {
                    numStr.push_back(expr[i]);
                }
                else {
                    throw std::invalid_argument("ILLEGAL");  // 遇到不合法的字符
                }
                i++;
            }
            i--;  // 调整回到最后一个数字
            values.push(stod(numStr)); // stod: 将字符串转换为 double 类型
        }
        // 如果是左括号，直接入栈
        else if (c == '(') {
            ops.push(c);
        }
        // 如果是右括号，计算直到遇到左括号
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.pop();  // 弹出左括号
        }
        // 如果是运算符，处理运算符栈
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(c)) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(c);
        }
    }

    // 处理栈中剩余的运算符
    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperation(val1, val2, op));
    }

    return values.top();  // 返回最终计算结果
}