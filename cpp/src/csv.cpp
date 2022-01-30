#include "csv.hpp"
#include "util.hpp"
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::vector<std::string>> Parser::parseCSV(std::string filename) {
  std::ifstream input{filename};

  if (!input.is_open()) {
    die("Couldn't read file");
  }

  std::vector<std::vector<std::string>> csvRows;

  for (std::string line; std::getline(input, line);) {
    std::istringstream ss(std::move(line));
    std::vector<std::string> row;
    if (!csvRows.empty()) {
      row.reserve(csvRows.front().size());
    }
    for (std::string value; std::getline(ss, value, ',');) {
      row.push_back(std::move(value));
    }
    csvRows.push_back(std::move(row));
  }

  return csvRows;
}

std::vector<std::vector<double>>
Parser::parseInt(std::vector<std::vector<std::string>> parsed_string) {
  std::vector<std::vector<double>> data;

  for (const auto &row : parsed_string) {
    std::vector<double> line;

    for (auto &s : row) {
      std::stringstream parser(s);
      double x = 0.0;
      parser >> x;

      line.push_back(x);
    }
    data.push_back(line);
  }
  return data;
}

Parser::Parser(std::string filename) {
  Parser::filename = filename;
  auto parsed_string = Parser::parseCSV(filename);
  Parser::data = parseInt(parsed_string);
}

Parser::~Parser() {}
