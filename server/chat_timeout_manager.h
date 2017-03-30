//
// Created by demiaowu on 2017/3/30.
//

#ifndef TCHAT_CHAT_TIMEOUT_MANAGER_H
#define TCHAT_CHAT_TIMEOUT_MANAGER_H

#include <boost/asio.hpp>

namespace chat {
    namespace server {

        //TODO timeout manager
        class chat_timeout_manager {
        public:

        private:
            boost::asio::io_service& io_service_;
        }; // chat_timeout_manager class

    } // server namespace
} // chat namespace

#endif //TCHAT_CHAT_TIMEOUT_MANAGER_H
