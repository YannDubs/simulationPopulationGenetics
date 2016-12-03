#ifndef METAPOOL_HPP
#define METAPOOL_HPP

#include <vector> 
#include <ostream> 

#include "Pool.h"

/*!
 * @file Metapool.hpp
 * @author Yann Dubois et David CLeres
 * @date 10 Novembre 2015
 * @version 1.0
 * @brief A Pool of Pools
 * 
 * This class is cainting several Pools, in order to be able to simulate 
 * the evolution of the same initial frequencies we had to create this class
*/ 

using namespace std; 

class Pool; 

/*!
 * @brief class containing all the alleles
 *
 * Class containing all the pools in order to simulate multiple repeats
 */
class Metapool
{
public:
		//On cree un tableaux de pool contenant au début tous les meme pool x et on applique nGenerations de fois nextGeneration() au repeats case du tableaux et on fait la moyenne pour voir si elle est constant
		/*!
		 * @brief constructor
		 * 
         * Must provide number of repeats *repeats*, vector containing the
		 * frequencies of the alleles *tabFreq* and sample size *nIndividus*.
		 * @param repeats number of simultaneous simulations must provide
		 * @param x name of the pool we want to take as a initial value (
		 * one pool si containing a vector with the allelic frequencies)
		 */
		Metapool (unsigned int const& repeats, Pool const& x); 
		
        /*!
		 * @brief default constructor
		 */
		Metapool() = default;
		
		/*!
		 * @brief Next Generation General
		 * 
		 * Simulates the next generation of allelic distribution, with 
		 * consideration of mutations, selection, etc..The considered phenonems
		 * are tested and considerated in the NextGeneration method of Pool.
		 */
		void nextGenerationGeneral();

		/*!
		 * @brief Average of Frequencies   
		 * 
		 * computes the mean of the frequencies of each repeats
		 * @param The indice of the allele in the table 
		 */
		double freqMoyenne (unsigned int const& indice) const; 
		
		/*!
		 * @brief Display/Output Fonction
		 * 
		 * Displays on Terminal or writes in the specified stream the output 
		 * frequences calculated by the method next generation.   
		 * @param The name of the stream output 
		 */
		void affiche (ostream& output) const;
    
        /*!
         * @brief bottleneck effect
         *
         * creates a natural disaster which randomly kills 90% of the population
         */
        void bottleneck();
		
		
	private: 
		vector<Pool> m_pools; 
	
}; 

#endif
