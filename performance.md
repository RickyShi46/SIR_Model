# Performance Analysis

We use ```gprof``` to evaluate the code performance in two scenarios by changing the probability of how people choose their move strategy, keeping the other conditions the same. 
```
Number of people: 500
Length of the sides of the box: 100
Width of the sides of the box: 80
Probability of spreading the infection: 0.6
Infection radius: 5
Number of timesteps that should be calculated: 40
```

**The first scenario:** The person who is not in quarantine has 
- 10% probability to transfer to another community
- 50% probability to move randomly in his present community
- 40% probability to move towards fixed points in his present community

**The second scenario:** The person who is not in quarantine has 
- 50% probability to transfer to another community
- 30% probability to move randomly in his present community
- 20% probability to move towards fixed points in his present community.

Through the evaluation of the performance of these two scenarios, we find that the running time of ```Point``` function, ```Community``` function and ```Person``` function will change significantly with the change of the probability of how people choose their move strategy. **(The performance evaluations will be showed at the end of the text)**


# Optimization

The sample we use to test
```
Number of people: 500
Length of the sides of the box: 100
Width of the sides of the box: 80
Probability of spreading the infection: 0.6
Infection radius: 5
Number of timesteps that should be calculated: 40
```

## Optimization 1

We replace the comparing distance and std::pow with comparing distance square and a cheaper multiplication:
```
double distance = (c1.x - c2.x)*(c1.x - c2.x) + (c1.y - c2.y)*(c1.y - c2.y)
```
Then we find that the percentage of the total running time of the program used by Community constructor containing this command decreases significantly and the elapsed time also decreased about 1% compared to the original code.

**Original Perfomance:**

elapsed time: 9.193
```
Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 50.01      0.06     0.06  3707841     0.02     0.02  Community::Community(Community const&)
 25.00      0.09     0.03  9266693     0.00     0.00  Point::Point(Point const&)
 16.67      0.11     0.02  1851011     0.01     0.06  Person::Person(Person const&)
```

**Improved Performance:**

elapsed time: 9.088
```
Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 57.15      0.04     0.04  9304223     0.00     0.00  Point::Point(Point const&)
 28.58      0.06     0.02  3722856     0.01     0.01  Community::Community(Community const&)
 14.29      0.07     0.01  1858511     0.01     0.04  Person::Person(Person const&)
```

## Optimization 2

We combine two if branch into one if branch for two place:
```
if(_community != world[5] && _if_quarantine){
            _original_comm = _community;
            _target = point_null;
            transfer(world[5]);
        }
if (otherp._status == StatusType::Infected
                && distance(otherp._coordinate, _coordinate) <= radius){
                n_infected++;       
            } 
```
In this case, we can see that the percentage of the total running time of the program used by people constructor decreases significantly and the elapsed time also decreases about *4%* compared to the original code.

**Original Perfomance**:

elapsed time: 10.266s
```
Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 58.83      0.10     0.10  3576000     0.03     0.03  Community::Community(Community const&)
 11.77      0.12     0.02  1785011     0.01     0.07  Person::Person(Person const&)
```

**Improved Performance**:

elapsed time: 9.838s
```
Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 46.67      0.07     0.07  3584811     0.02     0.02  Community::Community(Community const&)
 13.34      0.09     0.02  8959133     0.00     0.00  Point::Point(Point const&)
 13.34      0.11     0.02  3585817     0.01     0.01  Community::~Community()
  6.67      0.12     0.01  8961655     0.00     0.00  Point::~Point()
  6.67      0.13     0.01  1790011     0.01     0.02  Person::~Person()
  6.67      0.14     0.01  1789511     0.01     0.06  Person::Person(Person const&)
  6.67      0.15     0.01   146788     0.07     0.07  Point::position()
```

## The performance of the first scenario
see ```s1performance.txt```

## The performance of the second scenario
see ```s2performance.txt```