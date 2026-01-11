#include "crow.h"

#include "ping/ping.hpp"
#include "version/version.hpp"
#include "utils/Utils.hpp"
#include "auth/auth.hpp"
#include <cstdio>

int main()
{
    const auto PORT = std::stoi(Utils::GetEnv("PORT", "8000"));

    // Use App with BearerTokenAuth middleware
    // This enables the middleware to be used on specific routes
    crow::App<auth::BearerTokenAuth> app;

    // Public route - no authentication required
    CROW_ROUTE(app, "/")
    ([] {
        return "Hello Crow!";
    });

    ping::RegisterRoutes(app);
    version::RegisterRoutes(app);

    app.port(PORT).multithreaded().run();

    return 0;
}
