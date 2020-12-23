#pragma once

#include "basic_request.hpp"

struct RequestCreate : public BasicRequest {
  RequestCreate();

private:
  Status start(TableManagerPtr tableManager,
               std::stringstream &stream) override;
  std::string hint() override;
};
