//
// Created by demiaowu on 2017/3/25.
//
#include <iostream>
#include <list>

#include <boost/bind.hpp>

#include "chat_client.h"
#include "chat_rapidjson.h"
#include "chat_room_demo.h"
#include "logger.h"

namespace chat {
    namespace client {


        chat::client::chat_client::chat_client(const std::string &address, const std::string &port)
            : io_service_(),
              signals_(io_service_),
              socket_(io_service_),
              enter_room_(false){
            signals_.add(SIGINT);
            signals_.add(SIGTERM);
            signals_.async_wait(std::bind(&chat_client::handle_stop, this));


            boost::asio::ip::tcp::resolver resolver(io_service_);
            boost::asio::ip::tcp::resolver::query query(address, port);
            boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

            boost::asio::async_connect(socket_,
                                       iterator,
                                       boost::bind(&chat_client::handle_connect, this, boost::asio::placeholders::error));
        }

        void chat::client::chat_client::run() {
            io_service_.run();
        }

        void chat_client::write(const chat::server::chat_message& msg) {
            io_service_.post(boost::bind(&chat_client::do_write, this, msg));
        }

        void chat_client::handle_connect(const boost::system::error_code &ec) {
            if (!ec) {
                boost::asio::async_read(socket_,
                                        boost::asio::buffer(read_msg_.get_msg(), chat::server::MSG_HEADER_LEN),
                                        boost::bind(&chat_client::handle_read_header, this,
                                                    boost::asio::placeholders::error));
            } else {
                LOG_ERROR << ec.message();
                do_close();
            }
        }

        void chat_client::do_write(const chat::server::chat_message& msg) {
            int len = write_msgs_.size();
            if (len < max_message_queue_size) {
                write_msgs_.push_back(msg);
            } // else discard

            bool work_in_progress = !(0 == len);
            if (!work_in_progress) {
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                         boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error));
            }
        }

        void chat_client::handle_write(const boost::system::error_code &ec) {

            if (!ec) {
                LOG_TRACE << "write msg success:" << write_msgs_.front().get_body();
                write_msgs_.pop_front();
                if (!write_msgs_.empty()) {
                    boost::asio::async_write(socket_,
                                             boost::asio::buffer(write_msgs_.front().get_msg(), write_msgs_.front().get_msg_len()),
                                             boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error));
                }
            } else {
                LOG_ERROR << ec.message();
                do_close();
            }
        }

        void chat_client::close() {
            io_service_.post(boost::bind(&chat_client::do_close, this));
        }

        void chat_client::do_close() {
            socket_.close();
            // exit(-1) ??????????
        }

        void chat_client::handle_read_header(const boost::system::error_code &ec) {
            if (!ec && read_msg_.decode_header()) {
                boost::asio::async_read(socket_,
                                        boost::asio::buffer(read_msg_.get_body(), read_msg_.get_body_len()),
                                        boost::bind(&chat_client::handle_read_body, this, boost::asio::placeholders::error));
            }
            else {
                LOG_ERROR << ec.message();
                do_close();
            }
        }

        void chat_client::handle_read_body(const boost::system::error_code& ec) {
            if (!ec) {

                switch (read_msg_.get_command()[0]) {
                    case 'l':
                        {
                            std::list<chat::server::chat_room_demo> room_list = chat::server::string_to_rooms(read_msg_.get_body());
                            std::cout << "\nRoom list:" << std::endl;
                            for (auto iter=room_list.begin(); iter != room_list.end(); ++iter) {
                                std::cout << "  " << iter->get_room_id() << ":" << iter->get_room_name() << std::endl;
                            }
                            std::cout<<std::endl;
                        }
                        break;
                    case 'j':
                        LOG_TRACE << "加入room";
                        break;
                    default:
                        std::cout.write(read_msg_.get_body(), read_msg_.get_body_len());
                        std::cout << "\n";
                        break;
                }
                boost::asio::async_read(socket_,
                                        boost::asio::buffer(read_msg_.get_msg(), chat::server::MSG_HEADER_LEN),
                                        boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error));
            }
            else {
                LOG_ERROR << ec.message();
                do_close();
            }
        }

        void chat_client::handle_stop() {
            LOG_INFO << "client handle_stop";
            socket_.close();
            io_service_.stop();
        }

        bool chat_client::get_enter_room_flag() const {
            return enter_room_;
        }

        void chat_client::set_enter_room_flag(bool enter_room_flag) {
            enter_room_ = enter_room_flag;
        }


    } // client namespace
} // chat namespace