#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Fasta{
public:
	string id;
	string dna;

	void resetInputFileStream(ifstream& fin){
		fin.clear();
		fin.seekg(0, std::ios::beg);
	}

	int getFastaCount(ifstream& fin){
		int fastaCount = 0;
		char check;
		while(fin){
			fin >> check;
			if(check == '>')
				fastaCount++;
		}
		return fastaCount;
	}
	vector<Fasta> table;
	Fasta(){}	
	Fasta(ifstream& fin){
		populateTable(fin);
	}

// public would've gone here

	void populateTable(ifstream& fin){
		int max = getFastaCount(fin);
		resetInputFileStream(fin);
		for(int i = 0; i <= max; i++){
			Fasta f;
			string s;
			getline(fin,f.id);
			while(fin.peek() != '>' and fin){ 
				char c = fin.peek();
				string temp;
				getline(fin,temp);
				f.dna += temp;
			}
			table.push_back(f);
		}
	}

	vector<Fasta> getTable(){
		return table;
	}
	
	void printTable(){
		for_each(table.begin(), table.end(), printFasta);
	}

	static void printFasta(Fasta f){
	//	cout << '\n' << f.id;
		cout << f.dna << '\n';
	}
};
