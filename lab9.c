#include <stdio.h>
#include <stdlib.h>

int TABLE_SIZE = 15;

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* record;
	struct RecordType* nextRecord;
};
// Compute the hash function
int hash(int x)
{
	return x % TABLE_SIZE;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		struct RecordType* r;

		// if index is occupied with any records, print all
		while(pHashArray[i].nextRecord != NULL) {
			printf("hehe%d -> %d, %c, %d", i, r->id, r->name, r->order);
			if(pHashArray[i].nextRecord != NULL) {
				r = pHashArray[i].nextRecord;
			} else {
				break;
			}
		}	
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	//declare hash table 
	struct HashType* hashtable = malloc(sizeof(struct HashType) * TABLE_SIZE);

	printf("YEP");

	//add all records to hashtable
	for(int i = 0; i < recordSz; i++){
		//generate hash key
		int key = hash(pRecords[i].order);

		//if no entry at this point, insert record here
		if(hashtable[key].record != NULL){
			hashtable[key].record = &pRecords[i];
			hashtable[key].nextRecord = NULL;
		} else {
			//else add as next link in linked list at index key
			
			//loop to final link
			struct RecordType* r;
			while(hashtable[key].nextRecord != NULL){
				r = hashtable[key].nextRecord;
			}

			//add next link
			hashtable[key].nextRecord = &pRecords[i];
		}
	}

	displayRecordsInHash(hashtable, TABLE_SIZE);
	return 0;
}