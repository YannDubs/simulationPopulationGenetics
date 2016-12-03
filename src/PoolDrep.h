#ifndef POOLDREP_H
#define POOLDREP_H

#include "Pool.h"
#include "World.hpp"
/*!
 * @file PoolDrep.h
 * @author Yann Dubois & David Cleres
 * @date 10 november 2015
 * @version 1.0
 * @brief Generates a pool of alleles using the sickle cell anemia.  
 * This is class inherits of pool and uses the sickle cell model, based on
 * real values. 
 * 
 * Kind of pool (inherits of pool) and that uses the sickle cell anemia
 * model
*/ 

class World;  

/*!
 * @brief generator class PoolDrep
 * 
 * Generates a pool of alleles affected by the sickle cell anemia.  
 * This is class inherits of pool and uses the sickle cell model, based on
 * real values. 
 */
class PoolDrep: public Pool 
{
public: 
	/*!
	 * @brief Constructor
	 * 
	 * Must provide vector containing the frequencies of the alleles 
	 * *tabFreq*, sample size *nIndividus*, the probability of this pool 
	 * to be affected by the malaria desease *probaMalarya* and the name 
	 * of the country *nomPays* 
	 * @param tabFreq Vector containing the frequencies of the alleles must provide
	 * @param nIndividus Sample size must provide 
	 * @param probaMalarya Probability of being affected by the malaria desease
	 * in this country. 
	 * @param nomPays Name of the country (Congo, Cameroon or Gaboon) 
	 */
	PoolDrep (std::vector<double> const& tabFreq, unsigned int const& nIndividu,
			  double const& probaMalarya,
			  string const& nomPays);
	/*!
	 * @brief Default Constructor
	 */		  
	PoolDrep() = default; 
 
	/*!
	 * @brief Calculates and affects the new freqencies of each alleles 
	 * 
	 * Writes the next generation (i.e. the new frequences) of each
	 * allele in the m_tabFreq vector, considering either the probability 
	 * of being affected by malaria and the probability of being affected 
	 * by the Sickle cell anemia. There is a prooved correlation between 
	 * the survival of anemia affected pateint to the malaria desease. (This
	 * patients are use to deal with less oxygen provided because of their 
	 * deficient Erythrocytes.  
	 */
	void nextGenerationGeneral() override;
	
	/*!
	 * @brief alleles of the emigrants
	 * 
	 * Returns a vector with the number of the alleles of each groups of
	 * emigrants of one country. The function also supresses the alleles 
	 * of gone people from the m_tabFreq vector (our vector containing all 
	 * the alleles of the Pool. This vector of migrants is given to the World. 
	 * A further function in World is responsable of the repartition of this 
	 * migrants in their new country. (The number of migrants is fixed by a constant 
	 * in the world where this function is called. 
	 * @param nMigrant Total amount of persons to take in m_tabFreq. 
	 * (BE CAREFUL: the table is in frequencies and we want an amount of persons)  
	 * @return vector of vector of ints cintain the realamout of alleles 
	 * migrating from one country to the others.  
	 */ 
	vector<unsigned int> emigration (unsigned int const& nMigrant);
	
	/*!
	 * @brief Gives the World   
	 * 
	 * When we create our MetaPoolDrep we can't know in which world 
	 * we are because a World if selfdefined by a vector of MetaPoolDreps. 
	 * We have decided to first create the World and then to give the 
	 * adress of the studied world by using by setter function. This function
	 * is used in the constructor of World class. 
	 * @param ptr Pointer on the world  
	 */
	void setWorld (World* ptr); 
	
	/*!
	 * @brief Gives an ID by giving the slot in the vector of Pools in 
	 * which we are in order to know which country we are supposed to 
	 * symbolise.    
	 * 
	 * When we create our table MetaPoolDrep in world we can't know in advance 
	 * which position in this table of MetaPools we are occuping but also 
	 * we don't know which repeat of the experiment we are. This function 
	 * enables us to know this. 
	 * @param caseMeta Slot of storage in the vector of Pools  
	 */
	void setCaseMetapool (int const& caseMeta);
    
    /*!
	 * @brief Virtual destructor because PoolDrep inheritates of Pool. And 
	 * We are using vectors.  
	 */
    virtual ~PoolDrep();

private:

	double m_probaMalarya;
	World* m_ptrWorld;
	string m_nomPays;
	unsigned int m_caseMetaPool;

};

#endif
