//
// Created by demiaowu on 2017/3/25.
//

#ifndef TCHAT_NONCOPYABLE_H
#define TCHAT_NONCOPYABLE_H

namespace chat {
    namespace common {
        class noncopyable {
        public:
            noncopyable() = default;
            virtual ~noncopyable() = default;

        protected:
            noncopyable(const noncopyable &) = delete;
            const noncopyable &operator=(const noncopyable &) = delete;
        }; // noncopyable class

    } // common namespace
} //chat namespace

#endif //TCHAT_NONCOPYABLE_H
