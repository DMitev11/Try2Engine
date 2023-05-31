#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
namespace try1 {
    class EventEmitter {
      public:
        EventEmitter() = default;
        ~EventEmitter() = default;
        template <typename... Args>
        void Emit(int event, Args... args);
        template <typename... Args>
        uint32_t On(int event,
                    std::function<void(Args...)> cb);
        uint32_t On(int event, std::function<void()> cb);
        template <typename... Args>
        uint32_t Once(int event,
                      std::function<void(Args...)> cb);
        uint32_t Once(int event, std::function<void()> cb);
        void Remove(int event, uint32_t id);

      protected:
        EventEmitter(const EventEmitter &) = delete;
        EventEmitter(EventEmitter &&) = delete;
        template <typename... Args>
        uint32_t AddListener(int event, bool callOnce,
                             std::function<void(Args...)>);
        template <typename... Args>
        void EmitEvent(int event, Args... args);

        struct ListenerBase {
            ListenerBase() = delete;

            ListenerBase(int event, bool callOnce)
                : event(event), callOnce(callOnce) {}

            virtual ~ListenerBase() {}

            const int event;
            const bool callOnce;
        };

        template <typename... Args>
        struct Listener : public ListenerBase {
            Listener() = delete;

            Listener(int event, bool callOnce,
                     std::function<void(Args...)> c)
                : ListenerBase(event, callOnce), cb(c) {}

            std::function<void(Args...)> cb;
        };

        std::unordered_map<
            int, std::map<uint32_t,
                          std::shared_ptr<ListenerBase>>>
            listeners;
        std::unordered_map<int, uint32_t> lastListener;
    };
} // namespace try1
