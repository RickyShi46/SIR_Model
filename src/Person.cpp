#include"Person.h"


Person::Person(int box_len, int box_wid, Community comm)
// initialize id
:_id(counter){
    _status = StatusType::Sucepticle;
    _infected_time = -1;
    _if_quarantine = 0;
    _if_latent = 0;
    _infected_fre = 0;
    _prob_infected = 0.0;

    // in one timestep, a person can at most move the value of _velocity
    _velocity = 1.0;

    _community = comm;
    _original_comm = comm;

    // if _target = null, it means no target and move randomly
    _target = point_null;

    //_coordinate.x = ((rand() % (int(comm._length * 10) - 1)) + 1) / 10.0 + comm.northwest.x;
    //_coordinate.y = ((rand() % (int(comm._width * 10) - 1)) + 1) / 10.0 + comm.southeast.y;
    _coordinate.x = ((rand() % (int(comm._length * 10) - 1)) + 1) * 0.1 + comm.northwest.x;
    _coordinate.y = ((rand() % (int(comm._width * 10) - 1)) + 1) * 0.1 + comm.southeast.y;
    
    counter++;
}

unsigned Person::id(){
    return _id;
}

StatusType Person::status(){
    return _status;
}

Coordinate Person::position(){
    return _coordinate;
}


int Person::infected_time(){
    return _infected_time;
}

bool Person::if_quarantine(){
    return _if_quarantine;
}

bool Person::set_quarantine(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::discrete_distribution<> dist({0.5,0.5});
    return dist(gen);
}

bool Person::if_latent(){
    return _if_latent;
}

bool Person::set_latent(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::discrete_distribution<> dist({0.6,0.4});
    return dist(gen);
}

int Person::infected_fre(){
    return _infected_fre;
}

double Person::prob_infected(){
    return _prob_infected;
}

bool Person::if_infected(){
    if (_status == StatusType::Infected) 
        return true;
    else
        return false;
}

double Person::velocity(){
    return _velocity;
}

Community Person::community(){
    return _community;
}

bool Person::if_target(){
    //return _if_target;
    if(_target.position().x == 0.0 && _target.position().y == 0.0){
        return false;
    }
    else{
        return true;
    }
}

// Change parameters for infected people
void Person::get_infected(int curr_time){
    _status = StatusType::Infected;
    _infected_time = curr_time;
    _if_latent = set_latent();
    if(!_if_latent){
        _if_quarantine = set_quarantine();
    }
    _infected_fre++;
}

void Person::get_recovered(){
    _status = StatusType::Recovered;
    _infected_time = -1;
    if(_if_quarantine == 1){
        _if_quarantine = 0;
        transfer(_original_comm);
    }
}

void Person::movestep(){
    if (_coordinate.x - _community.northwest.x <= 1.0){
        _coordinate.x += (rand() % 10 + 1) * 0.1;
    }
    else if(_community.northeast.x - _coordinate.x <= 1.0){
        _coordinate.x -= (rand() % 10 + 1) * 0.1;
    }
    else if(rand() % 2){
        _coordinate.x += (rand() % 10 + 1) * 0.1; 
    }
    else{
        _coordinate.x -= (rand() % 10 + 1) * 0.1;   
    }

    if(_coordinate.y - _community.southeast.y <= 1.0){
        _coordinate.y += (rand() % 10 + 1) * 0.1;     
    }
    else if(_community.northeast.y - _coordinate.y <= 1.0){
        _coordinate.y -= (rand() % 10 + 1) * 0.1;   
    }
    else if(rand() % 2){
        _coordinate.y += (rand() % 10 + 1) * 0.1;   
    }
    else{
        _coordinate.y -= (rand() % 10 + 1) * 0.1;     
    }
}

