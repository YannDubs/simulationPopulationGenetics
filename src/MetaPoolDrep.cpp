#include <iomanip>      // std::setw

#include "MetaPoolDrep.hpp" 

using namespace std; 

/*!
 * @file MetapoolDrep.cpp
 * @author Yann Dubois et David CLeres
 * @date 1 December 2015
 * @version 1.0
 * @brief description MetapoolDrep: We have chosen not to use pointers on Pools
 * which would have alowed us to recycle the Metapool class and only add 
 * a few method in Pool. But using pointeurs is much more expensives 
 * in terms of memory cost that we choose to do 2 different classes. 
*/ 

MetapoolDrep::MetapoolDrep (unsigned int const& repeats, PoolDrep const& pool)
: m_poolsDrep (repeats)
{
	for (size_t i (0); i < m_poolsDrep.size(); i++)
	{
		m_poolsDrep[i] = pool; 
		m_poolsDrep[i].setCaseMetapool (i); 
	}
}

void MetapoolDrep::nextGenerationGeneral()
{
	for (auto& element : m_poolsDrep) 
	{
		element.nextGenerationGeneral(); 
	}
} 

vector<unsigned int> MetapoolDrep::emigration (unsigned int const& caseMetaPool, 
											   unsigned int const& nMigrant)
{
    return m_poolsDrep[caseMetaPool].emigration (nMigrant);
}

double MetapoolDrep::freqMoyenne (unsigned int const& indice) const 
{
	double somme (0);
	for (auto const& element : m_poolsDrep) 
	{
		somme += element.getTab()[indice]; 	
	}
	return somme / m_poolsDrep.size(); 
}

void MetapoolDrep::affiche (std::ostream& output) const 
{	
	for (size_t i (0); i < m_poolsDrep.size(); i++) 
	{
		output << setw (5) << setprecision (4);
		m_poolsDrep[i].affiche (output);
	}
}

void MetapoolDrep::setWorld (World* ptr) 
{
	for (auto& element : m_poolsDrep)
	{
		element.setWorld (ptr); 
	}
}
