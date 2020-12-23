#pragma once

#include "../db/status.hpp"
#include "../db/table_manager.hpp"
#include "../utilities.hpp"

struct BasicRequest {
  BasicRequest(std::string name) : mRequestName(name) {}

  virtual Status start(TableManagerPtr tableManager,
                       std::stringstream &stream) = 0;
  virtual std::string hint() = 0;

  std::string getRequestName() { return mRequestName; }

private:
  std::string mRequestName;
};
using BasicRequestPtr = std::shared_ptr<BasicRequest>;
