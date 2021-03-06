/* Agent.h */

#ifndef AGENT
#define AGENT

#include "repast_hpc/AgentId.h" //enables agent id structures to be implemented
#include "repast_hpc/SharedContext.h"
#include "repast_hpc/SharedNetwork.h"
#include "Network.h"
#include "repast_hpc/initialize_random.h"

/* Agents */
class RepastHPCAgent
{

private:
    repast::AgentId id_;
    double c;
    double total;
    
    int age; // Age of the agent expressed as an integer
    double commuteDist; // Distance agent must commute to work
    double socNorm; // The societal normality of cycling as perceived by the agent
    string region; // The region in which the agent resides. Four regions are modelled.

    double des_age; // The desire to cycle based on the age of the agent
    double des_commuteDist; // The desire to cycle based on the distance of commute
    double des_socNorm; // The desire to cycle based on the cycle state of agents neighbours
    double des_region; // The desire to cycle based on the region the agent
    double des_popHealth; // The desire to cycle based on the health of the populous in which the agent resides. Value between 0 and 1
    double des_popSafety; // The desire to cycle based on the safety of cycling as perceived as the populous. Value between 0 and 1

    bool cycles; // Agent binary state output - whether agent cycles
    

public:
    // Agent constructors
    RepastHPCAgent(repast::AgentId id);
    RepastHPCAgent(){}
    RepastHPCAgent(repast::AgentId id, double newC, double newTotal);

    ~RepastHPCAgent(); //agent destructor

    /* Required Getters */
    virtual repast::AgentId& getId()
    {
        return id_;
    }
    virtual const repast::AgentId& getId() const
    {
        return id_;
    }

    /* Agent state variable getters  */
    double getC()
    {
        return c;
    }
    double getTotal()
    {
        return total;
    }
    int getAge()
    {
        return age;
    }
    double getcommuteDist()
    {
         return commuteDist;
    }
    double getSocNorm()
    {
         return socNorm;
    }
    string getRegion()
    {
         return region;
    }

    /* Setter */
    void set(int currentRank, double newC, double newTotal);

    /* Actions */
    bool cooperate(); // Will indicate whether the agent cooperates or not; probability determined by = c / total
    void play(repast::SharedNetwork<RepastHPCAgent,
              ModelCustomEdge<RepastHPCAgent>,
              ModelCustomEdgeContent<RepastHPCAgent>,
              ModelCustomEdgeContentManager<RepastHPCAgent> > *network);

};

/* Serializable Agent Package */
struct RepastHPCAgentPackage
{

public:
    int    id;
    int    rank;
    int    type;
    int    currentRank;
    double c;
    double total;

    /* Constructors */
    RepastHPCAgentPackage(); // For serialization
    RepastHPCAgentPackage(int _id, int _rank, int _type, int _currentRank, double _c, double _total);

    /* For archive packaging */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & rank;
        ar & type;
        ar & currentRank;
        ar & c;
        ar & total;
    }

};


#endif
