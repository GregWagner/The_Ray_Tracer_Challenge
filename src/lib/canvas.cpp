#include "canvas.h"

#include <algorithm>
#include <sstream>

namespace rtc {

    int clamp_color_component(double component) {
        component = std::clamp(component, 0.0, 1.0);
        return static_cast<int>(component * 255.0 + 0.5);
    }

} // namespace
