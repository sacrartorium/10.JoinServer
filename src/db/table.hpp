#pragma once

#include "status.hpp"

#include <map>
#include <memory>
#include <mutex>
#include <unordered_map>

struct Table {
  using LockGuard = std::lock_guard<std::mutex>;
  using TablePtr = std::shared_ptr<Table>;

  /**
   Структура по заданию.
   */
  struct TableDataType {
    TableDataType(size_t id, std::string name) : id(id), name(name){};
    size_t id;
    std::string name;
  };

  /**
   Добавить запись в таблицу.
   @return Результат выполнения операции.
   */
  Status addRow(size_t id, std::string name);

  /**
   Очистить таблицу.
   @return Результат выполнения операции.
   */
  Status clear();

  /**
   Пересечение таблиц.
   @return Результат выполнения операции.
   */
  Status intersection(TablePtr secondary);

  /**
   Симметрическая разность.
   @return Результат выполнения операции.
   */
  Status symmetricDifference(TablePtr secondary);

protected:
  /**
   Вернуть индекс записи по заданному id. И -1, если нет.
   @param id - id записи.
   @return - индекс.
   */
  int64_t getIndex(size_t id);

private:
  std::mutex m;

  std::vector<TableDataType> mRows;
  std::map<size_t, size_t> mIndexMap;
};

using TablePtr = std::shared_ptr<Table>;
