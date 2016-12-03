#include <iomanip>   // std::setw
#include <vector>
#include <string> 
#include <ostream>   // std::cout
#include <fstream>

#include <tclap/CmdLine.h>

#include "MetaPool.hpp"
#include "IntConstraintTCLAP.h"
#include "VectorConstraintTCLAP.h"
#include "ProbaConstraintTCLAP.h"
#include "World.hpp" 

using namespace TCLAP;
using namespace std;

/*!
 * @file main.cpp
 * @author Yann Dubois et David Cleres
 * @date 12 november 2015
 * @version 1.0
 * @brief Model Wright-Fisher, Sickle Cell Anemia, Selection & Mutation 
 *
 * The main programm allows you to do:
 * - a modelisation of Wright Fisher in a context of total
 * biological abstration 
 * - a modelisation of the Natural Selection phenomena, taking in consideration 
 * the fitness of differents genes in relation to the others 
 * - a modelisation of mutations occuring with a specified mutation rate. 
 * - a modelisation of the evolution of the sickle cell anemia in three 
 * different countries. (Congo, Cameroon & Gaboon) This simulation is based 
 * on real facts. 
 * - a modelisation taking in concideration the bottleneck effect. This is 
 * often the case in natural crysis' in which a large part of the population 
 * is exitinct. In the major cases the most present population (in numeric terms
 * will be the only one which survives at the end, but sometimes this effect can 
 * make a less crowed population be the new leader population in term of 
 * numeric amount. 
 */

const double probaMalaryaCongo(0.047);
const double probaMalaryaCameroon(0.163);
const double probaMalaryaGabon(0.153);

//WE DIVIDED THE POPULATION BY 100 TO HAVE LESS CALCULATION TIME. 
long int popCongo (45000);
long int popCameroon (230000);
long int popGabon (16000);

/*!
 * @brief Display the Simulation Results in case of Drepanocitosis
 * 
 * Displays on the given stream *fStream* the calculated frequences. This is the 
 * display function which is specific for the displaying of the simulation 
 * in which we take in consideration the Sickle Cell Anemia desease. This function is 
 * used to make the first output on cout stream.
 * 
 * @param fStream Is the output stream in which we eant to write the frequences 
 * @param world Is the World containing our different MetapoolDreps (i.e. 
 * countries: Congo, Cameroon & Gaboon) 
 * @param nGenerations Is the number of generations on which we want to study 
 * our allelic evolution.  
 */
void affiche (ostream& fStream, World& world, unsigned int const& nGenerations);

/*!
 * @brief Display the Simulation Results in case of Drepanocitosis
 * 
 * Displays on the given stream *fStream* the calculated frequences. This is the 
 * display function which is specific for the displaying of the simulation 
 * in which we take in consideration the Sickle Cell Anemia desease. This function
 * writes the new frequences for each country in 3 different files. 
 * 
 * @param fStream Is the output stream in which we eant to write the frequences 
 * @param world Is the World containing our different MetapoolDreps (i.e. 
 * countries: Congo, Cameroon & Gaboon) 
 * @param nGenerations Is the number of generations on which we want to study 
 * our allelic evolution.  
 */
void affiche (ostream& fStreamA, ostream& fStreamB, ostream& fStreamC, 
			  World& world, unsigned int const& nGenerations); 
/*!
 * @brief Display the Simulation Results
 * 
 * This function is an overload of the other affiche fonction. 
 * This function Displays on the given stream *fStream* the calculated frequences. 
 * This is the display fonction which is specific for the displaying of the simulation 
 * in which we take in consideration Selection, mutation, the Wright-Fisher Model, ... 
 * 
 * @param fStream Is the output stream in which we eant to write the frequences 
 * @param setOfPool Is a metapool on which we will focus to study our 
 * allelic evolution. 
 * @param nGenerations Is the number of generations on which we want to study 
 * our allelic evolution. 
 * @param isBottleneck Is a boolean variable, that tells us if we are taking 
 * in consideration the bottleneckphenomena.  
 */
void affiche (ostream& fStream, Metapool& setOfPool, unsigned int const& nGenerations,
			  bool isBottleneck);
			  

/*!
 * @brief Main Programm
 * 
 * Main programme taking and interpreting the input of the user by using 
 * TCLAP commands and calling the necessary methods in the different classes 
 * to enable us to make our simulations. 
 * 
 * @param argc 
 * @param argv  
 */
