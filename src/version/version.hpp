#pragma once

#include "crow.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "auth/auth.hpp"

namespace version
{
    template<typename App>
    void RegisterRoutes(App& app)
    {
        CROW_ROUTE(app, "/version").CROW_MIDDLEWARES(app, auth::BearerTokenAuth)([] {
            crow::response res;
            res.set_header("Content-Type", "application/json");
            json response = {{"version", "1.0.0"}};
            res.body = response.dump();
            return res;
        });
    }
} // namespace version
