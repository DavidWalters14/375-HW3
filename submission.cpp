#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct problem{
	int numelements;
	int cap;
	vector<int> weights;
	vector<int> profits;
};

struct element{
	int weight;
	int profit;
};
vector<int> greedy1(problem p){
	int capacity = p.cap
	vector<int> ratios;
	vector<element> elements;
	for(int i = 0 ; i < p.numelements ; i++){
		ratios.push_back((p.profits[i]/p.weights[i]));
		element e;
		e.profit = p.profits[i];
		e.weight = p.weights[i];
		elements.push_back(e);
		
	}
	for(int i = 0 ; i < ratios.size() ; i++){
		for(int j = 1 ; j < ratios.size() ; j++){
			if(ratios[i]<ratios[j]){
				swap(ratios[i],ratios[j]);
				swap(elements[i], elements[j]);
			}
		}
	}
	vector<element> knapsack;
	int totalprofit = 0;
	for(int i = 0 ; i < elements.size() ; i++){
		if(elements[i].weight<=capacity){
			totalproft+=elements[i].profit;
		}
	}
};
int main(int argc, char *[]argv){
	ifstream infile(argv[1]);
	vector<problem> problems;
	int number = 0;
	int capacity = 0;
	while(infile >> number >> capacity){
		problem p;
		p.numelements = number;
		p.cap = capacity;
		for(int i = 0 ; i < number ; i++){
			int weight;
			int profit;
			infile >> weight >> profit;
			p.weights.push_back(weight);
			p.profits.push_back(profit);
		}
		problems.push_back(problem);
	}
	
}
