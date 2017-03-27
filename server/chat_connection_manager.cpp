//
// Created by demiaowu on 2017/3/26.
//

#include "chat_connection_manager.h"
#include "chat_connection.h"


namespace chat {
    namespace server {


        void chat_connection_manager::start(chat_participant_ptr con) {
            connections_.insert(con);
            (dynamic_cast<chat_connection*>(con.get()))->start();
        }

        void chat_connection_manager::stop(chat_participant_ptr con) {
            connections_.erase(con);
            (dynamic_cast<chat_connection*>(con.get()))->stop();
        }

        void chat_connection_manager::stop_all() {
            for(auto iter=connections_.begin(); iter!=connections_.end(); ++iter) {
                (dynamic_cast<chat_connection*>(iter->get()))->stop();
            }
            connections_.clear();
        }
    } // server namespace
} // chat namespace