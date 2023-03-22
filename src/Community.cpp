#include"Community.h"

Community::Community()
:_id(counter){

}

Community::Community(std::string name, int length, int width, Coordinate shift,
double gate_n, double gate_s, double gate_e, double gate_w)
:_id(counter){
    _community_name = name;

    _length = 0.2 * length;
    _width = 0.2 * width;

    northeast.x = shift.x + 0.5 * _length;
    northeast.y = shift.y + 0.5 * _width;

    northwest.x = shift.x - 0.5 * _length;
    northwest.y = shift.y + 0.5 * _width;

    southeast.x = shift.x + 0.5 * _length;
    southeast.y = shift.y - 0.5 * _width;

    southwest.x = shift.x - 0.5 * _length;
    southwest.y = shift.y - 0.5 * _width;

    // north gate
    _len_gate_n = gate_n;
    gate_ne.x = northeast.x - 0.5 * (_length - gate_n);
    gate_ne.y = northeast.y;
    gate_nw.x = northwest.x + 0.5 * (_length - gate_n);
    gate_nw.y = northwest.y;

    // south gate
    _len_gate_s = gate_s;
    gate_se.x = southeast.x - 0.5 * (_length - gate_s);
    gate_se.y = southeast.y;
    gate_sw.x = southwest.x + 0.5 * (_length - gate_s);
    gate_sw.y = southwest.y;

    // east gate
    _len_gate_e = gate_e;
    gate_en.x = northeast.x;
    gate_en.y = northeast.y - 0.5 * (_width - gate_s);
    gate_es.x = southeast.x;
    gate_es.y = southeast.y + 0.5 * (_width - gate_s);

    // west gate
    _len_gate_w = gate_w;
    gate_wn.x = northwest.x;
    gate_wn.y = northwest.y - 0.5 * (_width - gate_s);
    gate_ws.x = southwest.x;
    gate_ws.y = southwest.y + 0.5 * (_width - gate_s);

    // create fixed points in community
    // Assumption: every community (except hospital) has 2 fixed points, which position is relatively fixed
    if(_community_name != "hospital"){
        // define the approach radius of fixed points based on its length and width
        double appr_radius = 0.1 * std::min(_length,_width);
        
        Coordinate fp1{};
        Coordinate fp2{};
        fp1.x = southwest.x + 0.25 * _length;
        fp1.y = southwest.y + 0.25 * _width;
        _fpoint1 = Point(_community_name + "_edeka", fp1, appr_radius);
        
        fp2.x = northeast.x - 0.25 * _length;
        fp2.y = northeast.y - 0.25 * _width;
        _fpoint2 = Point(_community_name + "_dm", fp2, appr_radius);
         
    }
    
    else{
        _fpoint1 = point_null;
        _fpoint2 = point_null;
    }
    
    counter++;
}

Community& Community::operator=(const Community& from_Community){

    _community_name = from_Community._community_name;

    _length = from_Community._length;
    _width = from_Community._width;

    northeast = from_Community.northeast;
    northwest = from_Community.northwest;
    southeast = from_Community.southeast;
    southwest = from_Community.southwest;

    // north gate
    _len_gate_n = from_Community._len_gate_n;
    gate_ne = from_Community.gate_ne;
    gate_nw = from_Community.gate_nw;
    
    // south gate
    _len_gate_s = from_Community._len_gate_s;
    gate_se = from_Community.gate_se;
    gate_sw = from_Community.gate_sw;

    // east gate
    _len_gate_e = from_Community._len_gate_e;
    gate_en = from_Community.gate_en;
    gate_es = from_Community.gate_es;

    // west gate
    _len_gate_w = from_Community._len_gate_w;
    gate_wn = from_Community.gate_wn;
    gate_ws = from_Community.gate_ws;

    return *this;
}

bool Community::operator == (const Community& from_Community){
    if(_community_name.compare(from_Community._community_name) == 0){
        return true;
    }
    else{
        return false;
    }

}

bool Community::operator != (const Community& from_Community){
    if(_community_name.compare(from_Community._community_name) == 1){
        return true;
    }
    else{
        return false;
    }

}

int Community::id(){
    return _id;
}

