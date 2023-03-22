#ifndef PERSON_H
#define PERSON_H
#include<iostream>
#include<vector>
#include<random>
#include<array>
//#include"Coordinate.h"
#include"Community.h"

enum class StatusType {
    Sucepticle,
    Recovered,
    Infected
};



class Person{
    
    private:
        // unique id
        const unsigned _id;

        // status: sucepticle = 0; recovered = 1; infected = 2
        StatusType _status;

        // position
        Coordinate _coordinate;

        // time point getting infected
        int _infected_time;

        // pointer of id
        static inline unsigned counter = 0;

        // quarantine situation
        bool _if_quarantine;

        // latent period situation
        bool _if_latent;

        // times/frequency being infected
        int _infected_fre;

        // probability to get infected at the time and place
        double _prob_infected;

        // velocity
        double _velocity;

        // current community
        Community _community;

        ////record the commmunity where the infected person is found
        Community _original_comm;

        // target
        Point _target;
        
    public:
        // Constuctor
        Person(int box_len, int box_wid, Community comm);

        // get the id of the person
        unsigned id();

        // get the status of the person
        StatusType status ();

        // get the position of person
        Coordinate position();

        //get the infected time of person
        int infected_time();

        bool if_quarantine();
        bool set_quarantine();

        bool if_latent();
        bool set_latent();
        
        // get the information how many times the person has been infected
        int infected_fre();

        // get the infected probability of each person
        double prob_infected();

        bool if_infected();

        // get velocity
        double velocity();

        // int community();
        Community community();

        // examine whether the person has target
        bool if_target();

        void get_infected(int curr_time);
        void get_recovered();


        // how a person moves inside the box
        void movestep();
        void transfer(Community &to_comm);
        void approach(int to_point_id);

        void prob_calculator(double beta, int n_infected);
        
        bool gen_prob();
        void update (int recover_time, double radius, 
                    double beta, int world_time, 
                    std::vector<Person> &people,
                    std::vector<Community> &world);
        
};


#endif