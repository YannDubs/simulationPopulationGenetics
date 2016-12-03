#ifndef METAPOOLDREP_HPP
#define METAPOOLDREP_HPP

#include <vector> 
#include <ostream> 

#include "PoolDrep.h"

/*!
 * @file MetapoolDrep.hpp
 * @author Yann Dubois et David CLeres
 * @date 1 December 2015
 * @version 1.0
 * @brief A Pool of Drepanocitose Pools
 * 
 * This class is cainting several Pools of genes suffering of the genetic 
 * desease Drepanocitosis. In order to be able to simulate. We will as 
 * in MetaPool simulate the evolution of the frequences for nGenerations. 
 * the evolution of the same initial frequencies we had to create this class
*/ 

using namespace std; 

class PoolDrep; 
class World; 

class MetapoolDrep
{
	public: 
		/*!
		 * @brief Constructor of Class MetaPoolDrep
		 * 
		 * Must provide number of repeats *repeats*, PoolDrep which is our
		 * Pool of alleles in the case of a simulation of malaria evolution
		 * in Gabon, Congo & Cameroon  *pool*.
		 * @param repeats number of simultaneous simulations must provide
		 * @param pool name of the pool we want to study in our simulation
		 * (one pool is containing a vector with the allelic frequencies)
		 */
		MetapoolDrep (unsigned int const& repeats, PoolDrep const& pool); 
		
		/*!
		 * @brief default constructor
		 */
		MetapoolDrep() = default;
		
		/*!
		 * @brief alleles of each migrants
		 * 
		 * Function which computes the alleles of the migration population
		 * and at the same time deletes this alleles from the home countries 
		 * by calling the emigration function of each PoolDrep
		 * @param nMigrants The number of migrants for these countries 
		 * @param m_caseMetaPool The slot in which the watend pool is 
		 * @return vector of vector of the amount of each alleles in each 
		 * country. 
		 */
		vector<unsigned int> emigration (unsigned int const& m_caseMetaPool, unsigned int const& nMigrant);

		/*!
		 * @brief Display/Output Fonction
		 * 
		 * Displays on Terminal or writes in the specified stream the output 
		 * frequences calculated by the method next generation.   
		 * @param output The name of the output stream.  
		 */
		void affiche (ostream& output) const;

		/*!
		 * @brief Average of Frequencies   
		 * 
		 * Displays on Terminal or writes in the specified stream the output 
		 * frequences calculated by the method next generation.   
		 * @param indice The indice of the allele in the table 
		 * @return double containing the value of the average frequence of 
		 * each allele in the population. 
		 */
		double freqMoyenne (unsigned int const& indice) const;

		/*!
		 * @brief Next Generation General
		 * 
		 * Simulates the next generation of allelic distribution, with 
		 * consideration of the presence of a genetic faillure called 
		 * Drepanocitosis.The considered phenonems are tested and 
		 * considerated in the NextGeneration method of Pool.
		 */
		void nextGenerationGeneral();
		
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
		
	private: 
		
		vector<PoolDrep> m_poolsDrep; 
}; 

#endif
