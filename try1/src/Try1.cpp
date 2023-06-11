#include <inc/Try1.h>
#include <utils/layer.h>
class LayerTry : public utils::Layer {
  public:
    LayerTry(const char *name) : Layer(name) {
        this->name = name;
    };
    ~LayerTry() override{};
    void onAttach() {}
    void onDetach() {}
    void onTick(float delta) {}
};

using namespace try1;
Try1::Try1(){

};
void Try1::run() {
    this->layerStack.addLayer(new LayerTry("try1"));
    this->layerStack.tick(1);
    this->layerStack.removeLayer("try1");
};
Try1::~Try1(){};