int main(int argc, char* argv[])
{
	try 
	{
		CmdLine cmd ("Projet prog génomique", ' ', "Version 1.0");
		IntConstraintTCLAP Constraint0;
		ProbaConstraintTCLAP ConstraintProba;
		VectorConstraintTCLAP ConstraintSum1;

		ValueArg<int> nIndividu ("n", "indiv", "nombre d'individu: par défaut 100", false, 100, &Constraint0);
		cmd.add (nIndividu);
		ValueArg<int> nGeneration ("g", "generation", "nombre de génération: par défaut 10", false, 10, &Constraint0);
		cmd.add (nGeneration);
        ValueArg<int> nRepeat ("r", "repeat", "nombre de replicats: par défaut 3", false, 3, &Constraint0);
        cmd.add (nRepeat);
        ValueArg<double> mutation ("m", "rmutation", "taux de mutation: par défaut 0", false, 0, &ConstraintProba);
        cmd.add (mutation);
        SwitchArg bottleneck ("b", "bottleneck", "Fait un goulot d'étanglement génétique: événement qui fait qu'une partie de la population disparait ou ne peut plus se reproduire: ici c'est une catastrophe naturelle qui élimine 90% de la population à la <<génération du milieu>>: vous pouvez pas mettre de botlle neckeffect avec de l'anémie falciforme ");
        cmd.add (bottleneck);
        ValueArg<string> fichierSortie ("e", "fichierExit", "fichier de sortie: par défaut terminal", false, "terminal", "string");
        cmd.add (fichierSortie);
        SwitchArg isDrepanocytose ("a", "anemieFalciforme", "exemple de génétique des population avec l'anémie falciforme au Gabo, Cameroon et Congo en prenant en compte les migrations entre ces 3 pays, la vrai population, la probabilité d'avoir la malarya, le taux de survie pour les hétérozygote de l'anémie falciforme contre la malarya, le taux de mortalité des homozygote de l'anémie falciform (statistique de l'OMS) (NB: on travail avec un échantillon de 1% de la population): vous pouvez seulement spécifier le nombre de génération en plus de -a ");
        cmd.add (isDrepanocytose);
        //valeur pas possible donc on doit mettre à 0
		MultiArg<double> Fitness ("s", "Fitness", "tableau de Fitness (séléction naturelle) des allèles: par défaut pas de fitness", false, "réel plus grand que -1");
		cmd.add (Fitness);
		UnlabeledMultiArg<double> FreqAllele ("FreqAllele", "tableau de freqeunces respéctives des allèles: veuillez séparer les fréquences et vous n'avez pas besoin de mettre de flag: par défaut 0.1 0.2 0.3 0.4", false, &ConstraintSum1);
		cmd.add (FreqAllele);
		
		cmd.parse (argc, argv);
		
		bool isAnemie (isDrepanocytose.getValue());
        bool isBottleneck (bottleneck.getValue());
		unsigned int nIndividus (nIndividu.getValue());
		unsigned int nGenerations (nGeneration.getValue());
        unsigned int nRepeats (nRepeat.getValue());
        string fSortie (fichierSortie.getValue()); 
		vector<double> FreqAlleles (FreqAllele.getValue());
        if (FreqAlleles.empty())
        {
            FreqAlleles = {0.1, 0.2, 0.3, 0.4};
        }
        double tauxMutation (mutation.getValue());
        if (tauxMutation != 0 && FreqAlleles.size() == 1)
        {
            throw "Vous ne pouvez pas utilisé les mutations si vous n'avez qu'une seule allèle /elle ne va pas se mutter en elle même!";
        }
		vector<double> fitness (Fitness.getValue());
		
		//On test ici si la valeurs est comprise entre -1 et infini car 
		//on a modifié les MultiArg pour que travail seulement avec les 
		//tableaux + on doit connaitre la taille de freq pour comparer.
		if (!fitness.empty())
        {
            if (fitness.size() != FreqAlleles.size())
            {
                throw (ArgException ("Le nombre de fitness doit être égal au nombre d'allèle", "-s"));
            }
            bool isToutMoins1 (true);
            for (auto element : fitness)
            {
                if (element != -1)
                {
                    isToutMoins1 = false;
                }
                if (element < -1)
                {
                    throw (ArgException ("Les Fitness -s doivent être plus grand que -1", to_string(element) ,"Réel plus grand que -1"));
                }
            }
            // si toutes les allèles sont léthales il faut throw une erreur
            if (isToutMoins1) {
                throw "Toutes les allèles ne peuvent pas être léthales: donc au moins une valeurs des fitness doit être différent de -1";
            }
            if (tauxMutation != 0)
            {
                throw "Vous ne pouvez pas mettre des mutations et de la séléction naturelle";
            }
        }
    	if (isAnemie)
    	{
			vector<double> freqDrepCameroon ({0.71,0.29});
			vector<double> freqDrepCongo ({0.68,0.32});
			vector<double> freqDrepGabon ({0.75,0.25});
			PoolDrep poolCongo (freqDrepCongo, popCongo, probaMalaryaCongo, "Congo");
			PoolDrep poolCameroon (freqDrepCameroon, popCameroon, probaMalaryaCameroon, "Cameroon");
			PoolDrep poolGabon (freqDrepGabon, popGabon, probaMalaryaGabon, "Gabon");
			MetapoolDrep Congo (3, poolCongo);
			MetapoolDrep Cameroon (3, poolCameroon);
			MetapoolDrep Gabon (3, poolGabon);
			vector<MetapoolDrep> setOfPools ({Congo, Cameroon, Gabon});
			World world (setOfPools);
			
    		if (fSortie == "terminal")
			{
				affiche (cout, world, nGenerations);
			}
			else
			{
				string fSortieCameroon ("../Resultat/" + fSortie + "_Cameroon.txt");
				string fSortieCongo ("../Resultat/" + fSortie + "_Congo.txt");
				string fSortieGaboon ("../Resultat/" + fSortie + "_Gaboon.txt");
				ofstream fStreamCo;
				ofstream fStreamCa;
				ofstream fStreamGa;
				fStreamCa.open (fSortieCameroon);
				fStreamCo.open (fSortieCongo);
				fStreamGa.open (fSortieGaboon);
				affiche (fStreamCa, fStreamCo, fStreamGa, world, nGenerations);
				fStreamCa.close();
				fStreamCo.close();
				fStreamGa.close();
			}
    	}
    	//SANS DREPANOCITOSE 
    	else
    	{
			Pool x (FreqAlleles, nIndividus, tauxMutation, fitness); 
			Metapool setOfPool (nRepeats, x);
			
			if (fSortie == "terminal")
			{
				affiche (cout, setOfPool, nGenerations, isBottleneck);
			}
			else
			{
				fSortie = "../Resultat/" + fSortie + ".txt";
				ofstream fStream;
				fStream.open (fSortie);
				affiche (fStream, setOfPool, nGenerations, isBottleneck);
				fStream.close();
			}
		}
	} 
	catch (ArgException &e)
	{
		cerr << "error : " << e.error() << " for arg :" << e.argId() << endl;
	}
    catch (const char* erreur)
    {
        cerr << erreur << endl;
    }

	return 0; 
}

