#include "server.hpp"

#include "session.hpp"

Server::Server(boost::asio::io_service &service,
               const boost::asio::ip::tcp::endpoint &ep, DataBasePtr db)
    : mAcceptor(service, ep), mSocket(service), mSessions(), mDataBase(db) {
  accept();
}

void Server::accept() {
  mAcceptor.async_accept(mSocket, [this](boost::system::error_code errorCode) {
    if (!errorCode) {
      auto session =
          std::make_shared<Session>(std::move(mSocket), mSessions, mDataBase);
      mSessions.insert(session);
      session->begin();
    }
    accept();
  });
}
