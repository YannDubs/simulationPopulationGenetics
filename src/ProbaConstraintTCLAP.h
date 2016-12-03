/*!
 * @file ProbaConstraintTCLAP.h
 * @author Yann Dubois et David CLeres
 * @date 17 Novembre 2015
 * @version 1.0
 * @brief Constraint we want to apply to the inputs of the user. 
 * 
 * Class that constraints the values of the frequences given by the user. 
 * This function is for example use for testing that the probability of 
 * mutation is between 0 and 1. 
*/ 
class ProbaConstraintTCLAP : public Constraint<double>
{
public:
    /**
     * Virtual destructor.
     */
    virtual ~ProbaConstraintTCLAP() {}
    
    /**
     * Returns a description of the Constraint.
     */
    virtual string description() const;
    
    /**
     * Returns the short ID for the Constraint.
     */
    virtual string shortID() const;
    
    /*!
     * @brief Check
     * The method is used to verify that the value parsed from the command
     * line meets the constraint.In this case that the value of the given 
     * frequence is between 0 and 1. 
     * @param value - The value that will be checked.
     */
    virtual bool check (double const& value) const;
};

bool ProbaConstraintTCLAP::check (double const& val) const
{
    return (val > 0 && val < 1); 
}

string ProbaConstraintTCLAP::shortID() const
{
    string shortID ("réel compris entre 0 et 1");
    return shortID;
}

string ProbaConstraintTCLAP::description() const
{
    string description ("doit être compris entre 0 et 1");
    return description;
}
