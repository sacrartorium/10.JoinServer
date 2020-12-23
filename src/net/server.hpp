#pragma once

#include "session.hpp"

struct Server {
  Server(boost::asio::io_service &service,
         const boost::asio::ip::tcp::endpoint &ep, DataBasePtr db);

private:
  void accept();

  boost::asio::ip::tcp::acceptor mAcceptor;
  boost::asio::ip::tcp::socket mSocket;
  std::set<SessionPtr> mSessions;
  DataBasePtr mDataBase;
};
using ServerPtr = std::shared_ptr<Server>;
