// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

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

std::vector<TownID> Datastructures::find_towns(const Name &/*name*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("find_towns()");
}

bool Datastructures::change_town_name(TownID /*id*/, const Name &/*newname*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("change_town_name()");
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    // Replace the line below with your implementation
    throw NotImplemented("towns_alphabetically()");
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Replace the line below with your implementation
    throw NotImplemented("towns_distance_increasing()");
}

TownID Datastructures::min_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("min_distance()");
}

TownID Datastructures::max_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("max_distance()");
}

bool Datastructures::add_vassalship(TownID /*vassalid*/, TownID /*masterid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_vassalship()");
}

std::vector<TownID> Datastructures::get_town_vassals(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("get_town_vassals()");
}

std::vector<TownID> Datastructures::taxer_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("taxer_path()");
}

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
