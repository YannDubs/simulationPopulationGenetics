#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector> 
#include <string> 
 
using namespace std; 

#include "MetaPoolDrep.hpp"
#include "PoolDrep.h" 

/*!
 * @file World.hpp
 * @author Yann Dubois & David Cleres
 * @date 28 november 2015
 * @version 1.0
 * @brief generates a pool of alleles 
 * 
 * MetapoolDrep  is in this case a country and we are simulating the evolution
 * of anemia in Cameroon, Gaboon and Congo. The World is a set of 3 
 * MetapoolsDrep. (The Metapools is itself containing the number of test repeats
 * of the sample simulation on the same sample. 
*/

class PoolDrep; 
class MetapoolDrep;

//on doit pas utilisé la migration annuelle mais la migration durant une generation
// d'après wiki entre 22 et 32 ans mais vu qu'on est dans des pays moins développé
// 22 est une meilleure approximation
const int anneeGeneration (22);
const int migrantscongo_gabon (23 * anneeGeneration);
const int migrantsgabon_cameroon (240 * anneeGeneration);
const int migrantscameroon_congo (50 * anneeGeneration);

enum Pays {
   CONGO,
   CAMEROON,
   GABON,
};

/*!
 * @brief generator class
 *
 * Class containing multiple countries (metapools)
 */
class World 
{
	public: 

		//CONSTRUCTEUR
    /*!
     * @brief constructor
     *
     * Must provide vector containing the
     * multiple metapools *setOfMetaPools*
     * @param setOfPools vector of the different countries (metapools)
     */
		World (std::vector<MetapoolDrep> const& setOfMetaPools);
		
		//REDISTRIBUTION DES MIGRANTS (à la fois pour les émigrant que pour les 
		//migrants
		//FAIT LA SOMME DES DEUX QUI ARRIVE des deux autres pays
    /*!
     * @brief Sums the migrants
     *
     * computes the sum of the differents migrants depending on the alleles
     * @return the array of the sum of migrants
     */
		vector<unsigned int> imigrants (vector<unsigned int> const& pays1, vector<unsigned int> const& pays2) const;
    /*!
     * @brief gives the migrants of a certain countries
     *
     * Computes randomly the migrants going from a certain country *nomPays* in a certain repeat known by the *nbCase*
     * cell in which the repeat is contained in the metapool, to an other country
     * @param nomPays the country from which they are leaving
     * @param nbCase the repeat we are lookning at
     * @return the array of the migrants from a country to an other
     */
		vector<unsigned int> emigration (string const& nomPays, unsigned int const& nbCase);
    /*!
     * @brief Displays the calculed frequencies
     *
     * Displays in the output file the frenquencies of each allele
     * @param output output file must provide
     */
		void affiche (std::ostream& output) const;
    /*!
     * @brief Displays the calculed frequencies
     *
     * Displays in the output file the frenquencies of each allele
     * @param outputA  output file for Cameroon must provide
     * @param outputB  output file for Congo must provide
     * @param outputC  output file for Gabon must provide
     */
		void affiche (std::ostream& outputA, std::ostream& outputB, 
					  std::ostream& outputC) const;
    /*!
     * @brief computes new generation
     *
     * Computes the new frequencies of each allele in each pool
     */
		void nextGenerationGeneral();
	
	private:
		std::vector<MetapoolDrep> m_setOfMetapoolsDrep; 
		
}; 

#endif
