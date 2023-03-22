#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

#include "Person.h"
// output.cpp
void write_to_csv (std::vector<Person>& people,
                   std::string filename);