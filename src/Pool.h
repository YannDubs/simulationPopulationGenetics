#ifndef POOL_H
#define POOL_H

#include <vector>
#include <ostream> 

/*!
 * @file Pool.h
 * @author Yann Dubois & David Cleres
 * @date 10 november 2015
 * @version 1.0
 * @brief generates a pool of alleles 
 * 
 * Pool is the heart class of our project. Pool means "the pool of genes" 
 * we are simulation in this class how the number of alleles are mutating, 
 * being selected or simply how is their evolution in a Wright-Fisher 
 * Simulation
*/ 

/*!
 * @brief class containing all the alleles
 * 
 * Class containing all the alleles of the population at a certain time
 */
class Pool 
{
	
public: 

	//CONSTRUCTEURS 
	
	//CREATION D'UN OBJET DE TYPE POOL QUI PEUT ETRE SOUS INFLUENCE DE
	//LA SELECTION (DANS CE CAS ON DOIT DONNER UN TABLEAUX MAIS QUI PEUT 
	//AUSSI MUTER DANS CE CAS ON DOIT FOURNIR UN TAUX DE MUTATION 
	/*!
	 * @brief constructor
	 * 
	 * Must provide vector containing the
	 * frequencies of the alleles *tabFreq*, sample size *nIndividus*,
	 * the fitness (natural advantage of one gene in comparison to the other
	 * genes) *fitness* and the mutation rate *tauxMutation* 
	 * @param fitness evolutive advantage of the allele in comparison to 
	 * the others (optional)
	 * @param tabFreq vector containing the frequencies of the alleles must provide
	 * @param nIndividus sample size must provide
	 * @param tauxMutation Mutation rate of a specific Allele (optional) 
	 */
	Pool (std::vector<double> const& tabFreq, unsigned int const& nIndividu,
		  double const& tauxMutation = 0, 
		  std::vector<double> const& fitness = std::vector<double> ());
	
	/*!
	 * @brief default constructor
	 * 
	 * Necessary since we work with vectors for which the initialisation
	 * of the type containing the vector must have a default constructor
	 */
	Pool() = default; 

	//CALCULE LA PROCHAINE GENERATION 
	/*!
	 * @brief new freqencies of alleles 
	 * 
	 * Computes the next generation (i.e. the new frequences) of each
	 * allele consideration either: 
	 * 
	 * - The easiest case: Simulates the next generation of allelic distribution, with 
	 * no consideration of mutations, selection, etc. 	 
	 * Simplest simulation in term of concepts.  
	 * - Considering Mutations:  Simulates the next generation of allelic distribution, with 
	 * no consideration of selection but with consideration. Input 
	 * need to provide the mutation rate.   
	 * - Considering selection: Simulates the next generation of allelic distribution, with 
	 * no consideration of mutation but with consideration of selection.
	 * Input need to provide the table of fitness. (Provide the fitness
	 * one by one with the prefix -s)   
	 */
	virtual void nextGenerationGeneral();

	//AFFICHE LES PROBABILITES CALCULES DE LA PROCHAINE GENERATION 
	/*!
	 * @brief Displays the calculed frequencies 
	 * 
	 * Displays in the output file the frenquencies of each allele
	 * @param *output* : output file must provide
	 */
	void affiche(std::ostream& output) const;

	//GETTEURS
	/*!
	 * @brief Allows to access the number of Alleles  
	 * 
	 * Getteur fonction allowing the acces to the tab containning the 
	 * frequences of each allele: in order to do a gtest on the mean 
     * @return the array of frequencies
	 */
	std::vector<double> getTab() const;
    
    /*!
     * @brief bottleneck effect
     *
     * creates a natural disaster which randomly kills 90% of the population
     */
    void bottleneck();
    
    /*!
     * @brief destructor
     */
    virtual ~Pool();
	 
	 
protected:
    unsigned int m_nAllele; 
    std::vector<double> m_tabFreq;
    unsigned int m_nIndividu;
    double m_tauxMutation;
    std::vector<double> m_fitness; 
};

#endif
