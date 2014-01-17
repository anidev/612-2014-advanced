#include "UpdateRegistry.h"

UpdateRegistry::UpdateRegistry() {
    
}

UpdateRegistry::~UpdateRegistry() {
    
}

void UpdateRegistry::add(registry_object r) {
    registry.push_back(r);
}

void UpdateRegistry::update() {
    for (int i = 0; i < (int)registry.size(); i++) {
        ((registry.at(i)).h)((registry.at(i)).o);
    }
}
