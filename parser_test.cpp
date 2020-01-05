// parser_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_string.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

#include <boost/phoenix/core.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/phoenix/operator.hpp>
#include <string>
#include <vector>

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace qi = boost::spirit::qi;

using boost::property_tree::ptree;

typedef std::string::const_iterator iterator_type;

struct employee_t
{
    int age;
    std::string name;
    std::string favorite;
};


BOOST_FUSION_ADAPT_STRUCT(
    employee_t,
    (int, age)
    (std::string, name)
    (std::string, favorite)
)

void testEmployee()
{
    std::string str = "$start_ employee 43 ycyang video-game employee 40 iris cooking employee 7 andy watchTV $end_";
    employee_t employee_test;
    std::vector<employee_t> employees_test;

    qi::rule< iterator_type, std::string(), qi::ascii::space_type> _string;    
    qi::rule< iterator_type, employee_t(), qi::ascii::space_type> _employee;
    qi::rule< iterator_type, employee_t(), qi::ascii::space_type> _node;
    qi::rule< iterator_type, std::vector<employee_t>(), qi::ascii::space_type> _employees;
    qi::rule< iterator_type, std::vector<employee_t>(), qi::ascii::space_type> _tabTest;

    BOOST_SPIRIT_DEBUG_NODE(_employees);
    
    _string = (qi::lexeme[+(qi::char_ - ' ')] - qi::lit("$start_") ) - qi::lit("$end_");
    _employee = qi::lit("employee") >> qi::int_ >> _string >> _string;
    _employees = qi::repeat[_employee];
    _tabTest = qi::lit("$start_") >> _employees >> qi::lit("$end_");
      
    bool success0 = qi::phrase_parse(str.begin(), str.end(), _tabTest, qi::ascii::space, employees_test);
}

int main()
{
        
    testEmployee();
    return 0;      
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
