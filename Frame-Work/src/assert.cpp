#include "assert.h"
#include "logging.h"
#include <string>

namespace cs
{
    void assert_failed(const char* expression, const char* file, int line)
    {
        /*logger::log(std::string(std::string("Failed assertion:\nExpression: ") + 
        std::string(expression) + std::string("\nFile: ") + std::string(file) +
        std::string("\nLine: ") + std::to_string(line)).c_str()
        , L_CODE::C_ERROR_CONTINUE);
        */

        std::string str_expression = std::string("Expression: ") + std::string(expression);
        std::string str_file = std::string("File: ") + std::string(file);
        std::string str_line = std::string("Line: ") + std::to_string(line);

        logger::log("Failed Assertion: ", L_CODE::C_ERROR_CONTINUE);
        logger::log(str_expression.c_str(), L_CODE::C_ERROR_CONTINUE);
        logger::log(str_file.c_str(), L_CODE::C_ERROR_CONTINUE);
        logger::log(str_line.c_str(), L_CODE::C_ERROR);
    }
}