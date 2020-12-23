#pragma once

#include "basic_request.hpp"

struct RequestInsert : public BasicRequest {
  RequestInsert();

private:
  Status start(TableManagerPtr tableManager,
               std::stringstream &stream) override;
  std::string hint() override;
};
