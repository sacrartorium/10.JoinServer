#include "create.hpp"

RequestCreate::RequestCreate() : BasicRequest("create") {}

Status RequestCreate::start(TableManagerPtr tableManager,
                            std::stringstream &stream) {
  auto name = getNextToken<std::string>(stream);

  return (name.empty()) ? Status({Status::StatusCode::WrongArgument, hint()})
                        : tableManager->createTable(name);
}

std::string RequestCreate::hint() { return "create <table name>"; }
