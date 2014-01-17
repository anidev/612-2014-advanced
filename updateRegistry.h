#ifndef UPDATE_REGISTRY
#define UPDATE_REGISTRY

#include <Vector>

class UpdateRegistry {
public:
    typedef void* obj;
    typedef void (helper*)(obj);
    struct registry_object {
        obj o;
        helper h;
    };
    UpdateRegistry();
    void add(registry_object);
    void update();
private:
    Vector<registry_object> registry;
};

#endif
