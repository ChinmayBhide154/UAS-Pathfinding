/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include "JSON.h"


#include <fstream>
// #include <nlohmann/json.hpp>    // NOTE: Change to the line below
#include "../submodules/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
int main()
{
    std::ifstream f("Text.json");
    json data = json::parse(f);
    json otherdata = data.at("Name");
    std::cout << otherdata.at("id1");
    std::cout << otherdata.at("id2");
    return 0;
}