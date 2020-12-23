#pragma once

#include <string>
#include <vector>

struct Status {

  enum class StatusCode {
    Ok,
    TableNotExists,
    TableAlreadyExists,
    DuplicateKey,
    WrongArgument,
  };

  /**
   Состояние выполнения запроса.
   */
  Status(StatusCode code);
  Status(StatusCode code, std::vector<std::string> data);
  Status(Status::StatusCode code, std::string hintMessage);
  /**
   Возвращает строку с результатом выполнения запроса.
   @return - Строка с результатом выполнения.
   */
  std::string stringify() const;
  static std::string error(std::string message);

private:
  std::string errorMsg(std::string message) const;

  StatusCode mCodeResult;
  std::vector<std::string> mData;
  std::string mHintMessage;
};
