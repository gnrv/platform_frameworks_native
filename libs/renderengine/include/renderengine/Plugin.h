#pragma once

#include <utils/RefBase.h>

namespace android {
namespace renderengine {

// A small wrapper around dlopen/dlsym to load a plugin
class Plugin : public RefBase {
public:
    void *symbol(const char *name) const;

    static sp<Plugin> createPlugin(const char *soname);

protected:
    Plugin(const char *soname);
    virtual ~Plugin();

    void *mHandle = nullptr;
};

} // namespace renderengine
} // namespace android
