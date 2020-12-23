#include "symmetric_difference.hpp"

RequestSymmetricDifference::RequestSymmetricDifference()
    : BasicRequest("symmetric_difference") {}

Status RequestSymmetricDifference::start(TableManagerPtr tableManager,
                                         std::stringstream &stream) {
  auto tableNameA = getNextToken<std::string>(stream);
  auto tableNameB = getNextToken<std::string>(stream);

  if (tableNameA == "")
    tableNameA = "A";
  if (tableNameB == "")
    tableNameB = "B";

  TablePtr tableA = tableManager->getTableByName(tableNameA);
  if (!tableA) {
    return {Status::StatusCode::TableNotExists, {tableNameA}};
  }

  TablePtr tableB = tableManager->getTableByName(tableNameB);
  if (!tableB) {
    return {Status::StatusCode::TableNotExists, {tableNameB}};
  }

  return tableA->symmetricDifference(tableB);
}

std::string RequestSymmetricDifference::hint() {
  return "symmetric_difference";
}
