#include <iostream>
#include <fstream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include "spdlog/fmt/bin_to_hex.h"

#define MAX_INPUT_SIZE 4096

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: afl_driver <input_file>\n";
        return 1;
    }

    const char* input_file = argv[1];

    // Open the input file
    std::ifstream file(input_file, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open input file\n";
        return 1;
    }

    // Read the input data
    char input_buf[MAX_INPUT_SIZE];
    file.read(input_buf, sizeof(input_buf));

    // Initialize the logger
    auto logger = spdlog::stdout_logger_mt("logger");

    // Set the log level to display all messages
    spdlog::set_level(spdlog::level::trace);
    spdlog::enable_backtrace(32);

    // Log the input data
    logger->trace("Input data: {}", input_buf);
    std::array<char, MAX_INPUT_SIZE> buf;
    std::copy(std::begin(input_buf), std::end(input_buf), buf.begin());
    logger->info("Hex output: {}", spdlog::to_hex(buf));
    // Close the input file
    file.close();
    return 0;
}
