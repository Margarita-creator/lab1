//Copyright 2021 user31

#include "Student.hpp"

#include <iomanip>
#include <sstream>
#include <utility>

Student::Student(std::string _name, std::any _group,
                 std::any _avg, std::any _debt) {
  name = std::move(_name);
  group = std::move(_group);
  avg = std::move(_avg);
  debt = std::move(_debt);
}
bool anyDate(std::any a1, std::any a2)
{
  if (a1.type() != a2.type())
    return false;
  if (a1.type() == typeid(std::string))
    return std::any_cast<std::string>(a1)== std::any_cast<std::string>(a2);
  if (a1.type() == typeid(nullptr))
    return true;
  if (a1.type() == typeid(double))
    return std::any_cast<double>(a1) == std::any_cast<double>(a2);
  if (a1.type() == typeid(size_t))
    return std::any_cast<size_t>(a1) == std::any_cast<size_t>(a2);
  if (a1.type() == typeid(std::vector<std::string>))
    return
        std::any_cast<std::vector<std::string>>(a1)
        == std::any_cast<std::vector<std::string>>(a2);
  return false;
}

bool Student::operator==(const Student& student) const
{
  bool n =  name == student.name;
  bool g = anyDate(group, student.group);
  bool a = anyDate(avg, student.avg);
  bool d = anyDate(debt, student.debt);
  return n && g && a && d;
}

Student::Student() = default;

std::string get_name(const json& j)  {
  return j.get<std::string>();
}

std::any get_debt(const json& j) {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string>>();
}

std::any get_avg(const json& j) {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

std::any get_group(const json& j) {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::size_t>();
}

void from_json(const json& j, Student& s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}


std::string toString(std::any& item)
{
  std::stringstream ss;
  int check = 0;
  if (item.type() == typeid(std::nullptr_t)){
    ss << "null";
    check = check + 1;
  }
  if (item.type() == typeid(std::string)){
    ss << std::any_cast<std::string>(item);
    check = check + 1;
  }
  if (item.type() == typeid(double)){
    ss << std::any_cast<double>(item);
    check = check + 1;
  }
  if (item.type() == typeid(std::vector<std::string>)){
    ss << std::any_cast<std::vector<std::string> >(item).size();
    check = check + 1;
  }
  if (item.type() == typeid(size_t)){
    ss << std::any_cast<size_t>(item);
    check = check + 1;
  }
  if (check == 0)
    ss << "error";
  return ss.str();
}

void print(std::string s1, std::string s2,
           std::string s3, std::string s4, std::ostream& os)
{
  os << "| " << std::setw(20) << std::left << s1 << "| "
     <<  std::setw(10) << std::left << s2 << "| "
     <<  std::setw(10) << std::left << s3 << "| "
     <<  std::setw(10) << std::left << s4 << "|\n"
     << "|---------------------|-----------|-----------|-----------|\n";
}

void print(Student& student, std::ostream& os)
{
  print(student.name, toString(student.group), toString(student.avg),
        toString(student.debt), os);
}


void print(std::vector<Student>& students, std::ostream& os)
{
  print("name", "group", "avg", "debt", os);
  for (Student& student : students) {
    print(student, os);
  }
}
