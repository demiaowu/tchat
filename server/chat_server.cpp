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
              room_(),
              new_session_() {

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
            new_session_.reset(new chat_session(io_service_, room_));
            acceptor_.async_accept(new_session_->get_socket(),
                                   boost::bind(&chat_server::handle_accept, this, boost::asio::placeholders::error));
        }

        void chat_server::handle_accept(const boost::system::error_code &ec) {
            if (!ec) {
                LOG_INFO << new_session_->get_socket().local_endpoint().address().to_string() \
                         << " : " \
                         <<  new_session_->get_socket().local_endpoint().port();
                new_session_->start();
            }
            start_accept();
        }
    } // server namespace
} // chat namespace

