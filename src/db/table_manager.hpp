#pragma once

#include "table.hpp"

struct TableManager {
  /**
   Создать новую таблицу.
   @param name - Имя таблицы.
   @return Результат выполнения.
   */
  Status createTable(std::string name);

  /**
   Получить указатель на таблицу по её имени.
   @param name - Имя таблицы.
   @return Указатель на таблицу.
   */
  TablePtr getTableByName(std::string name);

protected:
  /**
   Вставить элемент.
   @param name - Имя таблицы.
   @param id - id элемента.
   @param value - Значение.
   @return Результат выполнения.
   */
  Status insert(std::string name, size_t id, std::string value);

  /**
   Очистить таблицу.
   @param name - имя таблицы
   @return Результат выполнения.
   */
  Status truncate(std::string name);

private:
  std::unordered_map<std::string, TablePtr> mTables;
};

using TableManagerPtr = std::shared_ptr<TableManager>;
