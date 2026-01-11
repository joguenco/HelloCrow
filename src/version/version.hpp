#pragma once

#include "crow.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace version {
    template<typename App>
    void RegisterRoutes(App& app)
    {        
        CROW_ROUTE(app, "/version")
        ([] {
            crow::response res;
            res.set_header("Content-Type", "application/json");
            json response = {{"version", "1.0.0"}};
            res.body = response.dump();
            return res;
        });
    }
} // namespace version
