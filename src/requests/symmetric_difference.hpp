#pragma once

#include "basic_request.hpp"

struct RequestSymmetricDifference : public BasicRequest {
  RequestSymmetricDifference();

private:
  Status start(TableManagerPtr tableManager,
               std::stringstream &stream) override;
  std::string hint() override;
};
