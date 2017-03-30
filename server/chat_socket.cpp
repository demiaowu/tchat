//
// Created by demiaowu on 2017/3/29.
//
#include <boost/bind.hpp>
#include <iostream>

#include "chat_socket.h"
#include "chat_server.h"
#include "logger.h"

namespace chat {
    namespace server {

        chat_socket::chat_socket(chat_server& server, io_service& io)
                : server_(server),
                  socket_(io) {
        }

        //TODO using the std::bind will occur compile error.
        void chat_socket::start() {
            socket_.async_read_some(boost::asio::buffer(read_msg_.get_msg(), read_msg_.get_header_len()),
                                    boost::bind(&chat_socket::handle_read_header,
                                                shared_from_this(),
                                                boost::asio::placeholders::error));
            //boost::asio::async_read(socket_,
            //                        boost::asio::buffer(read_msg_.get_msg(), chat_message::get_header_len()),
            //                        std::bind(&chat_session::handle_read_header, shared_from_this().get(), boost::asio::placeholders::error));
        }

        void chat_socket::handle_read_header(const boost::system::error_code &ec) {
            LOG_TRACE << ":" << (int)read_msg_.get_msg()[0]  << "-" << (int)read_msg_.get_msg()[1] << "-" << read_msg_.get_msg()[2] << "-" << read_msg_.get_msg()[3];

            if (!ec && read_msg_.decode_header()) {
                switch (read_msg_.get_command()[0]) {
                    case 'c':
                        LOG_TRACE << "创建room.";

                        break;
                    case 's':
                        LOG_TRACE << "接收到的消息是:" << read_msg_.get_body_len() <<  read_msg_.get_body();
                        break;
                    case 'l':
                        LOG_TRACE << "列举所有room";
                        break;
                    case 'j':
                        LOG_TRACE << "加入某个room";
                        break;
                    case 'm':
                        LOG_TRACE << "切换到某个room";
                        break;
                    case 'e':
                        LOG_TRACE << "退出";
                        break;
                    default:
                        break;
                }

                socket_.async_read_some(boost::asio::buffer(read_msg_.get_body(), read_msg_.get_body_len()),
                                        boost::bind(&chat_socket::handle_read_body,
                                                    shared_from_this(),
                                                    boost::asio::placeholders::error));
            } else {
                LOG_ERROR << "read header failed" << ec.message();
                stop();
            }
        }

        void chat_socket::handle_read_body(const boost::system::error_code& ec) {
            LOG_TRACE << "enter handle_read_body" << ":" << read_msg_.get_body();
            if (!ec) {
                switch (read_msg_.get_command()[0]) {
                    case 'c':
                        LOG_TRACE << "创建room:" <<  read_msg_.get_body();
                        server_.create_room(read_msg_.get_body(), socket_);
                        break;
                    case 's':
                        LOG_TRACE << "接收到的消息是:" << read_msg_.get_body_len() <<  read_msg_.get_body();
                        break;
                    case 'l':
                        LOG_TRACE << "列举所有room";
                        break;
                    case 'j':
                        LOG_TRACE << "加入某个room";
                        break;
                    case 'm':
                        LOG_TRACE << "切换到某个room";
                        break;
                    case 'e':
                        LOG_TRACE << "退出";
                        break;
                }
                socket_.async_read_some(boost::asio::buffer(read_msg_.get_msg(), read_msg_.get_header_len()),
                           boost::bind(&chat_socket::handle_read_header,
                                       shared_from_this(),
                                       boost::asio::placeholders::error));
            }
            else {
                LOG_ERROR << "read body error" << ec.message();
                stop();
            }
        }

        void chat_socket::deliver_msg(const chat_message& msg){
            size_t len =  write_msgs_.size();

            if (len < chat_socket::max_message_queue_size) {
                write_msgs_.push_back(msg);
            }

            bool write_in_progress = ! (len == 0);
            if (!write_in_progress) {   // Not write, thus write this message now
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                         boost::bind(&chat_socket::handle_write, shared_from_this(), boost::asio::placeholders::error));
            }
        }

        void chat_socket::handle_write(const boost::system::error_code& error) {
            if (!error) {
                write_msgs_.pop_front();
                if (!write_msgs_.empty()) {
                    boost::asio::async_write(socket_,
                                             boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                             boost::bind(&chat_socket::handle_write, shared_from_this(),
                                                         boost::asio::placeholders::error));
                }
            }
            else {
                LOG_ERROR <<"write failed";
                stop();
            }
        }

        void chat_socket::stop() {
            socket_.close();
        }


    } // server namespace
} // chat namespace