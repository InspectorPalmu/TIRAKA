// Datastructures.hh
//
// Student name: Lauri Mänty
// Student email: lauri.manty@tuni.fi
// Student number: H290353

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <queue>
#include <map>

// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};



struct Town
{
    TownID town_id_;
    Name town_name_;
    Coord town_coord_;
    int town_tax_;
    bool visited = false;
    Town* prev = nullptr;
    Town* master_ = nullptr;
    std::unordered_map<TownID, Town*> vassals_;
    std::unordered_map<TownID, Town*> roads_;

};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: .size command for unordered map
    //                               is constant in time complexity
    unsigned int town_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: each pointer needs to be destructed
    void clear_all();

    // Estimate of performance: O(1)
    // Short rationale for estimate: .find and .insert are constant
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance: O(1)
    // Short rationale for estimate: .find is constant
    Name get_town_name(TownID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: .find is constant
    Coord get_town_coordinates(TownID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: .find is constant
    int get_town_tax(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: for loop
    std::vector<TownID> all_towns();

    // Estimate of performance: O(n)
    // Short rationale for estimate: for loop
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance: O(1)
    // Short rationale for estimate: .find is constant
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: std::sort uses approximately nlog(n) comparisons
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: std::sort uses approximately nlog(n) comparisons
    //                               and euclidean distance is constant
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: same as towns_distance_increasing()
    //                               but we just return first value
    TownID min_distance();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: same as towns_distance_increasing()
    //                               but we just return last value
    TownID max_distance();

    // Estimate of performance: O(1)
    // Short rationale for estimate: .find and insert are constant
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: for loop
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: recursion, vector.pushback() and .find() are constants
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: for loop
    bool remove_town(TownID id);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: same as towns_distance_increasing()
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance: O(n)
    // Short rationale for estimate: it has to go through each town that is vassal to master
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: it has to go through each town that is vassal to master
    int total_net_tax(TownID id);

    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Have to go through each town
    void clear_roads();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: map insert is logarithmic
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: O(1)
    // Short rationale for estimate: .find is constant and single elemtn insertion is constant
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: same as get_town_vassals
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance: O(V+E)
    // Short rationale for estimate: BFS
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory phase 2 operations

    // Estimate of performance: O(1)
    // Short rationale for estimate: find is constant
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance: O(V+E)
    // Short rationale for estimate: BFS
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_road_network();

private:
    std::unordered_map<TownID, Town*> townMap;   

    std::vector<std::pair<TownID, TownID>> roadVec;

    double eucDist(Coord coord1, Coord coord2 = {0,0});

    std::vector<TownID> taxer_path_recursive(Town* masterTown,std::vector<TownID>& masterVec);

    std::vector<TownID> longest_path_recursive(Town* vassalTown, std::vector<TownID>& tempPath, std::vector<TownID>& longestPath);

    int total_net_tax_recursive(Town* vassalTown);

    std::vector<TownID> trace_route(TownID end);

};


#endif // DATASTRUCTURES_HH
