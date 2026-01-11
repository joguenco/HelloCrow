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

    // Protected route - requires bearer token authentication
    CROW_ROUTE(app, "/protected")
    .CROW_MIDDLEWARES(app, auth::BearerTokenAuth)
    ([] {
        // If we reach here, the token was validated successfully
        // The token is stored in the middleware context
        crow::response res;
        res.set_header("Content-Type", "application/json");
        res.body = R"({"message": "Access granted", "status": "authenticated"})";
        return res;
    });

    // Register other routes (these won't have auth middleware unless explicitly added)
    ping::RegisterRoutes(app);
    version::RegisterRoutes(app);

    app.port(PORT).multithreaded().run();

    return 0;
}
