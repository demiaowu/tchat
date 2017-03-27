//
// Created by demiaowu on 2017/3/26.
//
#include <boost/bind.hpp>

#include "chat_connection.h"
#include "chat_manager.h"


namespace chat {
    namespace server {

        chat_connection::chat_connection(chat_manager& manager, io_service& io)
            : manager_(manager),
              socket_(io) {
        }

        //TODO using the std::bind will occur compile error.
        void chat_connection::start() {
            socket_.async_read_some(boost::asio::buffer(read_msg_.get_msg(), chat_message::get_header_len()),
                                    boost::bind(&chat_connection::handle_read_header,
                                                shared_from_this(),
                                                boost::asio::placeholders::error));
            //boost::asio::async_read(socket_,
            //                        boost::asio::buffer(read_msg_.get_msg(), chat_message::get_header_len()),
            //                        std::bind(&chat_session::handle_read_header, shared_from_this().get(), boost::asio::placeholders::error));
        }

        void chat_connection::handle_read_header(const boost::system::error_code &ec) {
            if (!ec && read_msg_.decode_header()) {
                boost::asio::async_read(socket_,
                                        boost::asio::buffer(read_msg_.get_body(), read_msg_.get_body_len()),
                                        boost::bind(&chat_connection::handle_read_body, shared_from_this(), boost::asio::placeholders::error));
            } else {
                manager_.stop(shared_from_this());
            }
        }

        void chat_connection::handle_read_body(const boost::system::error_code& ec) {
            if (!ec) {
                manager_.deliver_msg(read_msg_);
                LOG_TRACE << "receive a message :" << std::string(read_msg_.get_body(), read_msg_.get_body_len());
                async_read(socket_,
                           boost::asio::buffer(read_msg_.get_msg(), chat_message::get_header_len()),
                           boost::bind(&chat_connection::handle_read_header,
                                       shared_from_this(),
                                       boost::asio::placeholders::error));
            }
            else {
                manager_.stop(shared_from_this());
            }
        }

        void chat_connection::deliver_msg(const chat_message& msg){
            size_t len =  write_msgs_.size();

            if (len < chat_connection::max_message_queue_size) {
                write_msgs_.push_back(msg);
            }

            bool write_in_progress = ! (len == 0);
            if (!write_in_progress) {   // Not write, thus write this message now
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                         boost::bind(&chat_connection::handle_write, shared_from_this(), boost::asio::placeholders::error));
            }
        }

        void chat_connection::handle_write(const boost::system::error_code& error) {
            if (!error) {
                LOG_TRACE << "write a message success :" << std::string(write_msgs_.front().get_body(), write_msgs_.front().get_body_len());
                write_msgs_.pop_front();
                if (!write_msgs_.empty())
                {
                    boost::asio::async_write(socket_,
                                             boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                             boost::bind(&chat_connection::handle_write, shared_from_this(),
                                                         boost::asio::placeholders::error));
                }
            }
            else {
                manager_.stop(shared_from_this());
            }
        }

        void chat_connection::stop() {
            socket_.close();
        }

    } // server namespace
} // chat namespace

