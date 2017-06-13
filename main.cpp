#include "cp.h"

int main(){
	ifstream fin;
	fin.open("rosalind_cons.txt");
	
	Fasta f;
	f.populateTable(fin);
	ConsensusProfile *cp = new ConsensusProfile(f);
	return 0;
}