/* 
    Assumption: with certain public transformation, people can travel
    from one community to another within one timestep
*/
void Person::transfer(Community &to_comm){
    Coordinate temp{};
    Coordinate min_coordinate{};
    double min_distance = (to_comm._length * 5) * (to_comm._length * 5);
    double tempdist = 0.0;

    if (to_comm._len_gate_n != 0){
        // transfer to the gate of the to_comm
        min_coordinate.x = ((rand() % (int(to_comm._len_gate_n * 10) - 1)) + 1) * 0.1 + to_comm.gate_nw.x;
        min_coordinate.y = to_comm.gate_ne.y;
        min_distance = distance(min_coordinate, _coordinate);
    }

    if (to_comm._len_gate_s != 0){
        // transfer to the gate of the to_comm
        temp.x = ((rand() % (int(to_comm._len_gate_s * 10) - 1)) + 1) * 0.1 + to_comm.gate_sw.x;
        temp.y = to_comm.gate_se.y;
        tempdist = distance(temp, _coordinate);
        if (tempdist < min_distance){
            min_coordinate = temp;
            min_distance = tempdist;
        }
    } 

    if (to_comm._len_gate_e != 0){
        // transfer to the gate of the to_comm
        temp.x = to_comm.gate_en.x;
        temp.y = ((rand() % (int(to_comm._len_gate_e * 10) - 1)) + 1) * 0.1 + to_comm.gate_es.y;
        //tempdist = pow(temp.x - _coordinate.x, 2) + pow(temp.y - _coordinate.y, 2);
        tempdist = distance(temp, _coordinate);
        if (tempdist < min_distance){
            min_coordinate = temp;
            min_distance = tempdist;
        }
    }  

    if (to_comm._len_gate_w != 0){
        // transfer to the gate of the to_comm
        temp.x = to_comm.gate_wn.x;
        temp.y = ((rand() % (int(to_comm._len_gate_w * 10) - 1)) + 1) * 0.1 + to_comm.gate_ws.y;
        tempdist = distance(temp, _coordinate);
        if (tempdist < min_distance){
            min_coordinate = temp;
            min_distance = tempdist;
        }
    }  
    _coordinate = min_coordinate; 
    _community = to_comm;
    _original_comm = to_comm;
}

void Person::approach(int to_point_id){
    // attracted by the fixed point
    // define _target at the first time
    if(to_point_id == 1){ 
        // fixed point 1
        _target = _community._fpoint1;     
    }
    else{
        // fixed point 2
        _target = _community._fpoint2;      
    }

    if(if_target()){
        _coordinate.x = int((_target.position().x + _coordinate.x) * 0.5 * 100) * 0.01;
        _coordinate.y = int((_target.position().y + _coordinate.y) * 0.5 * 100) * 0.01;
    }
    
    if(distance(_coordinate, _target.position()) <= _target.approach_radius() * _target.approach_radius()){
        // reach the target point
        _target = point_null;
    }
}

void Person::prob_calculator(double beta, int n_infected){
    // Assumption 1: no probability in quarantine
    // Assumption 2: no probability during latent periode

    // Assumption 3: increased index at fixed point
    // index is positive related to number of infected (not latent) surrounding
    _prob_infected = 1 - pow(1 - beta, n_infected);

    // Assumption 4: decreased index when infected second time
    // index is negative related to frequency of getting infected
    double de_index = exp(- 0.2 * _infected_fre);

    _prob_infected = de_index * _prob_infected;

}

bool Person::gen_prob() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::discrete_distribution<> dist({1-_prob_infected,0,_prob_infected});
    return dist(gen);
}

void Person::update(int recover_time, double radius, 
                    double beta, int world_time, 
                    std::vector<Person> &people,
                    std::vector<Community> &world){

    if (_status == StatusType::Infected){
        // infected person get recovered
        if(_infected_time >= 0 && world_time - _infected_time > recover_time){
            get_recovered();
        }

       // infected person get quarantined
        if(_community != world[5] && _if_quarantine){
            _original_comm = _community;
            _target = point_null;
            transfer(world[5]);
        }
        
    }

    else{
        int n_infected = 0;     // number of infected inside radius
        // examine how many infected surrounding
        for (Person otherp:people){
            if (otherp._status == StatusType::Infected
                && otherp._id != _id
                && distance(otherp._coordinate, _coordinate) <= radius * radius){
                n_infected++;       
            } 
        }
        
        if (n_infected != 0){
            prob_calculator(beta, n_infected);
            if(gen_prob()){
                get_infected(world_time); 
            }
        }
    }
}


    