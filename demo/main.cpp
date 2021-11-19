#include "iostream"
#include "Student.hpp"
#include <vector>


int main(int argc, char** argv)
{
  nlohmann::json data = takeJson(argc, argv);
  std::vector<Student> students = parsingJson(data);
  print(students, std::cout);
}