std::string Community::name(){
    return _community_name;
}

void Community::display(){
    // display boundary
    int n = 101;
    std::vector<double> x_north(n), y_north(n),
                        x_south(n), y_south(n),
                        x_east(n), y_east(n),
                        x_west(n), y_west(n);
    for (int i = 0; i <= n-1; i++){
        // north boundary
        x_north.at(i) = northwest.x + _length/n * i;
        y_north.at(i) = northeast.y;
        // south boundary
        x_south.at(i) = x_north.at(i);
        y_south.at(i) = southeast.y;
        // east boundary
        x_east.at(i) = northeast.x;
        y_east.at(i) = southeast.y + _width/n * i;
        // west boundary
        x_west.at(i) = northwest.x;
        y_west.at(i) = y_east.at(i);
    }
    plt::plot(x_north, y_north, {{"color", "black"}});
    plt::plot(x_south, y_south, {{"color", "black"}});
    plt::plot(x_east, y_east, {{"color", "black"}});
    plt::plot(x_west, y_west, {{"color", "black"}});

    // display fixed points
    std::vector<double> theta(n+1),
                        x_fp1(n+1), y_fp1(n+1),
                        x_fp2(n+1), y_fp2(n+1);
    for (int i = 0; i <= n; i++){
        theta.at(i) = 2*M_PI / n * i;
        if(i == n){
            x_fp1.at(i) = _fpoint1.position().x;
            y_fp1.at(i) = _fpoint1.position().y;

            x_fp2.at(i) = _fpoint2.position().x;
            y_fp2.at(i) = _fpoint2.position().y;
        }
        else{
            // fixed point 1
            x_fp1.at(i) = _fpoint1.approach_radius() * cos(theta.at(i)) + _fpoint1.position().x;
            y_fp1.at(i) = _fpoint1.approach_radius() * sin(theta.at(i)) + _fpoint1.position().y;
            // fixed point 2
            x_fp2.at(i) = _fpoint2.approach_radius() * cos(theta.at(i)) + _fpoint2.position().x;
            y_fp2.at(i) = _fpoint2.approach_radius() * sin(theta.at(i)) + _fpoint2.position().y;
        }
    }
    plt::plot(x_fp1, y_fp1, {{"color", "black"}});    
    plt::plot(x_fp2, y_fp2, {{"color", "black"}});              

}


std::vector<Community> createworld(double box_len, double box_wid){
    std::vector<Community> world{};
    // create community
    double len_gate1 = 0.03 * box_wid;
    double len_gate2 = 0.03 * box_len;
    // Community west
    Coordinate shift_w;
    shift_w.x = - 0.3 * box_len;
    shift_w.y = 0;
    Community west = Community("west", box_len, box_wid, shift_w, 0.0, 0.0, len_gate1, 0.0);
    world.push_back(west);
    // Community north
    Coordinate shift_n;
    shift_n.x = 0;
    shift_n.y = 0.3 * box_wid;
    Community north = Community("north", box_len, box_wid, shift_n, 0.0, len_gate2, 0.0, 0.0);
    world.push_back(north);
    // Community east
    Coordinate shift_e;
    shift_e.x = 0.3 * box_len;
    shift_e.y = 0;
    Community east = Community("east", box_len, box_wid, shift_e, 0.0, 0.0, 0.0, len_gate1);
    world.push_back(east);
    // Community south
    Coordinate shift_s;
    shift_s.x = 0;
    shift_s.y = - 0.3 * box_wid;
    Community south = Community("south", box_len, box_wid, shift_s, len_gate2, 0.0, 0.0, 0.0);
    world.push_back(south);
    // Community middle
    Coordinate shift_m;
    shift_s.x = 0;
    shift_s.y = 0;
    Community middle = Community("middle", box_len, box_wid, shift_m, len_gate2, len_gate2, len_gate1, len_gate1);
    world.push_back(middle);
    // Hospital
    Coordinate shift_hos;
    shift_hos.x = - 0.3 * box_len;
    shift_hos.y = 0.3 * box_wid;
    Community hospital = Community("hospital", box_len, box_wid, shift_hos, 0.0, 0.0, 0.0, len_gate1);
    world.push_back(hospital);

    return world;
}