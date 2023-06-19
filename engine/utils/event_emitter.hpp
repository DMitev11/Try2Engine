#pragma once
#include <functional>
#include <iostream>
#include <logger/logger.h>
#include <map>
#include <memory>
#include <unordered_map>
namespace utils {
    /**
     * @brief Bind listeners and emit events, based on
     * bindings
     * @ref
     * https://www.rioki.org/2014/12/29/eventemitter-in-c.html
     *
     */
    class EventEmitter {
      public:
        EventEmitter() = default;
        ~EventEmitter() = default;

        /**
         * @brief Emit an event from the subject which has
         * an instance of this class
         *
         * @tparam Args Based of what each event emits. \n
         * There's not a concrete amount or type of
         * arguments which can be emitted when emitting an
         * event
         * @param event Type of event to emit
         * @param args
         */
        template <typename... Args>
        void Emit(int event, Args... args);

        /**
         * @brief Bind a listener to a specific event.
         * @note Each listener should know the type and
         * amount of argument which used during an emit
         * of specific event
         *
         * @tparam Args Based on what does an event emit
         * @param event Type of event
         * @param cb supports only std::function, but
         * std::function(<lambda>) is a valid callback
         * too
         * @return uint32_t id of the listener
         */
        template <typename... Args>
        uint32_t On(int event,
                    std::function<void(Args...)> cb);

        /**
         * @see EventEmitter::On
         * @note Allows for parameterless functions as
         * callbacks
         */
        uint32_t On(int event, std::function<void()> cb);

        /**
         * @brief Similar to `On` but the listener (and its
         * callback/handler) is removed after handling a
         * single event emit
         * @see EventEmitter::On
         *
         * @tparam Args
         * @param event Type of event to emit
         * @param cb supports only std::function, but
         * std::function(<lambda>) is a valid callback
         * too
         * @return uint32_t id of the listener
         */
        template <typename... Args>
        uint32_t Once(int event,
                      std::function<void(Args...)> cb);

        /**
         * @see EventEmitter::Once
         * @note Allows for parameterless functions as
         * callbacks
         */
        uint32_t Once(int event, std::function<void()> cb);

        /**
         * @brief Remove an event listener (and its
         * callback/handler)
         *
         * @param event Type of event to which is bound
         * @param id of the listener
         */
        void Remove(int event, uint32_t id) {
            auto i = this->listeners.find(event);
            if (i == listeners.end()) {
                throw std::runtime_error(
                    "invalid event key");
            }
            auto &map = i->second;
            auto j = map.find(id);
            if (j == map.end()) {
                throw std::runtime_error(
                    "invalid listener key");
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

      protected:
        EventEmitter(const EventEmitter &) = delete;
        EventEmitter(EventEmitter &&) = delete;

        /**
         * @brief Called by On and Once. Adds a new event
         * listener (and a handler/callback for it) and
         * returns a unique id (for the event) corresponding
         * to it
         * @warning Ids overlap for different event types =>
         * id "1" could be valid for event "1" and event "2"
         * simultaneously
         *
         * @tparam Args variadic, based on the emitted event
         * @param event Type of the event
         * @param callOnce If the listener should be deleted
         * after a single call of the callback
         * @return uint32_t Id of the listener
         */
        template <typename... Args>
        uint32_t AddListener(int event, bool callOnce,
                             std::function<void(Args...)>);

        /**
         * @brief Called by EventEmitter::Emit. \n Checks if
         * there are any listeners to the argumented type of
         * event, retrieves all listeners and calls
         * their callbacks/handlers
         *
         * @tparam Args
         * @param event Type of event
         * @param args Parameters for that type of event
         * emit
         */
        template <typename... Args>
        void EmitEvent(int event, Args... args);

        /**
         * @brief Shared data between each listener
         */
        struct ListenerBase {
            ListenerBase() = delete;

            ListenerBase(int kEvent, bool kCallOnce)
                : kEvent(kEvent), kCallOnce(kCallOnce) {}

            virtual ~ListenerBase() {}

            /**
             * @brief Type of an event emit
             */
            const int kEvent;

            /**
             * @brief If it should be deleted after a single
             * callback/handler call
             */
            const bool kCallOnce;
        };

        /**
         * @brief Derivative defining possible variations of
         * listeners, based on what events are handled by
         * all event emitters, therefore what are all
         * possible parameters for a callback/handler
         *
         * @tparam Args Varation of parameters for a
         * callback/handler function
         */
        template <typename... Args>
        struct Listener : public ListenerBase {
            Listener() = delete;

            Listener(int event, bool callOnce,
                     std::function<void(Args...)> c)
                : ListenerBase(event, callOnce), cb(c) {}

            std::function<void(Args...)> cb;
        };

        /**
         * @brief Storage of listeners
         *
         * @note Unordered map for all events, as possible
         * types of events do not need to belong to a single
         * enum => every int is a valid event type.
         * An event emit must care only
         * for all listeners to the emitted event type.
         * An <int> could be shared between two event types
         * (eventA = 1, eventB = 1), but only if their
         * argument list differs
         *
         * @warning Emit (by the same event emitter) of 2
         * different event types with the same Id and same
         * argument list could lead to unhandled behaviour
         *
         * @note Map for listeners of an event type, as ids
         * of listeners should be unique, for the event
         * type. `lastListener` do not decrement, only
         * increment to prevent overlapping ids ex. Listener
         * "3" gets removed, but Listener "2" should still
         * be valid
         */
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
            LOG_ENGINE_ERROR("EventEmitter: ",
                             "invalid cb");
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
            return;
        }
        std::vector<uint32_t> keysToDelete;
        for (const auto &pair : this->listeners[event]) {
            std::shared_ptr<Listener<Args...>> ptr =
                std::static_pointer_cast<Listener<Args...>>(
                    pair.second);
            if (ptr) {
                ptr->cb(args...);
                if (ptr->kCallOnce) {
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
} // namespace utils