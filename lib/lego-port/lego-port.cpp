#include <lego-port.hpp>
using namespace Ev3Wrap;

Ev3Wrap::lego_port::lego_port(address_type address) {
    connect({{ "address", { address } }});
}

bool Ev3Wrap::lego_port::connect(const std::map<std::string, std::set<std::string>> &match) noexcept
{
    static const std::string _strClassDir { "sys/class/lego-port/" };
    static const std::string _strPattern  { "port" };

    try {
        return device::connect(_strClassDir, _strPattern, match);
    } catch (...) { }

    _path.clear();

    return false;
}