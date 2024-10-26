#include <renderengine/Plugin.h>

#include <mutex>
#include <map>

#include <dlfcn.h>

#include <log/log.h>

namespace android {
namespace renderengine {

Plugin::Plugin(const char *soname)
{
    mHandle = dlopen(soname, RTLD_LOCAL | RTLD_NOW);
    if (mHandle) {
        ALOGI("Successfully loaded libcrtfilter.so:");
    } else {
        ALOGE("Failed to load libcrtfilter.so:");
    }
    const char* msg;
    do {
        std::string message((msg = dlerror()) ? msg : "no error");
        ALOGI("dlerror: %s", message.c_str());
    } while (msg);
}

Plugin::~Plugin()
{
    if (mHandle)
        dlclose(mHandle);
}

void *Plugin::symbol(const char *name) const
{
    if (mHandle)
        return dlsym(mHandle, name);

    return nullptr;
}

sp<Plugin> Plugin::createPlugin(const char *soname)
{
    // Ensure that we only load the plugin once
    static std::mutex mutex;
    static std::map<std::string, sp<Plugin>> plugins;

    std::lock_guard<std::mutex> lock(mutex);
    auto it = plugins.find(soname);
    if (it == plugins.end()) {
        it = plugins.emplace(soname, new Plugin(soname)).first;
    }
    return it->second;
}

} // namespace renderengine
} // namespace android
