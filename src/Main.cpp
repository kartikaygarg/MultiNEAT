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

int num_class_labels = 7;      // labels for 0-4 and MISC
int num_tests = 10;   //No of training data tests
int num_gens = 1000;   //No of training data tests

//std::vector<double>
double xortest(Genome& g, double** outputs)
{

    NeuralNetwork net;
    g.BuildPhenotype(net);
    
    int depth = 30;
    double error = 0;
    double class_error = 0, miss_error = 0;
    std::vector<double> inputs;
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[0][i] = net.Output()[i];
        if(outputs[0][i] < 1e-3){
            outputs[0][i] = 0;
        }
        else if(outputs[0][i] > 0.135e2){
            outputs[0][i] = 1;
        }
        if(i == 0)
            class_error += fabs(outputs[0][i] - 1.0);
        else
            miss_error += fabs(outputs[0][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[1][i] = net.Output()[i];
        if(outputs[1][i] < 1e-3){
            outputs[1][i] = 0;
        }
        else if(outputs[1][i] > 0.135e2){
            outputs[1][i] = 1;
        }
        if(i == 1)
            class_error += fabs(outputs[1][i] - 1.0);
        else
            miss_error += fabs(outputs[1][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[2][i] = net.Output()[i];
        if(outputs[2][i] < 1e-3){
            outputs[2][i] = 0;
        }
        else if(outputs[2][i] > 0.135e2){
            outputs[2][i] = 1;
        }
        if(i == 2)
            class_error += fabs(outputs[2][i] - 1.0);
        else
            miss_error += fabs(outputs[2][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[3][i] = net.Output()[i];
        if(outputs[3][i] < 1e-3){
            outputs[3][i] = 0;
        }
        else if(outputs[3][i] > 0.135e2){
            outputs[3][i] = 1;
        }
        if(i == 3)
            class_error += fabs(outputs[3][i] - 1.0);
        else
            miss_error += fabs(outputs[3][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[4][i] = net.Output()[i];
        if(outputs[4][i] < 1e-3){
            outputs[4][i] = 0;
        }
        else if(outputs[4][i] > 0.135e2){
            outputs[4][i] = 1;
        }
        if(i == 4)
            class_error += fabs(outputs[4][i] - 1.0);
        else
            miss_error += fabs(outputs[4][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[5][i] = net.Output()[i];
        if(outputs[5][i] < 1e-3){
            outputs[5][i] = 0;
        }
        else if(outputs[5][i] > 0.135e2){
            outputs[5][i] = 1;
        }
        if(i == 5)
            class_error += fabs(outputs[5][i] - 1.0);
        else
            miss_error += fabs(outputs[5][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[6][i] = net.Output()[i];
        if(outputs[6][i] < 1e-3){
            outputs[6][i] = 0;
        }
        else if(outputs[6][i] > 0.135e2){
            outputs[6][i] = 1;
        }
        if(i == 6)
            class_error += fabs(outputs[6][i] - 1.0);
        else
            miss_error += fabs(outputs[6][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[7][i] = net.Output()[i];
        if(outputs[7][i] < 1e-3){
            outputs[7][i] = 0;
        }
        else if(outputs[7][i] > 0.135e2){
            outputs[7][i] = 1;
        }
        if(i == 7)
            class_error += fabs(outputs[7][i] - 1.0);
        else
            miss_error += fabs(outputs[7][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[8][i] = net.Output()[i];
        if(outputs[8][i] < 1e-3){
            outputs[8][i] = 0;
        }
        else if(outputs[8][i] > 0.135e2){
            outputs[8][i] = 1;
        }
        if(i == 8)
            class_error += fabs(outputs[8][i] - 1.0);
        else
            miss_error += fabs(outputs[8][i] - 0.0);
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
    for(int i=0; i<num_class_labels; ++i) {
        outputs[9][i] = net.Output()[i];
        if(outputs[9][i] < 1e-3){
            outputs[9][i] = 0;
        }
        else if(outputs[9][i] > 0.135e2){
            outputs[9][i] = 1;
        }
        if(i == 9)
            class_error += fabs(outputs[9][i] - 1.0);
        else
            miss_error += fabs(outputs[9][i] - 0.0);
    }

    return ((1.0 - class_error )/(1.0 + miss_error))*100.0;

}

void print_to_file(fstream& file, double** outputs, int gen){
    file<<"\n Better fitness at gen: "<<gen<<" with Genome: <Print Genome func> \n";
    file<<"-------------------------------------------------\n";
    file<<"Lab\\Out | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n";
    file<<"--------|---|---|---|---|---|---|---|---|---|---|";
    for(int i=0; i < num_tests ; ++i){      //Actual digit tested
        file<<"\nLabel "<<i<<" | ";
        for(int j=0; j < num_class_labels ; ++j){   //Value of output labels
            if(outputs[i][j] < 0.1)
                file<<0<<" | ";
            else if(outputs[i][j] > 0.9)
                file<<1<<" | ";
            else
                file<<outputs[i][j]<<" | ";
        }
    }
    file<<"\n-------------------------------------------------\n";
}

int main()
{
    char OutputFileName[] = "output.log";
    fstream Output_file;
    Output_file.open(OutputFileName, ios::out);
    
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
    
    // int num_class_labels = 4;     //No of output labels

    Genome s(0, 8,      //No of input sensor neurons
             0,
             num_class_labels,         //No of output labels
             false,
             UNSIGNED_SIGMOID,
             UNSIGNED_SIGMOID,
             0,
             params);
    Population pop(s, params, true, 1.0, time(0));
    
    double** outputs = NULL;
    outputs = (double**) malloc(num_tests*sizeof(double*));
    for(int i=0; i<num_tests ; ++i){
        outputs[i] = (double*) calloc(num_class_labels,sizeof(double));
    }
    
    for(int k=0; k<num_gens; k++)
    //for(int k=0; k<1500; k++)
    {
        double bestf = -999999;
        for(unsigned int i=0; i < pop.m_Species.size(); i++)
        {
            for(unsigned int j=0; j < pop.m_Species[i].m_Individuals.size(); j++)
            {
                double f = xortest(pop.m_Species[i].m_Individuals[j], outputs);
                pop.m_Species[i].m_Individuals[j].SetFitness(f);
                pop.m_Species[i].m_Individuals[j].SetEvaluated();

                if (f > bestf)
                {
                    bestf = f;
                    print_to_file(Output_file, outputs, k);
                }
            }
        }

        printf("Generation: %d, best fitness: %3.5f\n", k, bestf);
        pop.Epoch();
        
        if(bestf > 99.0){
            cout<<"\n-------------------------------------------------\n";
            cout<<"\nConvergence ACHIEVED!!!";
            break;
        }
    }

    Output_file.close();
    
    return 0;
}

#endif
