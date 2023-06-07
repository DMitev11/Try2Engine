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
        void Remove(int event, uint32_t id) {
            auto i = this->listeners.find(event);
            if (i == listeners.end()) {
                throw std::runtime_error(
                    "invalid event key");
            }
            auto& map = i->second;
            auto j = map.find(id);
            if (j == map.end()) {
                throw std::runtime_error(
                    "invalid listener key");
            }
            std::shared_ptr<ListenerBase>& ptr = j->second;
            ptr.reset();
            ptr = nullptr;
            map.erase(j);
            if (map.empty()) {
                this->listeners.erase(i);
            }
            return;
        }

    protected:
        EventEmitter(const EventEmitter&) = delete;
        EventEmitter(EventEmitter&&) = delete;
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
        struct Listener: public ListenerBase {
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

    template <typename... Args>
    uint32_t EventEmitter::AddListener(
        int event, bool callOnce,
        std::function<void(Args...)> cb) {
        if (!cb) {
            throw std::runtime_error("invalid cb");
        }
        if (this->lastListener.end() ==
            this->lastListener.find(event)) {
            this->lastListener[event] = 0;
        }
        uint32_t id = ++this->lastListener[event];
        if (this->listeners.find(event) ==
            this->listeners.end()) {
            this->listeners[event] =
                std::map<uint32_t,
                std::shared_ptr<ListenerBase>>();
        }
        this->listeners[event][id] =
            std::make_shared<Listener<Args...>>(
                id, callOnce, cb);

        return id;
    }
    template <typename... Args>
    uint32_t
        EventEmitter::On(int event,
            std::function<void(Args...)> cb) {
        return this->AddListener(event, false, cb);
    }

    template <typename... Args>
    uint32_t
        EventEmitter::Once(int event,
            std::function<void(Args...)> cb) {
        return this->AddListener(event, true, cb);
    }

    template <typename... Args>
    void EventEmitter::EmitEvent(int event, Args... args) {
        if (this->listeners.end() ==
            this->listeners.find(event)) {
            throw std::runtime_error("invalid event");
        }
        std::vector<uint32_t> keysToDelete;
        for (const auto& pair : this->listeners[event]) {
            std::shared_ptr<Listener<Args...>> ptr =
                std::static_pointer_cast<Listener<Args...>>(
                    pair.second);
            if (ptr) {
                ptr->cb(args...);
                if (ptr->callOnce) {
                    keysToDelete.push_back(pair.first);
                }
            }
        }
        for (const uint32_t key : keysToDelete) {
            this->listeners[event].erase(key);
        }
    }

    template <typename... Args>
    void EventEmitter::Emit(int event, Args... args) {
        this->EmitEvent(event, args...);
    }

} // namespace try1
