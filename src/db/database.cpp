#include "database.hpp"

DataBase::DataBase(TableManagerPtr tableManager) : mTableManager(tableManager) {
  create<RequestCreate>();
  create<RequestInsert>();
  create<RequestIntersection>();
  create<RequestSymmetricDifference>();
  create<RequestTruncate>();
}

DataBase::~DataBase() { mRequests.clear(); }

template <typename T> void DataBase::create() {
  BasicRequestPtr request = std::make_shared<T>();
  mRequests[request->getRequestName()] = request;
}

std::string DataBase::request(std::string request) {
  LockGuard lock(m);

  if (request.back() != '\n')
    request.push_back('\n');

  std::stringstream streamRequest(request);

  std::string command = getNextToken<std::string>(streamRequest);

  if (mRequests.count(command) == 0)
    return Status::error("Command '" + command + "' not found!");
  else
    return mRequests[command]->start(mTableManager, streamRequest).stringify();
}
