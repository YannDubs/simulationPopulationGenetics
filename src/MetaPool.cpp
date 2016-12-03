#include <iomanip>      // std::setw

#include "MetaPool.hpp" 

/*!
 * @file Metapool.cpp
 * @author Yann Dubois et David CLeres
 * @date 10 Novembre 2015
 * @version 1.0
 * @brief description Metapool
*/ 

Metapool::Metapool (unsigned int const& repeats, Pool const& x)
: m_pools (repeats)
{
	for (auto& element : m_pools)
	{
		element = x; 
	}
}

void Metapool::nextGenerationGeneral()
{
	for (auto& element : m_pools) 
	{
		element.nextGenerationGeneral(); 
	}
} 

double Metapool::freqMoyenne (unsigned int const& indice) const 
{
	double somme (0); 
	for (auto const& element : m_pools) 
	{
		somme += element.getTab()[indice]; 	
	}
	return somme / m_pools.size(); 
}

void Metapool::affiche (std::ostream& output) const 
{	
	for (size_t i (0); i < m_pools.size(); i++) 
	{
		output << setw(5) << setprecision(4);
		m_pools[i].affiche(output);
	}
}

void Metapool::bottleneck ()
{
    for (auto& pool : m_pools)
    {
        pool.bottleneck();
    }
}
