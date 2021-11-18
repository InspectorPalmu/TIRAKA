// Datastructures.cc
//
// Student name: Lauri Mänty
// Student email: lauri.manty@tuni.fi
// Student number: H290353

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::town_count()
{
    // Replace the line below with your implementation
    return townMap.size();
}

void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    townMap.clear();
}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{

    if (townMap.find(id) != townMap.end())
        {
            return false;
        }
    else
        {
            Town* newTown = new Town;
            newTown->town_id_ = id;
            newTown->town_name_ = name;
            newTown->town_coord_ = coord;
            newTown->town_tax_ = tax;
            townMap.insert({id, newTown});
            return true;
        }

}

Name Datastructures::get_town_name(TownID id)
{
    std::unordered_map<TownID,Town*>::const_iterator it;
    it = townMap.find(id);
    if (it != townMap.end())
    {
        return it->second->town_name_;
    }
    else
    {
        return NO_NAME;
    }
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    std::unordered_map<TownID,Town*>::const_iterator it;
    it = townMap.find(id);
    if (it != townMap.end())
    {
        return it->second->town_coord_;
    }
    else
    {
        return NO_COORD;
    }
}

int Datastructures::get_town_tax(TownID id)
{
    std::unordered_map<TownID,Town*>::const_iterator it;
    it = townMap.find(id);
    if (it != townMap.end())
    {
        return it->second->town_tax_;
    }
    else
    {
        return NO_VALUE;
    }
}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> idVec;
    std::unordered_map<TownID,Town*>::const_iterator it;
    for(auto it=townMap.begin(); it!=townMap.end(); it++)
    {
        idVec.push_back(it->first);
    }
    return idVec;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{

    std::vector<TownID> nameVec;
    std::unordered_map<TownID,Town*>::const_iterator it;
    for(auto it=townMap.begin(); it!=townMap.end(); it++)
    {
        if (it->second->town_name_ == name)
        {
            nameVec.push_back(it->first);
        }
    }
    return nameVec;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    std::unordered_map<TownID,Town*>::const_iterator it;
    it = townMap.find(id);
    if (it != townMap.end())
    {
        it->second->town_name_ = newname;
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    std::vector<TownID> idVec = all_towns();
    std::sort(idVec.begin(), idVec.end(),
               [&](TownID a, TownID b) { return get_town_name(a) < get_town_name(b); });
    return idVec;

}

double eucDistOriSqr(Coord coord1, Coord coord2 = {0,0})
{
    double dx = (coord1.x-coord2.x);
    double dy = (coord1.y-coord2.y);
    double distSqr = dx*dx + dy*dy;
    return distSqr; // returnig square of the distance is more efficient
                    // and for sorting purposes its exactly same as returning square root
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    std::vector<TownID> idVec = all_towns();
    std::sort(idVec.begin(), idVec.end(),
               [&](TownID a, TownID b) {
                    return eucDistOriSqr(get_town_coordinates(a))
                            < eucDistOriSqr(get_town_coordinates(b)); });
    return idVec;
}

TownID Datastructures::min_distance()
{
    std::vector<TownID> idVec = towns_distance_increasing();
    return idVec.front();
}

TownID Datastructures::max_distance()
{
    std::vector<TownID> idVec = towns_distance_increasing();
    return idVec.back();
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    std::unordered_map<TownID,Town*>::const_iterator itV;
    std::unordered_map<TownID,Town*>::const_iterator itM;
    std::unordered_map<TownID,TownID>::const_iterator itV2;
    itV = townMap.find(vassalid);
    itM = townMap.find(masterid);
    itV2 = vassalMap.find(vassalid);
    if (itV != townMap.end() && itM != townMap.end() && itV2 == vassalMap.end())
    {

        vassalMap.insert(std::make_pair(vassalid,masterid));
        return true;
    }
    else
    {
        return false  ;
    }

}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    std::unordered_map<TownID,TownID>::const_iterator it;
    it = vassalMap.find(id);
    std::vector<TownID> vassalVec;
    if (it != vassalMap.end())
    {
        for(auto it=vassalMap.begin(); it!=vassalMap.end(); it++)
        {
            if (it->second == id)
            {
                vassalVec.push_back(it->first);
            }
        }
    }
    else
    {
        vassalVec.push_back(NO_TOWNID);
    }
        return vassalVec;
}

std::vector<TownID> Datastructures::taxer_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("taxer_path()");
}
 // optional
bool Datastructures::remove_town(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_town()");
}

std::vector<TownID> Datastructures::towns_nearest(Coord /*coord*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("towns_nearest()");
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("longest_vassal_path()");
}

int Datastructures::total_net_tax(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("total_net_tax()");
}
