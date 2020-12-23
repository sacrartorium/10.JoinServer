#include "status.hpp"

Status::Status(Status::StatusCode code)
    : mCodeResult(code), mData(), mHintMessage("") {}

Status::Status(Status::StatusCode code, std::vector<std::string> data)
    : mCodeResult(code), mData(data), mHintMessage("") {}

Status::Status(Status::StatusCode code, std::string hintMessage)
    : mCodeResult(code), mData(), mHintMessage(hintMessage) {}

std::string Status::error(std::string message) {
  return "ERR " + message + "\n";
}

std::string Status::errorMsg(std::string message) const {
  return error(message + ((!mHintMessage.empty()) ? "\n" + mHintMessage : ""));
}

std::string Status::stringify() const {
  switch (mCodeResult) {
  case (StatusCode::Ok): {
    std::string result = "";

    if (!mData.empty())
      for (auto &data : mData) {
        result += data;
        result += "\n";
      }

    result += "OK\n";
    return result;
    break;
  }

  case (StatusCode::WrongArgument): {
    return errorMsg("Wrong arguments.");
    break;
  }
  case (StatusCode::TableAlreadyExists): {
    return error("Table already exists.");
    break;
  }
  case (StatusCode::TableNotExists): {
    return error("Unknown table.");
    break;
  }
  case (StatusCode::DuplicateKey): {
    return error("Duplicate key.");
    break;
  }
  default:
    return error("Unknown error.");
  }
}
