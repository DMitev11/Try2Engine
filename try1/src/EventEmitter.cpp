#include "inc/EventEmitter.h"
#include <stdexcept>
using namespace try1;
template <typename... Args>
uint32_t
EventEmitter::AddListener(int event, bool callOnce,
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
        std::make_shared<Listener<Args...>>(id, callOnce,
                                            cb);

    return id;
}

template <typename... Args>
uint32_t EventEmitter::On(int event,
                          std::function<void(Args...)> cb) {
    return this->AddListener(event, false, cb);
}

template <>
uint32_t EventEmitter::On(int event,
                          std::function<void(int i)> cb) {
    return this->AddListener(event, false, cb);
}

template <typename... Args>
uint32_t EventEmitter::Once(int event,
                            std::function<void(Args...)>) {
    return this->AddListener(event, true, cb);
}
template <>
uint32_t EventEmitter::Once(int event,
                            std::function<void(int i)> cb) {
    return this->AddListener(event, true, cb);
}

void EventEmitter::Remove(int event, uint32_t id) {
    auto i = this->listeners.find(event);
    if (i == listeners.end()) {
        throw std::runtime_error("invalid event key");
    }
    auto &map = i->second;
    auto j = map.find(id);
    if (j == map.end()) {
        throw std::runtime_error("invalid listener key");
    }
    std::shared_ptr<ListenerBase> &ptr = j->second;
    ptr.reset();
    ptr = nullptr;
    map.erase(j);
    if (map.empty()) {
        this->listeners.erase(i);
    }
    return;
}

template <typename... Args>
void EventEmitter::EmitEvent(int event, Args... args) {
    if (this->listeners.end() ==
        this->listeners.find(event)) {
        throw std::runtime_error("invalid event");
    }
    std::vector<uint32_t> keysToDelete;
    for (const auto &pair : this->listeners[event]) {
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
    this->EmitEvent(event, args);
}
template <> void EventEmitter::Emit(int event) {
    this->EmitEvent(event);
}
