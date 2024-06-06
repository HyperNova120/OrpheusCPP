#include "JsonReader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

std::string getBot_Token()
{
    std::ifstream input_data("config.json");

    std::cout << "hi\n";
    if (input_data.fail())
    {
        throw std::runtime_error("Unable to open config file");
    }
    std::cout << "ji\n";
    nlohmann::json data;
    input_data >> data;
    std::cout << "ki\n";
    return data["token"];
}