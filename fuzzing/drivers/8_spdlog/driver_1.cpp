#include <iostream>
#include <fstream>

#include "../../projectFiles/8_spdlog/include/spdlog/spdlog.h"
#include "../../projectFiles/8_spdlog/include/spdlog/sinks/stdout_sinks.h"
#include "../../projectFiles/8_spdlog/include/spdlog/fmt/bin_to_hex.h"

#define MAX_INPUT_SIZE 4096

int main() {
    // Open the input file
    auto & file = std::cin;
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
    return 0;
}
