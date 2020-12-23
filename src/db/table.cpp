#include "table.hpp"

#include "status.hpp"

#include <algorithm>

Status Table::addRow(size_t id, std::string name) {
  LockGuard lock(m);

  if (mIndexMap.count(id)) {
    return Status(Status::StatusCode::DuplicateKey, {std::to_string(id)});
  }
  mRows.push_back(TableDataType(id, name));
  mIndexMap[id] = mRows.size() - 1;

  return Status::StatusCode::Ok;
}

Status Table::clear() {
  mRows.clear();
  mIndexMap.clear();

  return Status::StatusCode::Ok;
}

Status Table::intersection(TablePtr secondary) {
  LockGuard lock(m);
  LockGuard lockOther(secondary->m);

  std::vector<std::string> data;
  for (auto index : mIndexMap) {
    auto id = index.first;

    auto secondaryIndex = secondary->getIndex(id);
    if (secondaryIndex != -1) {
      data.push_back(std::to_string(id) + "," + mRows.at(index.second).name +
                     "," + secondary->mRows.at(secondaryIndex).name);
    }
  }

  return Status(Status::StatusCode::Ok, data);
}

Status Table::symmetricDifference(TablePtr secondary) {
  LockGuard lock(m);
  LockGuard lockOther(secondary->m);

  std::vector<std::string> data;

  auto iteratorPrimary = mIndexMap.cbegin();
  auto endPrimary = mIndexMap.cend();
  auto iteratorSecondary = secondary->mIndexMap.cbegin();
  auto endSecondary = secondary->mIndexMap.cend();

  while ((iteratorPrimary != endPrimary) &&
         (iteratorSecondary != endSecondary)) {
    if (iteratorPrimary->first == iteratorSecondary->first) {
      iteratorPrimary++;
      iteratorSecondary++;
    } else if (iteratorPrimary->first < iteratorSecondary->first) {
      data.push_back(std::to_string(iteratorPrimary->first) + "," +
                     mRows.at(iteratorPrimary->second).name + ",");
      iteratorPrimary++;
    } else {
      data.push_back(std::to_string(iteratorSecondary->first) + ",," +
                     secondary->mRows.at(iteratorSecondary->second).name);
      iteratorSecondary++;
    }
  }

  if (iteratorPrimary != endPrimary) {
    std::for_each(iteratorPrimary, endPrimary, [&data, this](auto index) {
      data.push_back(std::to_string(index.first) + "," +
                     mRows.at(index.second).name + ",");
    });
  } else {
    std::for_each(iteratorSecondary, endSecondary,
                  [&data, secondary](auto index) {
                    data.push_back(std::to_string(index.first) + ",," +
                                   secondary->mRows.at(index.second).name);
                  });
  }

  return Status(Status::StatusCode::Ok, data);
}

int64_t Table::getIndex(size_t id) {
  return (mIndexMap.count(id)) ? (mIndexMap.at(id)) : -1;
}
