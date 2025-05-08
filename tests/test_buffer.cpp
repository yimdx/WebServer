#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <modern/lib.hpp>
#include "buffer/buffer.hpp"
#include <string>

TEST_CASE( "Buffer construction and deconstrucion", "[Buffer]" ) {
    SECTION("Buffer construction"){
        webs::Buffer buffer(1024);
    }

    SECTION("Buffer read and write"){
        webs::Buffer buffer(1024);
        buffer.append("test data", 9);
        auto data = buffer.peek();
        auto str = std::string(data);
        INFO(data);
        REQUIRE( data == std::string("test data") );
    }

    SECTION("Buffer readable and writable"){
        webs::Buffer buffer(1024);

        REQUIRE(buffer.readable() == 0);
        REQUIRE(buffer.writable() == 1024);

        buffer.append("test data", 9);
        auto data = buffer.peek();
        auto str = std::string(data);
        REQUIRE(buffer.readable() == 9);
        REQUIRE(buffer.writable() == 1024-9);
    }

    SECTION("Buffer retrieve"){
        webs::Buffer buffer(1024);
        
        buffer.append("test data", 9);
        auto data = buffer.peek();
        auto str = std::string(data);
        buffer.retrieve(9);
        REQUIRE(buffer.readable() == 0);
    }
}
