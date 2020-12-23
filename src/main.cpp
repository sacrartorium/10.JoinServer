#include "db/database.hpp"
#include "db/table_manager.hpp"
#include "net/server.hpp"
#include "net/session.hpp"

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cout << "Error: join_server <port>" << std::endl;
    return -1;
  }

  DataBasePtr db = std::make_shared<DataBase>(std::make_shared<TableManager>());
  db->request("create A");
  db->request("create B");

  boost::asio::io_service service;

  size_t port = atoi(argv[1]);
  boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
  Server server(service, ep, db);

  service.run();

  return 0;
}
