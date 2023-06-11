#include "layer_stack.h"
#include <logger/logger.h>

void utils::LayerStack::init() {}

void utils::LayerStack::tick(float delta) {
    for (Layer *layer : this->layers) {
        layer->onTick(delta);
    };
}

void utils::LayerStack::shutdown() {
    for (int i = this->layers.size() - 1; i >= 0; i--) {
        this->layers[i]->onDetach();
        delete this->layers[i];
        this->layers.erase(this->layers.begin() + i);
    };
    delete this;
}

utils::Layer *utils::LayerStack::addLayer(Layer *layer) {
    this->layers.push_back(layer);
    this->layers[this->layers.size() - 1]->onAttach();
    return this->layers[this->layers.size() - 1];
};

void utils::LayerStack::removeLayer(const char *name) {
    for (int i = 0; i < this->layers.size(); i++) {
        if (this->layers[i]->getName() == name) {
            this->layers[i]->onDetach();
            delete this->layers[i];
            this->layers.erase(this->layers.begin() + i);
            return;
        }
    }
    LOG_CLIENT_ERROR("LayerStack: ",
                     (std::string("Invalid layer named ") +
                      std::string(name))
                         .c_str());
    return;
}