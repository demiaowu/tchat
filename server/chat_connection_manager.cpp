//
// Created by demiaowu on 2017/3/26.
//

#include "chat_connection_manager.h"
#include "chat_connection.h"
#include "chat_message.h"


namespace chat {
    namespace server {


        void chat_connection_manager::start(chat_participant_ptr con) {
            connections_.insert(con);
            con->start();
        }

        void chat_connection_manager::stop(chat_participant_ptr con) {
            con->stop();
            connections_.erase(con);
        }

        void chat_connection_manager::stop_all() {
            for(auto iter=connections_.begin(); iter!=connections_.end(); ++iter) {
                iter->get()->stop();
            }
            connections_.clear();
        }

        void chat_connection_manager::deliver_msg(const chat_message &msg) {

        }
    } // server namespace
} // chat namespace