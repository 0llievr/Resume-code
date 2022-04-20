//Oliver Lynch
//project 4 SAIS
//10 April 2020
#include<iostream>
#include<string>
#include<vector>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

bool compareLMS(vector<int> Tint, vector<int> SL, int cur, int prv){
	//cout << "curr: " << cur << " Prev: " << prv << endl;
	int size = Tint.size()-1;
	bool same = true;

	while(same){
		if( SL[cur] != SL[prv]){ //if one ends and the other dosnt
			same = false;
			return false;
		}if(Tint[cur] != Tint[prv]){ //if the char are not the same
			same = false;
			return false;
		}if(same){//if it hasnt found a diffrence move up
			if( cur < size && prv < size){ //dont go over size + incrment up
				cur++;
				prv++;
			}if(SL[cur] == 1 && SL[prv] == 1){ //if they both hit end
				if(SL[cur-1] != 1 && SL[prv -1] != 1){ //this line of code took me 20+ hours to figure out it needed to be here
					if(Tint[cur] == Tint[prv]){ //and the char is the same
						same = false; //they are the same
						return true;
					}
				}
			}		
		}
	}
	printf("error\n");
	return true;
}

void SAIS( const vector<int> &Tint, vector<int> &SA, int alphabetSize, int iter){
	int size = Tint.size()-1;
	//vector<int> T (Tint); //make a copy of Tint becuase there is no god

	iter++;
	//cout << "Iteration " << iter << endl;
	//cout << "T at iteration " << iter << endl; for(int i = 0; i < (int)Tint.size(); i++)
	//cout << Tint[i] << " " ; cout << endl;

//Termination condition
	if(size == alphabetSize){
		for(int i = 0; i < (int)SA.size(); i++){
			SA[Tint[i]] = i;
		}
		return;
	}
//calculate buckets
	vector<int>A(alphabetSize+1, 0);
	vector<int>B(alphabetSize+1, 0);
	vector<int>C(alphabetSize+1, 0);
	//Make A
	for(int i=0; i <= size; i++){
		A[Tint[i]]++;
	}
	//Make C
	C[0] = 0;
	for(int i = 1; i <= alphabetSize; i++){
		C[i] = C[i-1] + A[i-1];
	}
	//Make B
	for(int i = 1; i <= alphabetSize; i++){
		B[i] = B[i-1]+A[i];
	}
	vector<int>BC (B); //B Copy

//step 0: calculate SL vector
	vector<int> SL (size+1, -1);
    SL[size] = 1;
	SL[size-1] = 0;

	//clear SA
	fill(SA.begin(), SA.end(), -1);
	SA[0] = size;

	//find SL type; L = 0 S = 1
	for(int i=size-2; i >= 0; i--){
		if(Tint[i]>Tint[i+1]){//L type
			SL[i] = 0;
			if(SL[i+1] == 1){//if LMS type
				SA[B[Tint[i+1]]] = i+1;
				B[Tint[i+1]]--;
			}
		}else if(Tint[i] == Tint[i+1]){//check prev
				SL[i] = SL[i+1];
                		if(SL[i+1] == 1 && SL[i] == 0){//if LMS type
                			SA[B[Tint[i+1]]] = i+1;
							B[Tint[i+1]]--;
                		}
		}else{//S type
			SL[i] = 1;
		}
	}
//Step 1: Sort LMS substrings
	//Recalculate B to head of c bucket
	for(int i = 0; i <= alphabetSize; i++){
		B[i] = C[i];
	}
 
	//induce sort L type
	for(int i = 0; i <= size; i++){
		if(SA[i] > 0){
			int p = SA[i];
			if(SL[p-1] == 0){
				SA[B[Tint[p-1]]] = p-1;
				B[Tint[p-1]]++;
			}
		}
	}
	SA[0]=size;
	//induce sort S type
	for(int i = size; i >= 0; i--){
		if(SA[i] > 0){
			int p = SA[i];
			if(SL[p-1] == 1){
				SA[BC[Tint[p-1]]] = p-1;
				BC[Tint[p-1]]--;
			}
		}
	}
	/*
	cout << "Type array:" << endl;
	for(int j = 0 ; j < (int)Tint.size(); j++){
		cout << SL[j] << " " ; 
	}
	cout << endl;

	cout << "LMS prefixes are sorted.\nSA at iteration " << iter << endl; for(int i = 0; i < (int)Tint.size(); i++)
	cout << SA[i] << " " ; cout << endl;
	*/


//Step 2: Find LMS Substrings
	int prv = SA[0];
	vector<int> N (size+1, -1);
	N[size] = 0;

	for(int i = 1; i <= size; i++){
		int cur = SA[i]; //current
		if(cur !=0 && SL[cur] == 1 && SL[cur-1] == 0){

			if(compareLMS(Tint, SL, cur, prv)){
				//the same
				N[cur] = N[prv];
				prv = cur;
			}else{
				//diffrent
				N[cur] = N[prv]+1;
				prv = cur;

			}
		}
	}

	//create and print T1
	vector<int> T1;
	for(int i = 0; i <= size; i++){
		if(N[i] != -1){
			T1.push_back(N[i]);	
		}
	}
	//cout << "T1 at iteration " << iter << endl; for(int i = 0; i < (int)T1.size(); i++)
	//cout << T1[i] << " " ; cout << endl;


//step 3: Recursive call
	//find new alphabet size
	int newAlphS = 0;
	for(int i : T1){
		if(i > newAlphS){
			newAlphS = i;
		}
	}
	//cout << "newAlphS: " << newAlphS << " T1 Size: " << (int)T1.size() << endl;
	//recurse condition
	vector<int>SA1((int)T1.size(), -1);
	if((int)T1.size() < newAlphS){
		//if all char are diffrent
		for(int i = 0; i < (int)SA.size(); i++){
			SA1[T1[i]]= i;
		}

	}else{
		//cout << "Iteration " << iter << ". Recursive call on T1." << "\n********************************************" << endl;
		SAIS(T1, SA1, newAlphS, iter);
	/*	cout << "\n********************************************"<< "\nAfter recursive call inside iteration " << iter << endl;
		cout << "SA1 at iteration " << iter << " (after recursive call) is:" << endl; 
		for(int i = 0; i < (int)SA1.size(); i++)
			cout << SA1[i] << " " ; 
		cout << endl;
		*/
	}

//step 4: After recurse
	//for some reason the original tint gets corrupted here so use the copy T from here out 
	// re-initalize SA to -1
	for(int i=0; i <= size; i++){
		SA[i] = -1;
	}
	
	//remake B and BC
	for(int i = 0; i<= alphabetSize; i++){ //inintalize to 0
		B[i] = BC[i] = 0;
	}for(int i = 1; i <= alphabetSize; i++){
		BC[i] = C[i];
		B[i] = B[i-1]+A[i]; //it works here too
	}
	B[0] = 0;

	//Overwrite T1 with the starting positions of LMS-substrings in T using t-array
	int inc = 0;
	for(int i = 1; i <= size; i++){
		if(SL[i] == 1 && SL[i-1] == 0){
			T1[inc] = i;
			inc ++;
		}
	}
	
	//Place positions of LMS substrings into SA using their relative order from SA1
	for (int i = SA1.size()-1; i >= 0; i--){
		SA[ B[ Tint[ T1[ SA1[ i ]]]]--] = T1[SA1[i]];
	}

	//induce sort L type
	for(int i = 0; i <= size; i++){
		if(SA[i] > 0){
			int p = SA[i];
			if(p-1 == -1){
				p = SA.size();
			}
			if(SL[p-1] == 0){
				SA[BC[Tint[p-1]]] = p-1;
				BC[Tint[p-1]]++;
			}
		}
	}
	SA[0]=size;

	//rebuild B
	for(int i = 0; i<= alphabetSize; i++){ //inintalize to 0
		B[i] = 0;
	}for(int i = 1; i <= alphabetSize; i++){
		B[i] = B[i-1]+A[i];
	}B[0] = 0;

	//induce sort S type
	for(int i = size; i >= 0; i--){
		if(SA[i] > 0){
			int p = SA[i];
			if(p-1 == -1){
				p = SA.size();
			}
			if(SL[p-1] == 1){
				SA[B[Tint[p-1]]] = p-1;
				B[Tint[p-1]]--;
			}
		}
	}
	/*
	cout << "SA at the end of SAIS function just before the return at iteration " << iter <<endl;
	for(int i = 0; i < (int)SA.size(); i++) 
		cout << SA[i] << " " ;
	cout << endl;
	*/
	return ;
}

int main(){	
//get input 
		string aline;
	string T;
	//get all of input file even if it has \n
	while(getline(cin,aline)){
		T = T + aline;
	}

//convert letters to numbers w/ custom alphabet
	//mark charictors with letters in T
	vector<int> count(256,0);
	for(int i = 0; i < (int)T.size(); i++){
		count[T[i]] = 1;
	}

	//if char is used in the string give it a number
	int curName = 1;
	for( int i = 0; i < 257; i++){
		if(count[i] == 1){
			count[i] = curName++;
		}
	}

	//assign thoes numbers to the base string
	vector<int> Tint;
	int alphabetSize = 0;
	for(int i = 0; i < (int)T.size(); i++){	
		Tint.push_back(count[T[i]]);
		if(count[T[i]] > alphabetSize){//get the size of tha alphabet
			alphabetSize = count[T[i]];
		}
	}
	Tint.push_back(0);

//Call SAIS
	vector<int> SA(Tint.size(), -1);
	int iter = 0;
	SAIS(Tint, SA, alphabetSize, iter);

//Print BWT
	for(int i = 0; i < SA.size(); i++){
		int p = SA[i];
		if(p != 0){
			cout << T[p-1];
		}
	}cout << endl;

	return 0;
}


























