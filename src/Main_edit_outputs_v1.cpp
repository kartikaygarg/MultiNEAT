/*
 * Main.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: peter
 */

 /*
  * Ignore this file. I use it to test stuff.
  *
  */

#define _GNU_SOURCE

#include "Genome.h"
#include "Population.h"
#include "NeuralNetwork.h"
#include "Parameters.h"
#include "Substrate.h"

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace NEAT;
using namespace std;

#define ENABLE_TESTING
#ifdef ENABLE_TESTING

/*
double abs(double x)
{
    if (x < 0) return -x;
    return x;
}*/

//std::vector<double>
std::array<std::vector<double>,10> xortest(Genome& g, double& fitness)
{

    NeuralNetwork net;
    g.BuildPhenotype(net);
    
    int output_labels = 4;      // labels for 0-4 and MISC
    int depth = 30;
    double error = 0;
    double class_error = 0, miss_error = 0;
    std::vector<double> inputs;
    std::array<std::vector<double>,10> ret_out;
    inputs.resize(8);

    net.Flush();    //0
    inputs[0] = 1;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 1;
    inputs[3] = 1;
    inputs[4] = 1;
    inputs[5] = 1;
    inputs[6] = 0;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    ret_out[0] = net.Output();
    for(int i=0; i<output_labels; ++i) {
        if(i == 0)
            class_error += fabs(ret_out[0][i] - 1.0);
        else
            miss_error += fabs(ret_out[0][i] - 0.0);
    }

    net.Flush();    //1
    inputs[0] = 0;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 1;
    inputs[3] = 0;
    inputs[4] = 0;
    inputs[5] = 0;
    inputs[6] = 0;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 1)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }

    net.Flush();    //2
    inputs[0] = 1;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 0;
    inputs[3] = 1;
    inputs[4] = 1;
    inputs[5] = 0;
    inputs[6] = 1;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 2)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }

    net.Flush();    //3
    inputs[0] = 1;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 1;
    inputs[3] = 1;
    inputs[4] = 0;
    inputs[5] = 0;
    inputs[6] = 0;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 3)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }
    
    net.Flush();    //4
    inputs[0] = 0;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 1;
    inputs[3] = 0;
    inputs[4] = 0;
    inputs[5] = 1;
    inputs[6] = 1;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 4)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }
    
    net.Flush();    //5
    inputs[0] = 1;  // Segment - a
    inputs[1] = 0;
    inputs[2] = 1;
    inputs[3] = 1;
    inputs[4] = 0;
    inputs[5] = 1;
    inputs[6] = 1;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 5)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }
    
    net.Flush();    //6
    inputs[0] = 1;  // Segment - a
    inputs[1] = 0;
    inputs[2] = 1;
    inputs[3] = 1;
    inputs[4] = 1;
    inputs[5] = 1;
    inputs[6] = 1;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 6)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }
    
    net.Flush();    //7
    inputs[0] = 1;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 1;
    inputs[3] = 0;
    inputs[4] = 0;
    inputs[5] = 0;
    inputs[6] = 0;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 7)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }
    
    net.Flush();    //8
    inputs[0] = 1;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 1;
    inputs[3] = 1;
    inputs[4] = 1;
    inputs[5] = 1;
    inputs[6] = 1;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 8)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }
    
    net.Flush();    //9
    inputs[0] = 1;  // Segment - a
    inputs[1] = 1;
    inputs[2] = 1;
    inputs[3] = 0;
    inputs[4] = 0;
    inputs[5] = 1;
    inputs[6] = 1;  // Segment - g
    inputs[7] = 1;  //BIAS
    net.Input(inputs);
    for(int i=0; i<depth; i++) { net.Activate(); }
    for(int i=0; i<output_labels; ++i) {
        if(i == 9)
            class_error += fabs(net.Output()[i] - 1.0);
        else
            miss_error += fabs(net.Output()[i] - 0.0);
    }

    // return ((1.0 - class_error )/(1.0 + miss_error))*100.0;
    fitness = ((1.0 - class_error )/(1.0 + miss_error))*100.0;

}

int main()
{
    Parameters params;

    params.PopulationSize = 150;
    params.DynamicCompatibility = true;
    params.WeightDiffCoeff = 4.0;
    params.CompatTreshold = 2.0;
    params.YoungAgeTreshold = 15;
    params.SpeciesMaxStagnation = 15;
    params.OldAgeTreshold = 35;
    params.MinSpecies = 5;
    params.MaxSpecies = 25;
    params.RouletteWheelSelection = false;
    params.RecurrentProb = 0.0;
    params.OverallMutationRate = 0.8;

    params.MutateWeightsProb = 0.90;

    params.WeightMutationMaxPower = 2.5;
    params.WeightReplacementMaxPower = 5.0;
    params.MutateWeightsSevereProb = 0.5;
    params.WeightMutationRate = 0.25;

    params.MaxWeight = 8;

    params.MutateAddNeuronProb = 0.03;
    params.MutateAddLinkProb = 0.05;
    params.MutateRemLinkProb = 0.0;

    params.MinActivationA  = 4.9;
    params.MaxActivationA  = 4.9;

    params.ActivationFunction_SignedSigmoid_Prob = 0.0;
    params.ActivationFunction_UnsignedSigmoid_Prob = 1.0;
    params.ActivationFunction_Tanh_Prob = 0.0;
    params.ActivationFunction_SignedStep_Prob = 0.0;

    params.CrossoverRate = 0.75 ;
    params.MultipointCrossoverRate = 0.4;
    params.SurvivalRate = 0.2;


    Genome s(0, 8,      //No of input sensor neurons
             0,
             4,         //No of output labels
             false,
             UNSIGNED_SIGMOID,
             UNSIGNED_SIGMOID,
             0,
             params);
    Population pop(s, params, true, 1.0, time(0));

    for(int k=0; k<1000; k++)
    //for(int k=0; k<1500; k++)
    {
        double bestf = -999999;
        for(unsigned int i=0; i < pop.m_Species.size(); i++)
        {
            for(unsigned int j=0; j < pop.m_Species[i].m_Individuals.size(); j++)
            {
                double f = 0;
                std::array<std::vector<double>,10> ret_out = xortest(pop.m_Species[i].m_Individuals[j], &f);
                // double f = xortest(pop.m_Species[i].m_Individuals[j]);
                pop.m_Species[i].m_Individuals[j].SetFitness(f);
                pop.m_Species[i].m_Individuals[j].SetEvaluated();

                if (f > bestf)
                {
                    bestf = f;
                }
            }
        }

        printf("Generation: %d, best fitness: %3.5f\n", k, bestf);
        pop.Epoch();
    }

    return 0;
}

#endif
