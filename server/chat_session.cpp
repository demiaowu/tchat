//
// Created by demiaowu on 2017/3/25.
//
#include <boost/bind.hpp>

#include "chat_session.h"


namespace chat {
    namespace server {

        //TODO using the std::bind will occur compile error.
        void chat_session::start() {
            room_.join(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(read_msg_.get_msg(), chat_message::get_header_len()),
                                    boost::bind(&chat_session::handle_read_header,
                                              shared_from_this(),
                                              boost::asio::placeholders::error));
            //boost::asio::async_read(socket_,
            //                        boost::asio::buffer(read_msg_.get_msg(), chat_message::get_header_len()),
            //                        std::bind(&chat_session::handle_read_header, shared_from_this().get(), boost::asio::placeholders::error));
        }

        void chat_session::handle_read_header(const boost::system::error_code &error) {
            if (!error && read_msg_.decode_header()) {
                boost::asio::async_read(socket_,
                                        boost::asio::buffer(read_msg_.get_body(), read_msg_.get_body_len()),
                                        boost::bind(&chat_session::handle_read_body, shared_from_this(), boost::asio::placeholders::error));
            } else {
                room_.leave(shared_from_this());
            }
        }

        void chat_session::handle_read_body(const boost::system::error_code& error) {
            if (!error) {
                room_.deliver_msg(read_msg_);
                async_read(socket_,
                           boost::asio::buffer(read_msg_.get_msg(), chat_message::get_header_len()),
                           boost::bind(&chat_session::handle_read_header,
                                     shared_from_this(),
                                     boost::asio::placeholders::error));
            }
            else {
                room_.leave(shared_from_this());
            }
        }

        void chat_session::deliver_msg(const chat_message& msg) {
            size_t len =  write_msgs_.size();

            if (len < chat_session::max_message_queue) {
                write_msgs_.push_back(msg);
            }

            bool write_in_progress = ! (len == 0);
            if (!write_in_progress) {   // Not write, thus write this message now
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                         boost::bind(&chat_session::handle_write, shared_from_this(), boost::asio::placeholders::error));
            }
        }

        void chat_session::handle_write(const boost::system::error_code& error) {
            if (!error) {
                write_msgs_.pop_front();
                if (!write_msgs_.empty())
                {
                    boost::asio::async_write(socket_,
                                             boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                             boost::bind(&chat_session::handle_write, shared_from_this(),
                                                         boost::asio::placeholders::error));
                }
            }
            else {
                room_.leave(shared_from_this());
            }
        }

    } // server namespace
} // chat namespace