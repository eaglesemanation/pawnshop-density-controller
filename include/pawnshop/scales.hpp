#pragma once
#include <chrono>
#include <fstream>
#include <future>
#include <optional>
#include <string>

namespace pawnshop {

class Scales {
public:
    Scales(const std::string serialPath);
    virtual ~Scales();
    std::optional<double> getWeight();
    bool poweredOn(
        std::chrono::duration<int> timeout = std::chrono::seconds(10));

private:
    std::string serial_path;
    struct State {
        std::string unit;
        double weight;
        bool stable;
        bool container;
    };
    std::optional<State> parse(const std::string line);
};

}  // namespace pawnshop
