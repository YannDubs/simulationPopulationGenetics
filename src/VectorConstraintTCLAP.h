/*!
 * @file VectorConstraintTCLAP.h
 * @author Yann Dubois et David CLeres
 * @date 17 Novembre 2015
 * @version 1.0
 * @brief Constraint we want to apply to the inputs of the user.
 * 
 * Class that constraints the values of the vector to have a sum equal
 * to (more or less) 1. We say more or less because we are dealing with 
 * doubles and we chose to give and Interval of validity of the given frequencies. 
 * If the the sum of the frequences is not one, or one frequence is negativ 
 * we will not accept this input and tell the user that there is a problem. 
*/ 

#ifndef VECTORCONSTRAINTTCLAP_H
#define VECTORCONSTRAINTTCLAP_H

#include <string>
#include <vector>

using namespace std;
namespace TCLAP {
		
	/*!
	 * @brief  A Constraint that constrains the vector to have a sum equal to 1
	 * 
	 * Class that constraints the values of the vector to have a sum equal
	 * to (more or less) 1. We say more or less because we are dealing with 
	 * doubles and we chose to give and Interval of validity of the given frequencies. 
	 * If the the sum of the frequences is not one, or one frequence is negativ 
	 * we will not accept this input and tell the user that there is a problem. 
	 */
	class VectorConstraintTCLAP 
	{

	public:
		/*!
		 * @brief Virtual Destructor 
		 */
		 ~VectorConstraintTCLAP() {}

		/*!
		 * @brief Returns a description of the Constraint. 
		 */
		string description() const;

		/*!
		 * @brief Returns the short ID for the Constraint.
		 */
		string shortID() const;

		/*!
		 * @brief check 
		 * 
		 * The method used to verify that the value parsed from the command
		 * line meets the constraint.
		 * @param Tab The value that will be checked.In this case it is the 
		 * vector with our frequences and we will test if the sum is one and 
		 * if no allele has a negativ frequence. 
		 */
		bool check (vector<double> const& Tab) const;
		
	};

	bool VectorConstraintTCLAP::check(vector<double> const& Tab) const
	{
		double sommeFrequence (0);
		bool isFreq (true);
		for (auto const& frequence : Tab)
		{
			sommeFrequence += frequence;
			
			//regarde si frequence est pas négative
			if (frequence <= 0)
			{
				isFreq = false;
			}
		}
		//DONNE UN INTERVALLE DE TOLÉRANCE POUR LA VALEUR DE LA SOMME DES 
		//DES FREQUENCES COMME ON NE PEUT PAS DIRECTEMENT COMPRER DES DOUBLES ET 
		//ET QUE NOUS AVONS PAS TROUVÉ UNE FONCTION PREDEFINIE 
		bool isOne (sommeFrequence > 0.99999999999 && sommeFrequence < 1.0000000001); 
		
		return !(!isOne || !isFreq); 
	}

	string VectorConstraintTCLAP::shortID() const
	{
		string shortID ("entier positif non nul");
		return shortID;
	}

	//Type de l'exception
	string VectorConstraintTCLAP::description() const
	{
		string description ("les fréquences doivent être des entiers positifs non nuls avec comme somme 1");
		return description;	
	}
}

#endif
