#pragma once

#include "basic_request.hpp"

struct RequestIntersection : public BasicRequest {
  RequestIntersection();

private:
  Status start(TableManagerPtr tableManager,
               std::stringstream &stream) override;
  std::string hint() override;
};
