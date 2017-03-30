//
// Created by demiaowu on 2017/3/25.
//
#include <boost/bind.hpp>

#include "chat_server.h"

#include "logger.h"

namespace chat {
    namespace server {

        chat_server::chat_server(const std::string &address, const std::string &port)
            : io_service_(),
              signals_(io_service_),
              acceptor_(io_service_),
              conncetion_manager_()
              {

            signals_.add(SIGINT);
            signals_.add(SIGTERM);
            signals_.async_wait(std::bind(&chat_server::handle_stop, this));

            boost::asio::ip::tcp::resolver resolver(io_service_);
            boost::asio::ip::tcp::resolver::query query(address, port);
            boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
            acceptor_.open(endpoint.protocol());
            acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            acceptor_.bind(endpoint);
            acceptor_.listen();

            start_accept();
        }

        void chat::server::chat_server::run() {
            LOG_INFO << "chat server begin to run";
            io_service_.run();
        }

        void chat_server::handle_stop() {
            LOG_INFO << "chat server handle_stop()";
            io_service_.stop();
        }

        void chat_server::start_accept() {
            new_socket_.reset(new chat_socket(*this, io_service_));
            acceptor_.async_accept(new_socket_->get_socket(),
                                   boost::bind(&chat_server::handle_accept, this, boost::asio::placeholders::error));
        }

        void chat_server::handle_accept(const boost::system::error_code &ec) {
            if (!ec) {
                LOG_INFO << "accept from:" << new_socket_.get()->get_socket().remote_endpoint().address().to_string() \
                         << ":" \
                         <<  new_socket_.get()->get_socket().remote_endpoint().port();
                start(new_socket_);
            }
            start_accept();
        }

        void chat_server::start(chat_socket_ptr socket) {
            sockets_.insert(socket);
            socket->start();
        }

        uint64_t chat_server::get_new_room_id() {
            uint64_t room_id = 0;
            while (room_id ++) {
                if (room_ids.end() == room_ids.find(room_id)) {
                    room_ids[room_id] = true;
                    break;
                }
            };

            return room_id;
        }

        void chat_server::create_room(const std::string room_name, boost::asio::ip::tcp::socket& socket) {
            chat_room_ptr room = std::make_shared<chat_room>(get_new_room_id(), room_name, conncetion_manager_);
            chat_session_ptr session = std::make_shared<chat_session>(*room.get(), room->get_session_manager(),socket.get_io_service());
//            session->get_connection()->get_socket() = socket;
            boost::asio::ip::tcp::socket& sock = session->get_connection()->get_socket();
            session->get_connection()->get_socket().assign(socket.remote_endpoint().protocol(), socket.native());
            rooms_.insert(room);
            room->start(session);
        }

    } // server namespace
} // chat namespace

