#include "ping.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ping {
    void RegisterRoutes(crow::SimpleApp& app)
    {
        CROW_ROUTE(app, "/ping")
        ([] {
            crow::response res;
            res.set_header("Content-Type", "application/json");

            json response = {{"message", "pong"}};
            res.body = response.dump();
            return res;
        });
    }
}
