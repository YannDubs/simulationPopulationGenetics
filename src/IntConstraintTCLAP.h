/*!
 * @file IntConstraintTCLAP.h
 * @author Yann Dubois et David CLeres
 * @date 09 Novembre 2015
 * @version 1.0
 * @brief Be different then 0
*/ 

#include <string>
#include "../tclap/include/tclap/Constraint.h"

using namespace TCLAP;
using namespace std;

/*!
 * @brief Constraint is to be different and greater than 0. 
 *
 * A Constraint that constrains the Arg to a not 0 or less value.
 */
class IntConstraintTCLAP : public Constraint<int>
{
public:
    /**
     * Virtual destructor.
     */
    virtual ~IntConstraintTCLAP() {}
    
    /**
     * Returns a description of the Constraint.
     */
    virtual string description() const;
    
    /**
     * Returns the short ID for the Constraint.
     */
    virtual string shortID() const;
    
    /*!
     * @brief Check is the constraint is meeted. 
     * The method used to verify that the value parsed from the command
     * line meets the constraint.
     * @param value The value that will be checked.In this case an int. 
     */
    virtual bool check (int const& value) const;   
};

bool IntConstraintTCLAP::check (int const& val) const
{
    return (val > 0); 
}

string IntConstraintTCLAP::shortID() const
{
    string shortID ("entier positif non nul ");
    return shortID;
}

string IntConstraintTCLAP::description() const
{
    string description ("ne peut pas être égal 0");
    return description;
}
