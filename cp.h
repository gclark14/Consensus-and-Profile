#include "Fasta.h"

class ConsensusProfile{
private:
	ofstream fout;
	struct BasePairs{
		int A = 0; 
		int C = 0;
		int G = 0;
		int T = 0;
	};
	vector<BasePairs> bp;
	string consensus = "";

	/** It is one column sohrt on the consensus profile */
	void populateBasePairs(){
		bp.resize(fasta.table.at(0).dna.length()+1);
		for(int i = 0; i < fasta.table.size(); i++){ 
			for(int j = 0; j < fasta.table.at(i).dna.length(); ++j){
				cout << ' ' << fasta.table.at(i).dna.at(j);
				if(fasta.table.at(i).dna.at(j) == 'A')
					bp.at(j).A++;
				if(fasta.table.at(i).dna.at(j) == 'C')
					bp.at(j).C++;	
				if(fasta.table.at(i).dna.at(j) == 'G')
					bp.at(j).G++;
				if(fasta.table.at(i).dna.at(j) == 'T')
					bp.at(j).T++;
			}
			cout << '\n';
		}
	}

	void getLargestBp(){
		int placeHolder = 0;
		for(int i = 0; i < bp.size()-1; i++){
			int largest = 0;
			if(bp.at(i).A > largest){
				placeHolder = 1; 
				largest = bp.at(i).A;
			}	
			if(bp.at(i).C > largest){
				placeHolder = 2;
				largest = bp.at(i).C;
			}
			if(bp.at(i).G > largest){
				placeHolder = 3;
				largest = bp.at(i).G;
			}
			if(bp.at(i).T> largest){
				placeHolder = 4;
				largest = bp.at(i).T;
			}
			createConsensus(placeHolder);
		}
	}


public:
	Fasta fasta;
	ConsensusProfile(){}
	ConsensusProfile(Fasta fasta){
		this->fasta = fasta;
		populateBasePairs();
		getLargestBp();
		fout.open("save.txt");
		printBasePairsToFile();
		displayDnaStringLength();
		fout.close();
	}
	
	void printBasePairsToFile(){
		fout << '\n' << consensus; 
		fout << "\nA:";
		for(int i = 0; i < bp.size()-1; i++){
			fout << ' ' << bp.at(i).A;
		}

		fout << "\nC:"; 
		for(int i = 0; i < bp.size()-1; i++){
			fout << ' ' << bp.at(i).C; 
		}

		fout << "\nG:"; 
		for(int i = 0; i < bp.size()-1; i++){
			fout << ' ' << bp.at(i).G; 
		}

		fout << "\nT:"; 
		for(int i = 0; i < bp.size()-1; i++){
			fout << ' ' << bp.at(i).T;
		}
	}

	void createConsensus(int placeHolder){
		if(placeHolder == 1)
			consensus += "A"; 
		if(placeHolder == 2)
			consensus += "C";
		if(placeHolder == 3)
			consensus += "G";
		if(placeHolder == 4)
			consensus += "T";
	}
	
	void displayDnaStringLength(){
		cout << "\nconsensus length: " << consensus.length() << '\n';
		cout << "old dna length: " << fasta.table.at(0).dna.length() << '\n';
	}
};
