# Disease-Spread-Simulator
## Introduction
Our project performed a simulation study and reported the average. We make a closed world assumption for a town. We assume a period of a week in which people in the town interacted with one another. At the end of the week a certain number of residents are found infected by a disease. Based on their recorded interactions during the week and the individuals found infected, we wish to determine people with the possible infection.
The problem has covered some important topics that have been taught in the Applied Graph Theory subject. For representing the population, data structures such as the adjacency matrix have been applied. Graph algorithms have been used to find the interactions between the people and find the spread of the disease.
## PROPOSED SYSTEM AND ALGORITHM
Our model considers a population of 2000 people who are living in a town. In this population we figure out the number of infected people for different infection rates for the different variants of the CoronaVirus. Other factors such as the effectiveness of social distancing are also considered for various possibilities. For example, a strict social distance implementation reduces the spread of disease to 0% and like this other inputs namely 50% and 75% are also provided. The infection rates of variants are also taken as 25% , 50% and 75% for the different cases. The simulation is done a number of times after which we calculate the standard deviation to find out the number of infected people over a period of iterations.
## RESULTS
Provided below are the tables representing the numbers that came out as a result of multiple iterations for different infection rates and different social distancing effectiveness.

First Variant. 25% infection rate.
![First Variant](https://github.com/Abhii-now/Disease-Spread-Simulator/blob/main/screenshots/variant1.png)
Second Variant. 50% infection rate.
![Second Variant](https://github.com/Abhii-now/Disease-Spread-Simulator/blob/main/screenshots/variant2.png)
Third variant. 75% infection rate.
![Thrid Variant](https://github.com/Abhii-now/Disease-Spread-Simulator/blob/main/screenshots/variant3.png)
## CONCLUSION
In this project we worked using different graph theory concepts that have been taught to us in this course. We worked on the Corona Virus problem and were able to find the spread of the deadly disease on a particular number of people using Graph theory concepts.
The most challenging aspect of this project was to find out a close to accurate measure of the spread of infection. The works already present in the domain make use of existing datasets to find a prediction. These datasets are of the initial Covid span so the result is somewhat not as good as expected.
The solution of the problem to make the model simulate the disease irrespective of the dataset which led to a more accurate result or a better one. The takeaway was the fact that the adjacency matrix performed better compared to adjacent lists in case of dense graphs (The graph representing a social network).
