/*!
 * @file FitnessConstraintTCLAP.h
 * @author Yann Dubois et David CLeres
 * @date 29 Novembre 2015
 * @version 1.0
 * @brief constraint value greater than -1
 * 
 * Creates a class that constraints the values of the fitness between -1 
 * and infinity
*/ 

#ifndef FITNESSCONSTRAINTTCLAP_H
#define FITNESSCONSTRAINTTCLAP_H

#include <string>
#include "../tclap/include/tclap/Constraint.h"

using namespace TCLAP;
using namespace std;

/*!
 * @brief Constraint -1 < x
 *
 * A Constraint that constrains the argument to be a value higher than 1.
 */
class FitnessConstraintTCLAP : public Constraint<double>
{
public:
    /**
     * Virtual destructor.
     */
    virtual ~FitnessConstraintTCLAP() {}
    
    /**
     * Returns a description of the Constraint.
     */
    virtual string description() const;
    
    /**
     * Returns the short ID for the Constraint.
     */
    virtual string shortID() const;

    /*!
	 * @brief check
	 *
	 * The method used to verify that the value parsed from the command
     * line meets the constraint. This method overrides the method in Constraint class.
     * @param value The value that will be checked. In this case a double
     * which represents the value of the given fitness. (given by the user)  
	 */
    virtual bool check (double const& value) const; 
};

bool FitnessConstraintTCLAP::check (double const& val) const
{
    return (val > -1); 
}

string FitnessConstraintTCLAP::shortID() const
{
    string shortID ("réel plus grand que -1");
    return shortID;
}

string FitnessConstraintTCLAP::description() const
{
    string description ("doit être plus grand que -1");
    return description;
}

#endif
