#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>

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
bool comp(const element& a, const element& b){
	if(a.weight==0){
		return false;
	}
	if(b.weight==0){
		return false;
	}
	return (a.profit/a.weight) > (b.profit/b.weight);
}
int greedy1(problem p){

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
			if((currweight+elements[i].weight)<=capacity){
				totalprofit+=elements[i].profit;
				currweight+=elements[i].weight;
				//cout << "currweight: " << currweight << endl;
				//cout << "totalprofit: " << totalprofit << endl;
			}
		}
	}

	return totalprofit;
};

int greedy2(problem p){

	int maxprofit = 0;
	for(int i = 0 ; i < p.numelements ; i++){
		if(p.profits[i]>maxprofit){
			if(p.weights[i] <= p.cap){
				maxprofit = p.profits[i];
			}
		}
	}
	int b = greedy1(p);
	//int bprof = b.tprofit;

	return max(b, maxprofit);
}
double bound(problem p){
	//cout << "computing bound" << endl;
	vector<element> elements;
	for(int i = 0 ; i < p.numelements ; i++){
		element e;
		e.profit = p.profits[i];
		e.weight = p.weights[i];
		elements.push_back(e);
	}
	sort(elements.begin(), elements.end() , comp);
	//cout << "finished sorting" << endl;
	int currweight = 0;
	int index = 0;
	double upperbound = 0;
	while(currweight <= p.cap && index < p.numelements){
		if(currweight+elements[index].weight <= p.cap){
			currweight+=elements[index].weight;
			upperbound+=elements[index].profit;
		}
		else{
			int sub = p.cap - currweight;
			double frac = (double)elements[index].profit/(double)elements[index].weight;
			double ret = sub * frac;
			currweight = p.cap;
			upperbound+=ret;
		}
		index++;
	}
	//cout << "finished while loop" << endl;
	return upperbound;
}

bool isPromising(problem p, int weight, int profit, int maxprofit){
	double upperbound = bound(p);
	if(weight >= p.cap){
		return false;
	}
	if(upperbound > maxprofit){
		return true;
	}
	return false;
}

int knapsackHelper(problem p, int level , int weight , int value, int currentmax){
	//cout << "in nap sack, level: " << level << endl;
	//cout << "numelements: " << p.numelements << endl;
	if(level >= p.numelements){
		return currentmax;
	}
	bool temp = isPromising(p, weight, value, currentmax);
	if(temp==true){
			//cout << "is promising was correct " << endl;
			if(value>currentmax){
				currentmax = value;
			}
			int leftmax = knapsackHelper(p, level+1, weight + p.weights[level] , value + p.profits[level], currentmax);
			//cout << "computed left" << endl;
			problem p2;
			p2.numelements = p.numelements;
			p2.cap = p.cap;
			for(int i = 0 ; i < p.numelements ; i++ ){
				if(i==level){
					p2.weights.push_back(0);
					p2.profits.push_back(0);
				}
				else{
					p2.weights.push_back(p.weights[i]);
					p2.profits.push_back(p.profits[i]);
				}
			}
			int rightmax = knapsackHelper(p2, level+1, weight, value, currentmax);
			return max(leftmax, rightmax);
	}
	return currentmax;
}


int knapsack(problem p){
	int maxprofit=greedy2(p);
	return knapsackHelper(p, 0, 0, 0, maxprofit);
};
int main(int argc, char** argv){
	ifstream infile(argv[1]);
	ofstream output;
	output.open(argv[2]);
	string dec = argv[3];
	int decider = stoi(dec);
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
	for(int i = 0 ; i < problems.size() ; i++){
		if(decider == 0){
			std::chrono::time_point<std::chrono::system_clock> s, e;//timer variable s = start , e = end
		  s = std::chrono::system_clock::now();
			int max = greedy1(problems[i]);
			e = std::chrono::system_clock::now();
		  std::chrono::duration<double> els = e - s;
			output << problems[i].numelements << " " << max << " " << els.count() << endl;
		}
		else if(decider == 1){
			std::chrono::time_point<std::chrono::system_clock> s, e;//timer variable s = start , e = end
		  s = std::chrono::system_clock::now();
			int max = greedy2(problems[i]);
			e = std::chrono::system_clock::now();
		  std::chrono::duration<double> els = e - s;
			output << problems[i].numelements << " " << max << " " << els.count() << endl;
		}
		else if(decider == 2){
			std::chrono::time_point<std::chrono::system_clock> s, e;//timer variable s = start , e = end
		  s = std::chrono::system_clock::now();
			int max = knapsack(problems[i]);
			e = std::chrono::system_clock::now();
		  std::chrono::duration<double> els = e - s;
			output << problems[i].numelements << " " << max << " " << els.count() << endl;
		}
	}
	infile.close();
	output.close();
}
