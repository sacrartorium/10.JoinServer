#pragma once

#include "basic_request.hpp"

struct RequestTruncate : public BasicRequest {
  RequestTruncate();

private:
  Status start(TableManagerPtr tableManager,
               std::stringstream &stream) override;
  std::string hint() override;
};
