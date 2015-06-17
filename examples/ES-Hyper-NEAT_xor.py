#!/usr/bin/python
import os
import sys
import time
import random as rnd
import commands as comm
import cv2
import numpy as np
import cPickle as pickle
import MultiNEAT as NEAT
import multiprocessing as mpc
import utilities

params = NEAT.Parameters()
params.PopulationSize = 200
params.DynamicCompatibility = True
params.CompatTreshold = 1.0
params.YoungAgeTreshold = 15
params.SpeciesMaxStagnation = 30
params.OldAgeTreshold = 35
params.MinSpecies = 1
params.MaxSpecies = 15
params.RouletteWheelSelection = False
params.MutateRemLinkProb = 0.02
params.RecurrentProb = 0.001
params.OverallMutationRate = 0.
params.MutateAddLinkProb = 0.03
params.MutateAddNeuronProb = 0.01
params.MutateWeightsProb = 0.90
params.MaxWeight = 5.0
params.WeightMutationMaxPower = 0.8
params.WeightReplacementMaxPower = 1.0
params.MutateNeuronActivationTypeProb = 0.03
params.CrossoverRate = 0.5
params.MutateWeightsSevereProb = 0.01

# Probabilities for a particular activation function appearance
params.ActivationFunction_SignedSigmoid_Prob = 0.25
params.ActivationFunction_UnsignedSigmoid_Prob = 0.0
params.ActivationFunction_Tanh_Prob = 0.0
params.ActivationFunction_TanhCubic_Prob = 0.0
params.ActivationFunction_SignedStep_Prob = 0.0
params.ActivationFunction_UnsignedStep_Prob = 0.0
params.ActivationFunction_SignedGauss_Prob = 0.25
params.ActivationFunction_UnsignedGauss_Prob = 0.0
params.ActivationFunction_Abs_Prob = 0.0
params.ActivationFunction_SignedSine_Prob = 0.25
params.ActivationFunction_UnsignedSine_Prob = 0.0
params.ActivationFunction_Linear_Prob = 0.25


params.DivisionThreshold = 0.5
params.VarianceThreshold = 0.03
params.BandThreshold = 0.3
params.InitialDepth = 5
params.MaxDepth = 5
params.IterationLevel = 1
params.Leo = True
params.LeoSeed = True
params.LeoThreshold = 0.3
params.CPPN_Bias = -1.0
params.Qtree_X = 0.0
params.Qtree_Y = 0.0
params.Width = 2.0

rng = NEAT.RNG()
rng.TimeSeed()

substrate = NEAT.Substrate([(-1., -1., 0.0), (1., -1., 0.0), (0., -1., 0.0)],
                           [],
                           [(0., 1., 0.0)])

substrate.m_allow_input_hidden_links = False
substrate.m_allow_input_output_links = False
substrate.m_allow_hidden_hidden_links = False
substrate.m_allow_hidden_output_links = False
substrate.m_allow_output_hidden_links = False
substrate.m_allow_output_output_links = False
substrate.m_allow_looped_hidden_links = False
substrate.m_allow_looped_output_links = False

# let's set the activation functions
substrate.m_hidden_nodes_activation = NEAT.ActivationFunction.SIGNED_SIGMOID
substrate.m_output_nodes_activation = NEAT.ActivationFunction.SIGNED_SIGMOID

# when to output a link and max weight
substrate.m_link_threshold = 0.2
substrate.m_max_weight_and_bias = 8.0



def evaluate_xor(genome):

    net = NEAT.NeuralNetwork()

    try:

        genome.Build_ES_Phenotype(net, substrate, params)
        error = 0
        depth = 5
        correct = 0.0

        net.Flush()

        net.Input([1,0,1])
        [net.Activate() for _ in range(depth)]
        o = net.Output()
        error += abs(o[0] - 1)
        if o[0] > 0.75:
            correct +=1.

        net.Flush()
        net.Input([0,1,1])
        [net.Activate() for _ in range(depth)]
        o = net.Output()
        error += abs(o[0] - 1)
        if o[0] > 0.75:
            correct +=1.

        net.Flush()
        net.Input([1,1,1])
        [net.Activate() for _ in range(depth)]
        o = net.Output()
        error += abs(o[0] - 0)
        if o[0] < 0.25:
            correct +=1.

        net.Flush()
        net.Input([0,0,1])
        [net.Activate() for _ in range(depth)]
        o = net.Output()
        error += abs(o[0] - 0)
        if o[0] < 0.25:
            correct +=1.



        return [(4 - error)**2, correct/4., net.GetTotalConnectionLength()]

    except Exception as ex:

        print 'Exception:', ex

        return [1.0, 0.0, 0.0]



def getbest(run, filename):
    g = NEAT.Genome(0, 7, 1, True, NEAT.ActivationFunction.SIGNED_GAUSS, NEAT.ActivationFunction.SIGNED_SIGMOID,
            params)

    pop = NEAT.Population(g, params, True, 1.0)
    results = []
    for generation in range(2000):
        print "---------------------------"
        print "Generation: ", generation
        genome_list = NEAT.GetGenomeList(pop)
    #    fitnesses = NEAT.EvaluateGenomeList_Parallel(genome_list, evaluate)
        fitnesses = NEAT.EvaluateGenomeList_Parallel(genome_list, evaluate_xor, display = False, cores= 4)
        [genome.SetFitness(fitness[0]) for genome, fitness in zip(genome_list, fitnesses)]
        [genome.SetPerformance(fitness[1]) for genome, fitness in zip(genome_list, fitnesses)]
        [genome.SetLength(fitness[2]) for genome, fitness in zip(genome_list, fitnesses)]
       
        best = pop.GetBestGenome()
        results.append([run,generation, best.GetFitness(), best.Length, best.GetPerformance()])
        print "Best ", best.GetFitness(), " Connecions: ",  best.Length, " Performance: ", best.GetPerformance()
        net = NEAT.NeuralNetwork()
       
        pop.Species[0].GetLeader().BuildPhenotype(net)
        img = np.zeros((500, 500, 3), dtype=np.uint8)
        img += 10
        NEAT.DrawPhenotype(img, (0, 0, 500, 500), net )
        cv2.imshow("CPPN", img)

        net = NEAT.NeuralNetwork()
        pop.Species[0].GetLeader().Build_ES_Phenotype(net, substrate, params)
        img = np.zeros((500, 500, 3), dtype=np.uint8)
        img += 10

        utilities.DrawPhenotype(img, (0, 0, 500, 500), net, substrate=True )
        cv2.imshow("NN", img)
        cv2.waitKey(1)

        generations = generation

        #if best > 15.0:
         #   break

        pop.Epoch()

    utilities.dump_to_file(results, filename)
    return generations


gens = []
for run in range(2):
    gen = getbest(run, "test.csv")
    print 'Run:', run, 'Generations to solve XOR:', gen
    gens += [gen]

avg_gens = sum(gens) / len(gens)

print 'All:', gens
print 'Average:', avg_gens

