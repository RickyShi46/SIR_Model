#include<iostream>
#include<sstream>
#include<cassert>
#include<fstream>
#include<vector>
#include<array>
#include<random>
#include<string>
#include<memory>
#include<algorithm>
#include<map>
#include<tuple>
#include<utility>
#include<cstring>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#include"Person.h"
#include"output.h"
//#include"Community.h"
//#include"prob_infected.h"

int main(){
    std::cout << "***Input paramaters***\n"; 

    // number of people
    int population{};
    std::cout << "Please enter the number of people: ";
    std::cin >> population;
    //std::cout << "Please enter a integer for population: ";
    

    // length of the sides of the box
    int box_len{};
    std::cout << "Please enter the length of the sides of the box: ";
    std::cin >> box_len;

    // width of the sides of the box
    int box_wid{};
    std::cout << "Please enter the width of the sides of the box: ";
    std::cin >> box_wid;

    // probability of spreading the infection
    // here the recovered are defined as not able to catch the disease again
    double beta{};
    double prob_infected{};
    std::cout << "Please enter the probability of spreading the infection: ";
    std::cin >> beta;

    // infection radius
    double radius{};
    std::cout << "Please enter the infection radius: ";
    std::cin >> radius;

    // number of timesteps that should be calculated
    int num_timesteps{};
    std::cout << "Please enter the number of timesteps that should be calculated: ";
    std::cin >> num_timesteps;

    const int recover_time = 14;
    
    static std::vector<Community> world = createworld(box_len, box_wid);

    // create certain number of people and initialize
    std::vector<Person> people{};
//    std::vector<InfectedPerson> infected_people{};
    // define the first infected person
    int first_infected_id = rand() % population; 
    for (int num_peo = 0; num_peo < population; num_peo++){
        int comm_id = rand() % 5;
        Person p = Person(box_len, box_wid, world[comm_id]);
        people.push_back(p);

        //Person p = Person(box_len, box_wid, comm);
        if (first_infected_id == people[num_peo].id()){
            people[num_peo].get_infected(0);
        }

    }

    

    for (int world_time = 0; world_time < num_timesteps; world_time++){
        for (int num_peo = 0; num_peo < population; num_peo++){
            
            if(!people[num_peo].if_target()){   // if the person has no target
                // 50% stay in the community; 50% travel (prob can be adjusted)
                if(rand() % 2){
                    
                    int to_comm_id = people[num_peo].community().id();
                    while(to_comm_id == people[num_peo].community().id()){
                        to_comm_id = rand() % 5;
                    }
                    people[num_peo].transfer(world[to_comm_id]);
                    
                }
                else if(rand() % 2){
                    people[num_peo].movestep();
                }
                else{
                    //approach to fixed points, first time has target
                    int fp_id = rand() % 2;
                    people[num_peo].approach(fp_id);
                    
                }
            }
            else{   // if the person has target, approch to the point until inside radius
                // approach to fixed points
                people[num_peo].approach(-1);
            }
            //prob_infected = prob_calculate(people[num_peo], beta);
            people[num_peo].update(recover_time, radius, beta, world_time, people, world); 
            
            /*
            if(!people[num_peo].if_target()){   // if the person has no target
                // 33% stay in the community; 33% travel (prob can be adjusted); 33% approach to fixed point
                int move_strategy = rand() % 3 + 1;
                switch (move_strategy)
                {
                case 1:{
                    int to_comm_id = people[num_peo].community().id();
                    while(to_comm_id == people[num_peo].community().id()){
                        to_comm_id = rand() % 5;
                    }
                    people[num_peo].transfer(world[to_comm_id]);                    
                    continue;
                }
                case 2:{
                    people[num_peo].movestep();
                    continue;
                }
                case 3:{
                    //approach to fixed points, first time has target
                    int fp_id = rand() % 2;
                    //people[num_peo].approach(fp_id);
                    continue;
                }
                default:
                    break;
                }
            }
            else{   // if the person has target, approch to the point until inside radius
                // approach to fixed points
                people[num_peo].approach(-1);
            }
            people[num_peo].update(recover_time, radius, beta, world_time, people, world);
            */
        }

    }

    // output the data into a .csv file
    // file will be stored in subfolder data
    std::string file_menu = "../data/";
    // define the filename by user
    std::string filename{};
    std::cout << "Please enter the filename: ";
    std::cin >> filename;
    filename = file_menu + filename + ".csv";
    write_to_csv (people, filename);

}