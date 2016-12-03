#include <random>
#include <string>
#include <cassert>

#include "PoolDrep.h"

/*!
 * @file PoolDrep.cpp
 * @author Yann Dubois et David CLeres
 * @date 10 Novembre 2015
 * @version 1.0
 * @brief description pool
c
*/ 

using namespace std;

//CONSTRUCTEUR AVEC MUTATIONS ou par defaut sans mutation 
PoolDrep::PoolDrep (vector<double> const& tabFreq,
					unsigned int const& nIndividu,
					double const& probaMalarya,
					string const& nomPays)
: Pool (tabFreq, nIndividu)
, m_probaMalarya (probaMalarya) 
, m_nomPays (nomPays)
{
    m_ptrWorld = nullptr;
}

//METHODS 

void PoolDrep::nextGenerationGeneral()
{
	//ici on calcule les probabilités d'avoir un allèle normal et 
	//un allèle anémique et on les stockes dans le tableau => on change 
	//notre tableau.
	//NOTE: tabFreq[0] = normal et tabFreq[1] = anémique
	double p (m_tabFreq[0]);
	double q (m_tabFreq[1]);
	m_tabFreq[0] = (1 - m_probaMalarya) * (p * p) + p * q;
	m_tabFreq[1] = 0.3 * (q * q) + p * q;

	//Itérateur sur le tableaux (ATTENTION: begin() et end() ne sont pas 
	//les indice de début et fin du tableau
	discrete_distribution<int> alleleGenerator (m_tabFreq.begin(), m_tabFreq.end());
	random_device rd;
	mt19937 rng = mt19937 (rd());
	int allele (0);
	
	vector<double> newTabFreq (m_nAllele);
	
	if (m_nIndividu == 0)
	{
		throw 0; 
	}
	for (size_t i (0); i < m_nIndividu * 2; ++i)
	{
		allele = alleleGenerator (rng);
		newTabFreq[allele] += (1.0 / (m_nIndividu * 2));
	}

	m_tabFreq = newTabFreq;

    assert (m_ptrWorld != nullptr);
    vector<unsigned int> imigrant (m_ptrWorld->emigration (m_nomPays, m_caseMetaPool));
	
	for (size_t j (0); j < m_tabFreq.size(); ++j)
	{
		m_tabFreq[j] += (imigrant[j] / (m_nIndividu*2));
	}
}

vector<unsigned int> PoolDrep::emigration (unsigned int const& nMigrant)
{
	discrete_distribution<int> alleleGenerator (m_tabFreq.begin(), m_tabFreq.end());
	random_device rd;
	mt19937 rng = mt19937 (rd());
	int allele (0);
	
	vector<unsigned int> newTabFreq (m_nAllele, 0);
	
	if (m_nIndividu == 0)
	{
		throw 0; 
	}
    
	for (size_t i (0); i < nMigrant * 2; ++i)
	{
		allele = alleleGenerator (rng);
		m_tabFreq[allele] -= (1.0 / (m_nIndividu * 2));
		newTabFreq[allele] += (1.0);
	}
    
	return newTabFreq;
}

void PoolDrep::setWorld (World* ptr)
{
	m_ptrWorld = ptr; 
}

void PoolDrep::setCaseMetapool (int const& caseMeta)
{
	m_caseMetaPool = caseMeta; 
}

PoolDrep::~PoolDrep()
{}
