//#include "Coordinate.h"
#include "Point.h"
#include<string>
#include<vector>
#include<algorithm>

#ifndef COMMUNITY_H
#define COMMUNITY_H
#include<iostream>

class Community{
        friend class Person;
    private:
        const unsigned _id;
        std::string _communityname;
        static inline unsigned counter = 0;
        
        double _length;
        double _width;
        Coordinate northeast;
        Coordinate northwest;
        Coordinate southeast;
        Coordinate southwest;

        double length_w_co;
        double length_e_co;

        double width_n_co;
        double width_s_co;

        // North gate
        double _len_gate_n;
        Coordinate gate_ne;
        Coordinate gate_nw;

        // South gate
        double _len_gate_s;
        Coordinate gate_se;
        Coordinate gate_sw;

        // East gate
        double _len_gate_e;
        Coordinate gate_en;
        Coordinate gate_es;

        // West gate
        double _len_gate_w;
        Coordinate gate_wn;
        Coordinate gate_ws;

        // Fixed Points
        //static std::vector<Point> _fixedpoints;
        //std::vector<Coordinate> _fixedpoints;
        Point _fpoint1;
        Point _fpoint2;
        //double _appr_radius;

    public:
        Community();
        Community(std::string name, int length, int width, Coordinate shift, 
                double gate_n, double gate_s, double gate_e, double gate_w);
        
        Community& operator=(const Community& from_Community);
        bool operator == (const Community& from_Community);
        bool operator != (const Community& from_Community);
        
        int id();
        std::string name();
        //std::vector<Point> fixedpoints();
        //std::vector<Coordinate> fixedpoints();
};


std::vector<Community> createworld(double box_len, double box_wid);

#endif