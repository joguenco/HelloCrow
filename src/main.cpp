#include "crow.h"

#include "ping/ping.hpp"
#include "version/version.hpp"
#include "utils/Utils.hpp"
#include <cstdio>

int main()
{
    const auto PORT = std::stoi(Utils::GetEnv("PORT", "8000"));

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([] {
        return "Hello Crow!";
    });

    ping::RegisterRoutes(app);
    version::RegisterRoutes(app);

    app.port(PORT).multithreaded().run();

    return 0;
}
