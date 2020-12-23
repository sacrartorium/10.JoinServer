#include "table_manager.hpp"

Status TableManager::createTable(std::string name) {
  if (mTables.count(name)) {
    return Status::StatusCode::TableAlreadyExists;
  }

  mTables[name] = std::make_shared<Table>();

  return Status::StatusCode::Ok;
}

TablePtr TableManager::getTableByName(std::string name) {
  return (!mTables.count(name)) ? nullptr : mTables[name];
}

Status TableManager::insert(std::string name, size_t id, std::string value) {
  auto table = getTableByName(name);

  return (!table) ? Status::StatusCode::TableNotExists
                  : table->addRow(id, value);
}

Status TableManager::truncate(std::string name) {
  auto table = getTableByName(name);

  return (!table) ? Status::StatusCode::TableNotExists : table->clear();
}
