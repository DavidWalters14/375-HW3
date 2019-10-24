#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

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
struct answer{
	int tprofit;
	int size;
	double time;
};
answer greedy1(problem p){
	std::chrono::time_point<std::chrono::system_clock> s, e;
  s = std::chrono::system_clock::now();
  const clock_t begin_time = clock();
	int capacity = p.cap;
	vector<int> ratios;
	vector<element> elements;
	for(int i = 0 ; i < p.numelements ; i++){
		ratios.push_back((p.profits[i]/p.weights[i]));
		element e;
		e.profit = p.profits[i];
		e.weight = p.weights[i];
		elements.push_back(e);

	}
	int n = sizeof(ratios) / sizeof(ratios[0]);
	sort(begin(ratios), end(ratios) , greater<int>());
	for(int i = 0 ; i < ratios.size() ; i++){
		for(int j = 0 ; j < elements.size();j++)
		if(ratios[i]==(elements[j].profit/elements[j].weight)){
			element temp = elements[i];
			elements[i]=elements[j];
			elements[j]=temp;
		}
	}
	vector<element> knapsack;
	int totalprofit = 0;
	int currweight = 0;
	for(int i = 0 ; i < elements.size() ; i++){
		if(elements[i].weight<=capacity){
			if((currweight+elements[i].weight)<capacity){
				totalprofit+=elements[i].profit;
				currweight+=elements[i].weight;
				//cout << "currweight: " << currweight << endl;
				//cout << "totalprofit: " << totalprofit << endl;
			}
		}
	}
	e = std::chrono::system_clock::now();
  std::chrono::duration<double> els = e - s;
	answer a;
	a.tprofit = totalprofit;
	a.size = p.numelements;
	a.time = els.count();
	return a;
};

answer greedy2(problem p){
	std::chrono::time_point<std::chrono::system_clock> s, e;
  s = std::chrono::system_clock::now();
  const clock_t begin_time = clock();
	int capacity = p.cap;
	vector<int> ratios;
	vector<element> elements;
	for(int i = 0 ; i < p.numelements ; i++){
		ratios.push_back(p.profits[i]);
		element e;
		e.profit = p.profits[i];
		e.weight = p.weights[i];
		elements.push_back(e);

	}
	int n = sizeof(ratios) / sizeof(ratios[0]);
	sort(begin(ratios), end(ratios) , greater<int>());
	for(int i = 0 ; i < ratios.size() ; i++){
		for(int j = 0 ; j < elements.size();j++)
		if(ratios[i]==(elements[j].profit)){
			element temp = elements[i];
			elements[i]=elements[j];
			elements[j]=temp;
		}
	}
	int totalprofit = 0;
	int currweight = 0;
	for(int i = 0 ; i < elements.size() ; i++){
		if(elements[i].weight<=capacity){
			if((currweight+elements[i].weight)<capacity){
				totalprofit+=elements[i].profit;
				currweight+=elements[i].weight;
			}
		}
	}
	e = std::chrono::system_clock::now();
  std::chrono::duration<double> els = e - s;
	answer a;
	a.tprofit = totalprofit;
	a.size = p.numelements;
	a.time = els.count();
	return a;
}
int main(int argc, char** argv){
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
		problems.push_back(p);
	}
	answer a = greedy1(problems[0]);
	cout << a.tprofit << ", " << a.size << ", " << a.time << endl;
	answer b = greedy2(problems[0]);
	cout << b.tprofit << ", " << b.size << ", " << b.time << endl;

}
