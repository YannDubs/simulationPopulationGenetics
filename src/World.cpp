/*!
 * @file World.cpp
 * @author Yann Dubois et David CLeres
 * @date 28 Novembre 2015
 * @version 1.0
 * @brief description pool

*/
#include <cassert>

#include "World.hpp"

using namespace std;

World::World (vector<MetapoolDrep> const& setOfMetaPools)
: m_setOfMetapoolsDrep (setOfMetaPools)
{
	for (auto& element : m_setOfMetapoolsDrep)
	{
		element.setWorld (this);
	} 
}


//ASSEMBLE LES DEUX VECTEURS DE MIGRANTS VERS UN PAYS ENSEMBLE 
vector<unsigned int> World::imigrants (vector<unsigned int> const& pays1, vector<unsigned int> const& pays2) const
{
    assert(pays1.size() == pays2.size());
	vector<unsigned int> imigrants;
	for (size_t i(0); i < pays1.size(); i++) 
	{
		imigrants.push_back (pays1[i] + pays2[i]); 
	}
	return imigrants; 
}

//ON A DONNÉ UN POINTEUR SUR LE WOLRD DANS LES POOLDREP AINSI ILS SONT ACCES 
//ET VONT APPELER CETTE FONCTION POUR SAVOIR QUI C'EST QUI VIENT 
//case est le repeat dans lequel ou est 
vector<unsigned int> World::emigration (string const& nomPays, unsigned int const& nbCase)
{
	if (nomPays == "Congo") 
	{
		return imigrants (m_setOfMetapoolsDrep[CAMEROON].emigration(nbCase, 
						  migrantscameroon_congo),
						  m_setOfMetapoolsDrep[GABON].emigration (nbCase, 
						  migrantscongo_gabon));
	}
	else if (nomPays == "Cameroon") 
	{
		return imigrants (m_setOfMetapoolsDrep[GABON].emigration (nbCase,
						  migrantsgabon_cameroon), 
						  m_setOfMetapoolsDrep[CONGO].emigration (nbCase,
						  migrantscameroon_congo));
	}
	return imigrants (m_setOfMetapoolsDrep[CAMEROON].emigration (nbCase,
                    migrantsgabon_cameroon),
                    m_setOfMetapoolsDrep[CONGO].emigration (nbCase,
                    migrantscongo_gabon));
}
	
void World::affiche (std::ostream& output) const 
{
	output << "CONGOLEXISATION DE LA MALARIA: " << endl; 
	m_setOfMetapoolsDrep[CONGO].affiche (output); 
	output << endl; 
	output << "CAMEROONISATION DE LA MALARIA: " << endl; 
	m_setOfMetapoolsDrep[CAMEROON].affiche (output);
	output << endl; 
	output << "GABONENISATION DE LA MALARIA: " << endl; 
	m_setOfMetapoolsDrep[GABON].affiche (output); 
	output <<endl; 
}

void World::affiche (std::ostream& outputA, std::ostream& outputB, 
					 std::ostream& outputC) const 
{
	m_setOfMetapoolsDrep[CONGO].affiche (outputB); 
	outputB << endl; 
	m_setOfMetapoolsDrep[CAMEROON].affiche (outputA);
	outputA << endl; 
	m_setOfMetapoolsDrep[GABON].affiche (outputC); 
	outputC <<endl; 
}

void World::nextGenerationGeneral()
{
	for (auto& element : m_setOfMetapoolsDrep)
	{
		element.nextGenerationGeneral(); 
	}
}


