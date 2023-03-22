#include"Output.h"
#include <iomanip>

std::ostream & operator<<(std::ostream &os, const StatusType &status){
    os << static_cast<std::underlying_type<StatusType>::type>(status);
    return os;
}

void write_to_csv (std::vector<Person>& people,
                   std::string filename){

    // open file stream for output
    std::ofstream csv_file(filename);

    // csv column headers
    csv_file << "id,x,y,status,community\n";
    // retain two digit
    std::cout<<std::setiosflags(std::ios::fixed)<<std::setprecision(2);
    
    for(Person p:people){

        csv_file << p.id() << "," << p.position().x << "," 
        << p.position().y<< "," << p.status() << "," << p.community().name() 
        << "\n";
    }

   csv_file.close();
}