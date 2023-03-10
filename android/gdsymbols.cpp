#include "include/gd/include/gd.h"
#include "techno.h"

namespace GDSymbols {
    const char *libraryName = "libcocos2dcpp.so";
    namespace MenuLayer {
        const char *init(void *menuLayerClass) {
            return "_ZN9MenuLayer4initEv";
        }
    }
    namespace FLAlertLayer {
        const char *create(FLAlertLayerProtocol *delegate, char *title, std::string contents, const char *btn0, const char *btn2) {
            return "_ZN12FLAlertLayer6createEP20FLAlertLayerProtocolPKcSsS3_S3_fbf";
        }
    }
}
