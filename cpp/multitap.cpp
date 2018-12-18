#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

#include "multitap.h"

int encode_character(char c, char* multitap){

	//If the key has less than 4 characters, put a 1 behind which will automatically fail
	char key[9][5] = {{".,!?"},{"abc1"},{"def1"},{"ghi1"},{"jkl1"},{"mno1"},{"pqrs"},{"tuv1"},{"wxyz"}};
	
	//Records which position of multitap it needs to "fill"
	int pos = 0;	
	
	//record the key required
	char button;

	//First check whether input is a digit
	if(isdigit(c)){
		multitap[pos] = '*';
		pos++;
		multitap[pos] = c;
		pos++;
		multitap[pos] = '\0';

		return pos;
	}

	//Check whether it's a symbol or space
	if(!isalpha(c)){
		if(c ==' ' ){
			multitap[pos] = '0';
			pos++;

		}else{
			for(int i = 0; i <4; i++){
				//If key found fill required places
				if(c == key[0][i]){
					for(int j=0; j<i+1; j++){
						multitap[pos] = '1';
						pos++;
					}
				}		
			}
		}

		multitap[pos] = '\0';
		return pos;
	}

	//Check whether it's uppercase
	if(!islower(c)){
		multitap[pos] = '#';
		pos++;
		c = tolower(c);
	}

	//At this point the input will be a lowercase alphabet
	for(int i = 1; i<9;i++){
		for(int j = 0; j<4;j++){
			if(c == key[i][j]){
				//button = (char) i;

				button = i+1 +'0';

				for(int k = 0; k<j+1;k++){
					multitap[pos] = button;
					pos++;
				}
				multitap[pos] = '\0';
				return pos;
			}
		}
	}
	
	cerr << "Unknown error" << endl;
	return -1;
}


void encode(char* plaintext, char* multitap){
	//Iterative version
	//Counter for position in plaintext
	int i =0;
	
	//Counter for where the previous letter is
	int j= 1;

	//Holds a temp buffer
	char temp[5];
	temp[0] = '\0';
	
	//Holds a total position counter
	int pos=0;

	//Holds the number of characters
	int count =0;

	while(plaintext[i] != '\0'){
		count = encode_character(plaintext[i],temp);

		if(i >0){
			while(i-j>0 && !isalpha(plaintext[i-j])&& !isdigit(plaintext[i-j])){
				j++;
			}
			//Check whether going from upper -> lower
			if(plaintext[i-j] != ' ' && !(islower(plaintext[i-j])) && islower(plaintext[i])){
				multitap[pos] = '#';
				pos++;
				strcpy(&multitap[pos],temp);
				pos += count;
			
			//Check whether going from upper -> upper
			}else if(plaintext[i-j]!=' ' && !(islower(plaintext[i-j])) && !(islower(plaintext[i]))){
			
				if(multitap[pos-1] == temp[1]){
					multitap[pos] = '|';
					pos++;
				}
				strcpy(&multitap[pos],&temp[1]);
				pos += count -1;
				
			//Lower -> lower or lower -> upper
			}else{
				if(multitap[pos-1] == temp[0] && temp[0]!='0'){
					multitap[pos] = '|';
					pos++;
				}
			strcpy(&multitap[pos],temp);
			pos +=count;
			}
		}else{
		strcpy(multitap,temp);
		pos+=count;
		}

		i++;
		j=1;
	}
	return;
}
