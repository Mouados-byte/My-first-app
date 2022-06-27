#include "fileio.h"



void writef(std::vector<LOGIN> inps) {
    std::fstream fapp;
    fapp.open("Names.txt", std::ios::app);
    for (const auto& inp : inps) {
        fapp << inp.name << "," << inp.passwd << "\n";
    }
}

std::vector<LOGIN> readf() {
    using namespace std;
    std::fstream foutt;
    foutt.open("Names.txt");
    LOGIN holder;
    vector<LOGIN> ret;
    while (getline(foutt, holder.name , ',')) {
        getline(foutt, holder.passwd);
        ret.push_back(holder);
    }
    return ret;
}

int ifname(char* name) {
    static std::vector<LOGIN> resources = readf();
    for (auto resource : resources) {
        if (strcmp(resource.name.c_str(), name) == 0) {
            return 1;
        }
    }
    return 0;
}
