#include "session.hpp"

Session::Session(boost::asio::ip::tcp::socket socket,
                 std::set<SessionPtr> &sessions, DataBasePtr db)
    : mSocket(std::move(socket)), mData(0), mBuffer(""), mSessions(sessions),
      mDataBase(db) {}

void Session::begin() { read(); }

void Session::read() {
  auto session = shared_from_this();
  boost::asio::async_read(
      mSocket, boost::asio::buffer(&mData, 1),
      [this, session](boost::system::error_code errorCode,
                      [[maybe_unused]] std::size_t length) {
        if (!errorCode) {
          if (mData != '\n') {
            mBuffer += mData;
          } else {
            if (mBuffer.back() == '\r') {
              mBuffer.pop_back();
            }

            auto result = mDataBase->request(mBuffer);
            boost::asio::async_write(
                mSocket, boost::asio::buffer(result.c_str(), result.size()),
                [](const boost::system::error_code &errorCode,
                   [[maybe_unused]] std::size_t bytesTransferred) {
                  if (errorCode)
                    std::cout << "Writing data error: " << errorCode.message()
                              << std::endl;
                });
            mBuffer.clear();
          }
          read();
        } else {
          mSessions.erase(session);
          mSocket.close();
        }
      });
}
