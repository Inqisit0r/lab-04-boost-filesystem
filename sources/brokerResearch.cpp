// Copyright 2021 Your Name <your_email>
#include "brokerResearch.hpp"

auto example() -> void {
  throw std::runtime_error("not implemented");
}

void path_convert(const BOOST_PATH& path, std::cmatch* m)
{
  regex_search(path.c_str(), *m,
               std::regex("([a-z]+)/balance_([0-9]+)_([0-9]+).txt"));
}

void broker_insert(std::cmatch& m, std::vector<broker>& brokerList)
{
  bool checker = false;
  for (auto& iter : brokerList)
  {
    if (iter.broker == m[1])
    {
      iter.files++;
      if (std::stoi(m[3]) > static_cast<int>(iter.lastDate))
        iter.lastDate = std::stoi(m[3]);
      checker = true;
    }
  }
  if (!checker)
  {
    broker temp;
    temp.broker = m[1];
    temp.account = m[2];
    temp.lastDate = static_cast<size_t>(std::stoi(m[3]));
    temp.files = 1;
    brokerList.push_back(temp);
  }
}

void formatPrint(std::vector<broker>& brokerList)
{
  for (auto& iter : brokerList)
  {
    std::cout << "broker:"  << std::setw(10) << std::left << iter.broker   <<
                 "account:" << std::setw(8)  << std::left << iter.account  <<
                 "files:"   << std::setw(8)  << std::left << iter.files    <<
                 "data:"    << std::setw(8)  << std::left << iter.lastDate <<
                 std::endl;
  }
}

void broker_research(BOOST_PATH& path)
{
  std::vector<BOOST_PATH> pathList;
  std::vector<std::vector<BOOST_PATH>> balanceList;
  BOOST_PATH tempPath;

  //Записываем начальный список путей
  for (const boost::filesystem::directory_entry& x :
       boost::filesystem::directory_iterator{path})
  {
    if (is_directory(x))
    {
      pathList.push_back(x);
    }
  }

  std::cmatch m;
  std::vector<broker> brokerList;
  for (auto& element : pathList)
  {
    for (const boost::filesystem::directory_entry& x :
         boost::filesystem::directory_iterator{element})
    {
      if (is_directory(x))
      {
        pathList.push_back(x);
      } else if (boost::filesystem::is_regular_file(x)){
        path_convert(x.path(), &m);
        if (m[3] != "")
          broker_insert(m, brokerList);
      }
    }
  }
  formatPrint(brokerList);
}
