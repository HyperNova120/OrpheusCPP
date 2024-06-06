#include "JsonReader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

std::string getBot_Token()
{
    std::ifstream input_data("config.json");
    if (input_data.fail())
    {
        throw std::runtime_error("Unable to open config file");
    }
    nlohmann::json data;
    input_data >> data;
    return data["token"];
}