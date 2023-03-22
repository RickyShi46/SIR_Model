# AdvProg_SIR
Bonus project: SIR model

Contributed by Junting Yao and Shi Yu

Latest Version: version 3


## Introduction
The goal of this project is to implement SIR model to simulate and visualize the spread of an epidemic. 
The idea is to gradually increase the sophistication of the simulation by adding more assumptions and conditions, 
e.g. more complex behaviors of the people (people living in households, going to work, grocery store, separated communities, quarantine). Additionally, we might switch to to a modified SIR
model to include different assumptions about the epidemic itself, 
e.g. a latent period of the disease where the person is not infectious. In the end, a visualization of the simulated data is planned.

Source:  
- General project description: [SIR model](https://gitlab.lrz.de/tum-i05/public/advprog-project-ideas.git)

## Prepare
```matplotlibcpp``` is included in this project. Therefore, please make sure the following files have been installed before you compile and run the code.
- Python
- numpy
- matplotlib

You can read this website for more details about [matplotlib-cpp](https://github.com/lava/matplotlib-cpp)

## Install
- Clone the repository
```
https://gitlab.lrz.de/00000000014AEAAB/advprog_sir.git
```
- Go into the top level directory
```
cd advprog_sir
```
- Create a ```build``` directory and a ```data``` directory
```
mkdir build
mkdir data
```
- Run cmake let it compile the files in src and write makefiles in ```build```
```
cmake -S ./src -B ./build . -G "Unix Makefiles"
```
- Generate the executables
```
cd build
make
```
- Run the code
```
./main
```

## Tasks and Contribution

### Sprint 1
- [x] **definition.h & definition.cpp:** definition of parameters and assumptions
    - Assume infected people will get recovered after 14 days
    - Initialize the global vector of infected people, which stores the serial number of infected people
- [x] **function.h:** definition of functions 
- [x] **init.cpp:** initialize all people 
    - Initialize the serial number, position and status
    - The initial position of each person is randomly distributed
    - There is only one infected person whose serial number is randomly chosen
    - Define the timestep for the infected as 0; the uninfected as -1 until they get infected
- [x] **move.cpp:** let people move in each time step
    - Each person's position is represented by coordinate _[x,y]_
    - People move randomly (both x and y increases or decreases _[0,1]_ with the precision of 0.1) in each time step
    - Define boundary area so that people will not move outside the box
- [x] **SIR.cpp:** how the status of each person gets changed 
    - function eraser: When the person is recovered, he or she will be removed from the infected people list
    - function f: Suceptible people who are in the infection radius have certain probability to get infected
    - function get_infected: get each person's information (position, status) at the end of the timestep through the iteration of each timestep and each person
        - how person gets infected
        - how person gets recovered
- [x] **output.cpp:** print results to .csv file

### Sprint 2
- [x] **Improvements:** change structure into class, object-oriented program
- [x] **Community.h & Community.cpp:** create the map of the city which includes five communities and a hospital       
    - Set the fixed model of the community
    - There are two fixed meeting points in each community. (class Point)
    - Create communities in the four directions and middle of the city. Create the hospital in the northwest of the city.
- [x] **Person.h & Person.cpp:** initialize and update the state of a person
    - Initialize the serial number, position, host community, status, target.
    - The infected person has 70% probability to get quarantined which means transfered to hospital and 40% probability to have laten period of the disease.
    - The recovered person will be transfered to original community from hospital.
    - For person who stays in the community, there's 25% probability to move randomly and 75% to approach the fixed point.
    - We assume that people can travel from one community to another within one timestep with certain public transformation.
    - The person who has a target fixed point will approch the target in a dichotomy way. The target will be canceled when the person get in a certain span around the fixed point which defined in Point.cpp.
    - We assume that a person who is in quarantine or during latent periode has no probability to spread infection. The probability is positive related to number of infected (not latent) surrounding, negative related to frequency of getting infected. 
    - Update the status of a person in each timestep.
- [x] **Point.h & Point.cpp:** create the fixed points in each community       
    - Each fixed point has its name, position and approach radius
    - We assume that when people are inside its approach radius, it is defined as reaching the point.


### Sprint 3
- [x] **Visualization:** _matplotlibcpp.h_ is used for the visualization of the result
    - visualization of world map 
    - visualization of each person 

## User-defined Parameters
Open the _main.exe_ file in _.\build_ folder to run the code

User needs to define the following parameters:

- **population:** the total number of people that needs to be simulated and visualized
- **box_len:** length of the square box in which simulated people move
- **beta:** probability of spreading the infection
- **radius:** infection radius, when sucepticle people are inside the radius of an infected person, then they are possible to be infected
- **num_timesteps:** number of timesteps that should be calculated
- **filename:** name of the .csv file which stores results





