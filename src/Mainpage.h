/*!
 * @mainpage Main Programm
 * @section initial_sec Initial Project: The Wright-Fischer Model
 * \b -e output file <em> (default: terminal)</em> \b -r number repeats <em> (default: 3)</em> \b -g number generations <em> (default: 10)</em> \b -n number individuals <em> (default: 100)</em> <b> no flag </b> alleles frequencies <em> (default: 0.1 0.2 0.3 0.4)</em>
 *
 * Initially we only make a simple model of population genetics using the Wright Fisher model: there is 
 * population of N individual, they mate randomly and "mix" their DNA to produce the next generation of 
 * N individual
 * @subsection lackBiology Lack of Biology
 * We only model genetic drift, no selection, mutation, migration and no change in population size. 
 * For this basic model we don't need to take into consideration the sex of the individuals and we can even only
 * take into consideration the N*2 alleles and not the fact that they are grouped by 2.
 * @image html lackBiology.png "Simple Wright-Fisher model"
 * @subsection randomMatting Random Matting:
 * @image html randomMating.png
 * @subsection results Results & Plots 
 * @image html RPlots.png "Graphs showing the evolution of the frequences of the different alleles"
 * @image html FixationTimes.png "Fixation Times of different simulations with different sizes of population, different frequences, number generation and number of repeats" 
 * @section mutation_sec Mutation Extension
 * \b -m mutation probability <em> (default: 0)</em>
 *
 * To introduce mutation (probability of mutating: m)  we just need to substract to the number of each allele \f$ N_i \f$ the number of alleles which mutates \f$ N_i*m \f$ and add the number of the alleles which mutate into \f$ N_i \f$ which is the number of other alleles times m \f$ (N_{tot}-N_i)*m \f$  divided by the number of alleles in which they can mutate (note that you can't mutate into you) so: \f$ N_i'= N_i - N_i*m +\frac{(N_{tot}-N_i)*m}{A-1} \f$
 *finally we divide by the number of total alleles \f$ N_{tot} \f$ to obtain frequencies:
 * \f[
 * f_i'= f_i - f_i*m +\frac{(1-f_i)*m}{A-1}= f_i(1-m-\frac{m}{A-1}) + \frac{m}{A-1} = f_i(1-\frac{A*m}{A-1}) + \frac{m}{A-1} 
 * \f]
 * @section selection_sec Natural Selection Extension
 * \b -s alleles fitnesses <em> (default: 0 0 0 ...)</em>
 *
 * To introduce natural selection we just need to multiply \f$ f_i \f$ by a \f$ s_i \f$ which can be between -1 and infinity (0 if no selection) and then 
 * in order to have a constant population size you divide by \f$ \sum f_k*(1+s_k)\ \f$ so:
 * \f[ 
 * f_i'= \frac{f_i*(1+s_i)}{\sum f_k*(1+s_k)} = \frac{f_i*(1+s_i)}{\sum f_k +\sum f_ks_k} = \frac{f_i*(1+s_i)}{1 +\sum f_ks_k} 
 * \f]
 * @section botlleneck_sec Bottleneck Extension
 * \b -b bottleneck effect flag <em> (default: no)</em>
 *
 * The bottleneck effect is a sharp reduction of the population size due to envirenmental events (earthquakes, fires ...) or human activities (genocides...). It enables a huge effect 
 * of genetic drift (random selection). In this case it creates a natural disaster which randomly kills 90% of the population.
 * @image html bottleneck.png "Bottleneck diagramm"
 * @section anemia_sec Sickle Cell and Malaria Extension
 * \b -a sickle cell anemia flag <em> (default: no)</em>
 *
 * In this "main" extension we wanted to make a model of genetic population more complex than the basic model. We chose to study the population genetics of sickle cell disease while
 * taking into account malaria:
 *      - Sickle cell anemia is indeed often taken as an example of natural selection. This disease is an inherited red blood cell disorder which comes from an
 * abnormal hemoglobin coded by the recessive S allele of hemoglobin gene. The homozygous SS genotype is deadly in approximatively 70% of cases. The heterozygous NS genotype causes some
 * complications but doesn't normally result in death (we didn't take into complications the low death rate of NS), but prevents the patient of dying from malaria because the
 * parasites cannot reproduce in the red blood cells. This adaptative advantage explains why drepanocytosis (sickle cell disease) is very prevalent in regions touched by malaria. 
 *      - We chose 3 countries: Cameroon, Gabon and the Republic of the Congo, to try to make a model of the popultaion genetics while taking into account the real statistics.
 *      - In order to make a better model we also computed the migration between these countries.
 * Note that we didn't take into account the population growth, mutations, other migrations with other countries, non random matting.
 * The statistics (population size, malaria pourcentage, sickle cell disease pourcentage, population migration...) were taken from \b WHO
 * @image html anemiaCountries.png "The statistics taken from the WHO used to model this genetic population"
 *
 * -> Using basic probability we found the new probabiliy of getting a N and a S: \f$ f(N)= (1-m)*p^{2} + p*q \f$ and \f$ f(S)= 0.3*q^{2} + p*q \f$
 *
 * @image html anemiaGenetics.png "Tree diagramm to find the probability of getting a N and a S"
 
 */
