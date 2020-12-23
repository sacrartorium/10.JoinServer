#include "insert.hpp"

RequestInsert::RequestInsert() : BasicRequest("insert") {}

Status RequestInsert::start(TableManagerPtr tableManager,
                            std::stringstream &stream) {
  auto tableName = getNextToken<std::string>(stream);

  if (tableName.empty()) {
    return {Status::StatusCode::WrongArgument, hint()};
  }

  TablePtr table = tableManager->getTableByName(tableName);
  if (!table) {
    return Status::StatusCode::TableNotExists;
  }

  auto id = getNextToken<size_t>(stream);

  if (stream.bad()) {
    return {Status::StatusCode::WrongArgument, hint()};
  }

  auto name = getNextToken<std::string>(stream);

  if (name.empty()) {
    return {Status::StatusCode::WrongArgument, hint()};
  }

  return table->addRow(id, name);
}

std::string RequestInsert::hint() { return "insert <table name> <id> <value>"; }
