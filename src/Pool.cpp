/*!
 * @file Pool.cpp
 * @author Yann Dubois et David CLeres
 * @date 10 Novembre 2015
 * @version 1.0
 * @brief description pool
*/ 

#include <string>
#include <random>
#include <iomanip>
#include <vector> 
#include <iostream>

#include "Pool.h"

using namespace std;

//CONSTRUCTEUR AVEC MUTATIONS ou par defaut sans mutation 
Pool::Pool (vector<double> const& tabFreq, unsigned int const& nIndividu, double const& tauxMutation, vector<double> const& fitness)
: m_nAllele (tabFreq.size())
, m_tabFreq (tabFreq)
, m_nIndividu (nIndividu)
, m_tauxMutation (tauxMutation)
, m_fitness (fitness)
{}

//METHODES

void Pool::nextGenerationGeneral()
{
    if (!m_fitness.empty())
    {
        double sum_FreqTimesFitness (0);
        for (size_t i (0); i < m_tabFreq.size(); ++i)
        {
            sum_FreqTimesFitness += (m_tabFreq[i] * m_fitness[i]);
        }
    
        sum_FreqTimesFitness += 1;
    
        for (size_t j (0); j < m_tabFreq.size(); ++j)
        {
            m_tabFreq[j] = m_tabFreq[j] * ((1 + m_fitness[j]) / (sum_FreqTimesFitness));
        }
    }
    
	//itérateur sur le tableaux (begin() et end() ne sont pas les indice de début et fin du tableau
	discrete_distribution<int> alleleGenerator (m_tabFreq.begin(), m_tabFreq.end());
	random_device rd;
	mt19937 rng = mt19937 (rd());
	int allele (0);
	
	if (m_tauxMutation != 0)
	{
		vector<double> newTabFreq (m_nAllele, m_tauxMutation / (m_nAllele - 1));
    
		if (m_nIndividu == 0)
		{
			throw 0;
		}
		for (size_t i (0); i < m_nIndividu * 2; ++i)
		{
			allele = alleleGenerator (rng);
			newTabFreq[allele] += (1.0/(m_nIndividu * 2)) * (1 - (m_tauxMutation * m_nAllele / (m_nAllele - 1)));
		}
		m_tabFreq = newTabFreq;
	}
    //fitness ou normal
	else
	{
		vector<double> newTabFreq (m_nAllele);
		
		if (m_nIndividu == 0)
		{
			throw 0; 
		}
		for (size_t i = 0; i < m_nIndividu*2; ++i)
		{
			allele = alleleGenerator (rng);
			newTabFreq[allele] += (1.0 / (m_nIndividu * 2));
		}
		m_tabFreq = newTabFreq;
	}
}

void Pool::affiche(std::ostream& output) const
{
	output << "\t"; 
	for (size_t i (0); i < m_nAllele; ++i)
	{
		output << fixed << setprecision (3) << m_tabFreq[i] << "|";
	}
}
   
vector<double> Pool::getTab() const
{
	return m_tabFreq; 
}


void Pool::bottleneck()
{
    // on ne garde que 10% de la pop (reste un int car stocke en int)
    m_nIndividu *= 0.1;
    if (m_nIndividu == 0)
    {
        m_nIndividu = 1;
    }
}

Pool::~Pool()
{}
