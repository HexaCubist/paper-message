#pragma once
#include <HTTPClient.h>

// Use one instance of the HTTPClient class to reduce reconnects and memory usage
class HttpClientSingleton {
public:
    static HTTPClient& getInstance() {
        static HTTPClient instance;
        return instance;
    }

private:
    HttpClientSingleton() {} // Private constructor to prevent instantiation
    HttpClientSingleton(const HttpClientSingleton&) = delete;
    HttpClientSingleton& operator=(const HttpClientSingleton&) = delete;
};