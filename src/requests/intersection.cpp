#include "intersection.hpp"

RequestIntersection::RequestIntersection() : BasicRequest("intersection") {}

Status RequestIntersection::start(TableManagerPtr tableManager,
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
  return tableA->intersection(tableB);
}

std::string RequestIntersection::hint() { return "intersection"; }
