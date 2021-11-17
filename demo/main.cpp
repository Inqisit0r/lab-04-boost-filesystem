#include "brokerResearch.hpp"

int main(int argc, char* argv[]) {
  BOOST_PATH path;
  if (argc > 1)
  {
    path = (BOOST_PATH)argv[1];
  } else {
    path = (BOOST_PATH)argv[0];
  }
  broker_research(path);
}