void affiche (ostream& fStream, World& world,
			  unsigned int const& nGenerations)
{
	//AFFICHAGE SUR LE TERMINAL POUR L'UTILISATEUR 
	cout << "Les fréquences entrées sont: ";
	world.affiche (cout);
	cout << endl;
	
	for (unsigned int i(0); i <= nGenerations; i++)
	{
		fStream << i << " ";
		world.affiche (fStream);
        world.nextGenerationGeneral();
		fStream << endl; 
	}
}

void affiche (ostream& fStream, Metapool& setOfPool, 
			  unsigned int const& nGenerations, bool isBottleneck)
{
	//AFFICHAGE SUR LE TERMINAL POUR L'UTILISATEUR 
	cout << "Les fréquences entrées sont: ";
	setOfPool.affiche (cout);
	cout << endl; 
	
	//AFFICHAGE DE LA GENERATION 0
	fStream << 0;
	setOfPool.affiche (fStream);
	fStream << endl; 
	
	for (unsigned int i(0); i < nGenerations; i++)
	{
        if (isBottleneck && i == (nGenerations / 2))
        {
            setOfPool.bottleneck();
        }
		fStream << i+1;
		setOfPool.nextGenerationGeneral();
		setOfPool.affiche(fStream);
		fStream << endl; 
	}
}

void affiche (ostream& fStreamA, ostream& fStreamB, ostream& fStreamC, 
			  World& world, unsigned int const& nGenerations)
{
	//AFFICHAGE SUR LE TERMINAL POUR L'UTILISATEUR 
	cout << "Les fréquences entrées sont: ";
	world.affiche (cout);
	cout << endl;
	fStreamA << "CAMEROONISATION DE LA MALARIA: " << endl; 
	fStreamB << "CONGOLEXISATION DE LA MALARIA: " << endl; 
	fStreamC << "GABONENISATION DE LA MALARIA: " << endl; 
	
	for (unsigned int i(0); i <= nGenerations; i++)
	{
		fStreamA << i << " ";
		fStreamB << i << " "; 
		fStreamC << i << " "; 
		world.affiche (fStreamA, fStreamB, fStreamC);
        world.nextGenerationGeneral();
		fStreamA << endl; 
		fStreamB << endl;
		fStreamC << endl;
	}
}
