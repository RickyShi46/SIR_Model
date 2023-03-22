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
#include <stdexcept>
#include <cstdlib>
#include <chrono>

#include"Person.h"
#include"Output.h"

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

/* 
    FUNCTION:
    generate probability of how people choose their move strategy
    10% probability to transfer to another community
    50% move randomly
    40% move towards fixed points
*/
int gen_prob_move(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::discrete_distribution<> dist({0.1,0.5,0.4});
    return dist(gen);
}


int main(){

    /** Part 1: Input parameters **/
    std::cout << "***Input paramaters***\n"; 

    // number of people
    int population{};
    std::cout << "Please enter the number of people (e.g. 500): ";
    std::cin >> population;

    // length of the sides of the box
    int box_len{};
    std::cout << "Please enter the length of the sides of the box (e.g. 100): ";
    std::cin >> box_len;

    // width of the sides of the box
    int box_wid{};
    std::cout << "Please enter the width of the sides of the box (e.g. 80): ";
    std::cin >> box_wid;

    // probability of spreading the infection
    double beta{};
    double prob_infected{};
    std::cout << "Please enter the probability of spreading the infection (e.g. 0.6): ";
    std::cin >> beta;

    // infection radius
    double radius{};
    std::cout << "Please enter the infection radius (e.g. 5): ";
    std::cin >> radius;

    // number of timesteps that should be calculated
    int num_timesteps{};
    std::cout << "Please enter the number of timesteps that should be calculated (e.g. 20): ";
    std::cin >> num_timesteps;

    // Assumption: after 14 days people will recover from the disease
    const int recover_time = 14;
    

    /** Part 2: Initialize **/
    // create the world map
    static std::vector<Community> world = createworld(box_len, box_wid);

    // create certain number of people and initialize
    std::vector<Person> people{};
    
    // create a vector to store the x,y coordinate of infected and unifected people
    std::vector<double> uninfectedpeople_x_co{}, uninfectedpeople_y_co{},
                        infectedpeople_x_co{}, infectedpeople_y_co{};

    // define the first infected person
    int first_infected_id = rand() % population; 

    // initialize each person
    for (int num_peo = 0; num_peo < population; num_peo++){
        
        int comm_id = rand() % 5;
        Person p = Person(box_len, box_wid, world[comm_id]);
        people.push_back(p);

        if (first_infected_id == people[num_peo].id()){
            people[num_peo].get_infected(0);
        }

    }
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    start = std::chrono::system_clock::now();

    /** Part 3: Run **/
    for (int world_time = 0; world_time < num_timesteps; world_time++){
        for (int num_peo = 0; num_peo < population; num_peo++){
            /* Part 3.1: How people move */
            // people in quarantine can only move inside the hospital
            if(people[num_peo].if_quarantine()){
                people[num_peo].movestep();
            }
            else{
                // Person without target
                if(!people[num_peo].if_target()){  
                    int move_strategy = gen_prob_move();
                    // 10% probability to transfer to another community
                    if(move_strategy == 0){
                        int to_comm_id = people[num_peo].community().id();
                        while(to_comm_id == people[num_peo].community().id()){
                            to_comm_id = rand() % 5;
                        }
                        people[num_peo].transfer(world[to_comm_id]);
                    }
                    
                    // 50% move randomly
                    else if(move_strategy == 1){
                        people[num_peo].movestep();
                    }
                    
                    // 40% move towards fixed points
                    else if(move_strategy == 2){
                        //approach to fixed points, first time has target
                        int fp_id = rand() % 2 + 1;
                        people[num_peo].approach(fp_id);
                    }
                    
                }

                // Once the person has target, approch to the point until inside radius
                else{   
                    // approach to fixed points
                    people[num_peo].approach(-1);
                }
            }
            /* Part 3.2: Update the status */
            people[num_peo].update(recover_time, radius, beta, world_time, people, world); 

        /* Part 4: Display */
            if(people[num_peo].if_infected()){
                infectedpeople_x_co.push_back(people[num_peo].position().x);
                infectedpeople_y_co.push_back(people[num_peo].position().y);

            }
            else{
                uninfectedpeople_x_co.push_back(people[num_peo].position().x);
                uninfectedpeople_y_co.push_back(people[num_peo].position().y);

            }
        }
        plt::figure(1);
        //plt::title("total time step = $num-timesteps$ ");

        for (Community w:world){
        w.display();
        }

        plt::plot(infectedpeople_x_co,infectedpeople_y_co,"or");
        plt::plot(uninfectedpeople_x_co,uninfectedpeople_y_co,"og");
        plt::xlim(-0.5*box_len-1,0.5*box_len+1);
        plt::ylim(-0.5*box_wid-1,0.5*box_wid+1);
        plt::draw();
        plt::pause(0.1);
        plt::clf();
        infectedpeople_x_co.clear();
        infectedpeople_y_co.clear();
        uninfectedpeople_x_co.clear();
        uninfectedpeople_y_co.clear();

    }

    end = std::chrono::system_clock::now();
    auto elapsed =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time: " << elapsed.count()/1000.0 << " seconds" << std::endl;

    /** Part 5: Export the data **/
    // export the data into a .csv file
    // file will be stored in subfolder data
    std::string file_menu = "../data/";

    // define the filename by user
    std::string filename{};
    std::cout << "Please enter the filename: ";
    std::cin >> filename;
    filename = file_menu + filename + ".csv";
    write_to_csv (people, filename);

    return 0;
}