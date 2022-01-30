/* See LICENSE file for copyright and license details. */

#ifndef FRANKNET_CSV_HPP_
#define FRANKNET_CSV_HPP_

#include <sstream>
#include <vector>

class Parser {
private:
  std::vector<std::vector<std::string> > parseCSV(std::string filename);
  std::vector<std::vector<double> > parseInt(std::vector<std::vector<std::string> >);

public:
  Parser(std::string);
  virtual ~Parser();
  std::string filename;
  std::vector<std::vector<double> > data;
};

#endif // FRANKNET_CSV_HPP_
