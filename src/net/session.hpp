#pragma once

#include "../db/database.hpp"

#include <boost/asio.hpp>
#include <set>

struct Session : public std::enable_shared_from_this<Session> {
  using SessionPtr = std::shared_ptr<Session>;

  Session(boost::asio::ip::tcp::socket socket, std::set<SessionPtr> &sessions,
          DataBasePtr db);
  void begin();

private:
  void read();

  boost::asio::ip::tcp::socket mSocket;
  char mData;

  std::string mBuffer;
  std::set<SessionPtr> &mSessions;
  DataBasePtr mDataBase;
};

using SessionPtr = std::shared_ptr<Session>;
