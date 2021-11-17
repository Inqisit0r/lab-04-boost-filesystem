// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_BROKERRESEARCH_HPP_
#define INCLUDE_BROKERRESEARCH_HPP_

#include <boost/filesystem.hpp>
#include <iostream>
#include <regex>
#include <iomanip>
#include <string>
#include <vector>

#define BOOST_PATH boost::filesystem::path

struct broker {
  std::string broker;
  std::string account;
  size_t files;
  size_t lastDate;
};

auto example() -> void;

void broker_research(BOOST_PATH& path);

void formatPrint(std::vector<broker>& brokerList);

#endif // INCLUDE_BROKERRESEARCH_HPP_
