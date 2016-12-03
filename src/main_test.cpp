#include "gtest/gtest.h"
#include "Pool.h"
#include "MetaPool.hpp"
#include "VectorConstraintTCLAP.h" 
#include "IntConstraintTCLAP.h" 
#include "ProbaConstraintTCLAP.h"
#include "FitnessConstraintTCLAP.h"

/*!
 * @file main_test.cpp
 * @author Yann Dubois et David Cleres
 * @date 28 november 2015
 * @version 1.0
 * @brief Tests on the simulation of the wright fisher model
 *
 * test the programm: NB: cannot tust much because all our test are made in Tclap
 */

/*!
 * @brief Number of individuals tested  
 * 
 * Tests if the number of individus *m_nIndividus* is not smaller or equal 
 * then 0. 
 */
TEST (Pool, nIndividus)
{
	Pool x({0.5,0.3,0.2},3);
	//nombre d'inidividus null
	Pool y ({0.5,0.3,0.2},0);
	ASSERT_NO_THROW (x.nextGenerationGeneral()); 
	ASSERT_THROW (y.nextGenerationGeneral(),int); 
}

//On teste si la la moyenne de frequences est constante avec repats = nombre de d'expériences simulranée 
/*!
 * @brief Check constance of the average frequencies  
 * 
 * Assures that the average frequence of each allele stay constant during 
 * the generations. We gave an intervalle of 0.01 after *nGenerations*. This 
 * test fails sometimes since we choose to give a very small confidence intervall
 * for the distance to the theoric average value of a specific allele.  
 */
TEST (Pool, Moyenne_Constante) 
{
	unsigned int nGenerations (100); 
	unsigned int nIndividus (500); 
	Pool x ({0.5,0.3,0.2}, nIndividus);
	int repeats (500);
	Metapool y (repeats, x); 
	//la moyenne des frequence finale doit être égal aux frequence intiale puisque rien ne change 
	double moyFrequn (x.getTab()[0]); 
	double moyFreqdeux (x.getTab()[1]); 
	double moyFreqtrois (x.getTab()[2]); 
	double abs_error (0.02);
	
	//On fait une similation nGeneration 
	for (unsigned int i (0); i < nGenerations; ++i)
	{
		y.nextGenerationGeneral(); 
	} 
	
	EXPECT_NEAR(moyFrequn, y.freqMoyenne (0), abs_error);
	EXPECT_NEAR(moyFreqdeux, y.freqMoyenne (1), abs_error);
	EXPECT_NEAR(moyFreqtrois, y.freqMoyenne (2), abs_error);
}

/*!
 * @brief Check If the sum is one  
 * 
 * Tests if the the sum is equal to one, that we have no negative or null 
 * values. (make the same test then check_THROW_TESTING but does test the 
 * return and not the assertions  
 */
//TEST SI LA SOMME DES FREQUENCE DU TABLEAUX DOIT BIEN VALOIR UN ET 
//QUE SI CE N'EST PAS LE CAS ALORS ON RETOURNE UN ECHEC 
//CHECK TEST DEJA SI IL Y A UENE FREQUENCE NEGATIVE DONC IL Y A JUSTE A 
//AJOUTER UN VECTOR AVEC UNE VALEUR NEGATIVE POUR LE TEST 
TEST (VectorConstraintTCLAP, sum_one_and_null_or_negativ)
{
	vector <double> x({0.5,0.3,0.2});
	vector <double> y ({0.3,1.2, 2.2}); 
	vector <double> negatif ({0.3,1.2, - 2.2}); 

	TCLAP::VectorConstraintTCLAP ConstraintSum1; 
	
	EXPECT_TRUE (ConstraintSum1.check (x)); 
	EXPECT_FALSE (ConstraintSum1.check (y));
	EXPECT_FALSE (ConstraintSum1.check (negatif)); 
}

/*!
 * @brief Tests signs of the input 
 * 
 * Tests if the specific boolean is thrown when we provide negative, null
 * or positive values 
 */
//On ne peut pas faire puisque il faudrait inclure main.cpppour avoir acces 
//à la classe intconstraint et on a donc deux main et cela pause problème
TEST (IntConstraintTCLAP, entier_poitive_or_null) 
{
	//regarde si les entrée de types entière sont positives ou nulle 
	IntConstraintTCLAP Constraintint; 
	EXPECT_FALSE (Constraintint.check (0)); 
	EXPECT_TRUE (Constraintint.check (1)); 
	EXPECT_FALSE (Constraintint.check (-1)); 
}

/*!
 * @brief Tests signs of the input 
 * 
 * Tests if the specific boolean is thrown when we provide negative, null
 * or positive values 
 */
TEST (ProbaConstraintTCLAP, Test_mutation_range) 
{
	ProbaConstraintTCLAP constraint; 
	EXPECT_FALSE (constraint.check (-2)); 
	EXPECT_FALSE (constraint.check (0)); 
	EXPECT_TRUE (constraint.check (0.3));
	EXPECT_TRUE (constraint.check (0.9));
	EXPECT_FALSE (constraint.check (1));
	EXPECT_FALSE (constraint.check (2)); 
}

/*!
 * @brief Tests signs of the input 
 * 
 * Tests if the specific boolean is thrown when we provide negative, null
 * or positive values 
 */
TEST (FitnessConstraintTCLAP, Test_fitness_range) 
{
	FitnessConstraintTCLAP constraint; 
	EXPECT_FALSE (constraint.check (-2)); 
	EXPECT_TRUE (constraint.check (0)); 
	EXPECT_TRUE (constraint.check (2));
}

/*!
 * @brief main() 
 * 
 * Launches the tests (all the tests) 
 */
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}
