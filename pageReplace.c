/*
Name: Zoe Baker, Elora Browning
Date: 5/11/24
Description: Implementation of several page replacement algorithms
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_PAGE_REFERENCE_LENGTH 100
#define MAX_PAGE_NUMBER 9
#define DEBUG 0

//Replacement algorithm using First-In First-Out method
int FIFOReplacement(int frames, int testPages[]){
    //Initialize memory
    int memSlots[frames];
    for(int i = 0; i < frames; i++){memSlots[i] = -1;}
    //Keeps track of first page in
    int firstInPointer = 0;
    //Keeps track of faults
    int faultCount = 0;

    //Parsing thru testPages loop
    for(int i = 0; i < 100; i++){
        
        //Check if frame already in memory
        bool frameFound = false;
        for(int j = 0; j < frames; j++){
            if (memSlots[j] == testPages[i]){
                frameFound = true;
            }
        }
        
        //Finding a slot if not in memory
        if(!frameFound){
            //Increment faultCount
            faultCount++;
            for(int j = 0; j < frames; j++){
                //If space is available, insert in free space
                if(memSlots[j] == -1){
                    memSlots[j] = testPages[i];
                    break;
                } else {
                    //If not, replace first in and increment firstInPointer
                    memSlots[firstInPointer] = testPages[i];
                }
            }
            if(firstInPointer >= frames - 1){firstInPointer = 0;}
            else{firstInPointer++;}
        }
        // I used this to look at the frames
        // printf("%d, %d, %d\n", memSlots[0],memSlots[1], memSlots[2]);
    }
    return faultCount;
}

//Replacement algorithm using Least Recently Used method
int LRUReplacement(int frames, int testPages[]){
	//Initialize memory
	int memSlots[frames];
	for(int i = 0; i < frames; i++){memSlots[i] = -1;}
	//Keeps track of faults
	int faultCount = 0;
	
	//Parsing thru testPages loop
	for(int i = 0; i < 100; i++){
		//Check if frame already in memory
		bool frameFound = false;
		for(int j = 0; j < frames; j++){
			if (memSlots[j] == testPages[i]){
				frameFound = true;
				break;
			}
		}
		
		//Finding a slot if not in memory
		if(!frameFound){
			//Increment faultCount
			faultCount++;
			for(int j = 0; j < frames; j++){
				//If space is available, insert in free space
				if(memSlots[j] == -1){
					memSlots[j] = testPages[i];
					break;
				}
				
				//Find least recent item in mem
				for(int k = 0; k < frames; k++){
					if(memSlots[k] == testPages[i - frames + 1]){
						//Replace
						memSlots[k] = testPages[i];
						break;
					}
				}
			}
		}
	}
	return faultCount;
}

//Replacement algorithm using Optimal method
int OPTReplacement(int frames, int testPages[]){
	//Initialize memory
	int memSlots[frames];
	for(int i = 0; i < frames; i++){memSlots[i] = -1;}
	//Keeps track of faults
	int faultCount = 0;
	
	//Parsing thru testPages loop
	for(int i = 0; i < 100; i++){
		
		//Check if frame already in memory
		bool frameFound = false;
		for(int j = 0; j < frames; j++){
			if (memSlots[j] == testPages[i]){
				frameFound = true;
				break;
			}
		}
		
		//Finding a slot if not in memory
		if(!frameFound){
			//Increment faultCount
			faultCount++;
			//Tracks page of value to be replaced
			int oldValue = -1;
			for(int j = 0; j < frames; j++){
				//If space is available, insert in free space
				if(memSlots[j] == -1){
					memSlots[j] = testPages[i];
					break;
				}
				//If not, replace least soon to be used
				//Parse memory space
				for(int k = 0; k < frames; k++){
					//For each num in mem, find how far the next use is
					//Parse list for next
					for(int n = i + 1; n < 100; n++){
						if(memSlots[k] == testPages[n]){
							//If value is farther away, overwrite
							if(n > oldValue){
								oldValue = n;
							}
							break;
						}
					}
				}
			//Replace tracker value with new value
			memSlots[oldValue] = testPages[i];
			}
		}
	}
	return faultCount;
}

int main(int argc, char *argv[]) {
    int testPages[] = {8,3,8,7,4,7,8,2,9,0,3,2,6,3,8,1,3,7,3,5,1,1,8,9,7,0,9,6,6,8,8,4,4,9,1,0,7,3,8,0,5,8,8,4,4,4,4,8,4,5,9,9,5,1,4,3,0,8,0,0,7,1,2,3,8,3,4,9,4,1,6,8,2,8,1,6,6,9,2,2,0,3,6,6,5,1,3,0,8,7,6,1,9,1,6,6,1,3,7,0};
	//Check - user input should have 1-2 vals:
	//1 - number of frames
	//2 - seed (optional)
	
	//If user input does not comply, give error message and quit
	if(!(argc == 2 || argc == 3)){
		printf("ERROR: Incorrect parameters. Please provide (1) a number of frames and, optionally, (2) a seed.\n");
		exit(1);
	}
	//Record frames
	int numFrames = atoi(argv[1]);
	
	//Check for optional seed value and
	//generate numbers if necessary
	if(argc == 3){
		int seed = atoi(argv[2]);
		srand(seed);
		for(int i = 0; i < 100; i++){
						//(UBound - LBound + 1) +LBound
			int randNum = rand() % (9 - 0 + 1) + 0;
			testPages[i] = randNum;
		}
	}


	//Call algorithm functions
	int FIFOFaults = FIFOReplacement(numFrames, testPages);
	int LRUFaults = LRUReplacement(numFrames, testPages);
	//int OPTFaults = OPTReplacement(numFrames, testPages);


	//Print results
	printf("Algorithm\t#Page Faults\n");
	printf("FIFO\t\t%d\n", FIFOFaults);
	printf("LRU\t\t%d\n", LRUFaults);
	//printf("OPT\t\t%d\n", OPTFaults);
    return 0;
}
