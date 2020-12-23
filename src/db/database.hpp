#pragma once

#include "../requests/create.hpp"
#include "../requests/insert.hpp"
#include "../requests/intersection.hpp"
#include "../requests/symmetric_difference.hpp"
#include "../requests/truncate.hpp"

#include <iostream>
#include <mutex>

struct DataBase {
  using LockGuard = std::lock_guard<std::mutex>;

  DataBase(TableManagerPtr tableManager);
  ~DataBase();

  std::string request(std::string strCommand);

private:
  template <typename T> void create();

  std::mutex m;
  TableManagerPtr mTableManager;
  std::unordered_map<std::string, BasicRequestPtr> mRequests;
};

using DataBasePtr = std::shared_ptr<DataBase>;
