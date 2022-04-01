project(tcp_server_multithread C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS -pthread)

add_executable(tcp_server_multithread main.c logic_server.c logic_server.h logic_response.c logic_response.h)
