#include "truncate.hpp"

RequestTruncate::RequestTruncate() : BasicRequest("truncate") {}

Status RequestTruncate::start(TableManagerPtr tableManager,
                              std::stringstream &stream) {
  auto tablename = getNextToken<std::string>(stream);

  if (tablename.empty()) {
    return {Status::StatusCode::WrongArgument, hint()};
  }

  TablePtr table = tableManager->getTableByName(tablename);

  if (!table) {
    return {Status::StatusCode::TableNotExists, {tablename}};
  }

  return table->clear();
}

std::string RequestTruncate::hint() { return "truncate <table name>"; }
