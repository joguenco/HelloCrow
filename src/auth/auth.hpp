#pragma once

#include "crow.h"
#include "crow/middleware.h"
#include <string>
#include <unordered_set>

namespace auth
{
    struct BearerTokenAuth : public crow::ILocalMiddleware
    {
        struct context
        {
            std::string token;
            bool is_authenticated = false;
        };

        void before_handle(crow::request& req, crow::response& res, context& ctx)
        {
            // Get Authorization header
            auto auth_header = req.get_header_value("Authorization");
            
            if (auth_header.empty())
            {
                res.code = 401;
                res.set_header("Content-Type", "application/json");
                res.body = R"({"error": "Missing Authorization header"})";
                res.end();
                return;
            }

            // Check if it starts with "Bearer "
            const std::string bearer_prefix = "Bearer ";
            if (auth_header.size() < bearer_prefix.size() || 
                auth_header.substr(0, bearer_prefix.size()) != bearer_prefix)
            {
                res.code = 401;
                res.set_header("Content-Type", "application/json");
                res.body = R"({"error": "Invalid Authorization header format. Expected: Bearer <token>"})";
                res.end();
                return;
            }

            // Extract token
            std::string token = auth_header.substr(bearer_prefix.size());
            
            // Validate token (you can customize this validation logic)
            if (!is_valid_token(token))
            {
                res.code = 401;
                res.set_header("Content-Type", "application/json");
                res.body = R"({"error": "Invalid or expired token"})";
                res.end();
                return;
            }

            // Store token in context for use in route handlers
            ctx.token = token;
            ctx.is_authenticated = true;
        }

        void after_handle(crow::request& /*req*/, crow::response& /*res*/, context& /*ctx*/)
        {
            // Optional: Add any post-processing logic here
        }

    private:
        // Token validation function - customize this based on your needs
        // This is a simple example that checks against a set of valid tokens
        // In production, you might want to:
        // - Validate JWT tokens
        // - Check against a database
        // - Verify token expiration
        // - Check token signature
        bool is_valid_token(const std::string& token) const
        {
            if (token.empty())
            {
                return false;
            }

            // Example: Check against a set of valid tokens
            // In production, replace this with proper token validation
            static const std::unordered_set<std::string> valid_tokens = {
                "your-secret-token-here",
                "another-valid-token"
            };

            return valid_tokens.find(token) != valid_tokens.end();
        }
    };
} // namespace auth
