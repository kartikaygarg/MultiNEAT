sed.exe -e "s/\^M//" Parameters.cpp > test.cpp
rm Parameters.cpp
mv test.cpp Parameters.cpp
sed.exe -e "s/\^M//" Assert.cpp > test.cpp
rm Assert.cpp
mv test.cpp Assert.cpp
sed.exe -e "s/\^M//" Genes.cpp > test.cpp
rm Genes.cpp
mv test.cpp Genes.cpp
sed.exe -e "s/\^M//" Genome.cpp > test.cpp
rm Genome.cpp
mv test.cpp Genome.cpp
sed.exe -e "s/\^M//" Innovation.cpp > test.cpp
rm Innovation.cpp
mv test.cpp Innovation.cpp
sed.exe -e "s/\^M//" NeuralNetwork.cpp > test.cpp
rm NeuralNetwork.cpp
mv test.cpp NeuralNetwork.cpp

sed.exe -e "s/\^M//" PhenotypeBehavior.cpp > test.cpp
rm PhenotypeBehavior.cpp
mv test.cpp PhenotypeBehavior.cpp
sed.exe -e "s/\^M//" Population.cpp > test.cpp
rm Population.cpp
mv test.cpp Population.cpp
sed.exe -e "s/\^M//" PythonBindings.cpp > test.cpp
rm PythonBindings.cpp
mv test.cpp PythonBindings.cpp
sed.exe -e "s/\^M//" Random.cpp > test.cpp
rm Random.cpp
mv test.cpp Random.cpp
sed.exe -e "s/\^M//" Species.cpp > test.cpp
rm Species.cpp
mv test.cpp Species.cpp
sed.exe -e "s/\^M//" Substrate.cpp > test.cpp
rm Substrate.cpp
mv test.cpp Substrate.cpp

sed.exe -e "s/\^M//" Utils.cpp > test.cpp
rm Utils.cpp
mv test.cpp Utils.cpp
