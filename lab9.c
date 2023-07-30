#include <stdio.h>
#include <stdlib.h>

int TABLE_SIZE = 15;

// LinkedList
struct RecordLink
{
	struct RecordType* record;
	struct RecordLink* next;	
};

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
	struct RecordLink* recordList;
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

//helper function for printing a hash-index and a record
void printRecord(int i, struct RecordType* r){
	printf("%d -> %d, %c, %d", i, r->id, r->name, r->order);
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
		struct RecordLink* recLink;
		struct RecordType* rec;

		recLink = pHashArray[i].recordList;

		// if index is occupied with any records, print all
		while(recLink != NULL) {
			rec = recLink->record;
			printRecord(i, rec);

			if(recLink->next != NULL) {
				recLink = recLink->next;
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

	//make all links NULL to start
	for(int i = 0; i < TABLE_SIZE; i++){
		hashtable[i].recordList = malloc(sizeof(struct RecordLink));
		hashtable[i].recordList->record = NULL;
	}

	//add all records to hashtable
	for(int i = 0; i < recordSz; i++){

		//generate hash key
		int key = hash(pRecords[i].order);
		//printf("key generated: %d\n", key);

		//if no entry at this point, insert record here
		if(hashtable[key].recordList->record == NULL){
			hashtable[key].recordList = malloc(sizeof(struct RecordLink));
			hashtable[key].recordList->record = &pRecords[i];
			hashtable[key].recordList->next = NULL;
		} 
		
		//else add as next link in linked list at index key
		else {
					
			//loop to final link
			struct RecordLink* r = hashtable[key].recordList;
			while(r->next != NULL){
				r = r->next;
				//printf("looping to last link\n");
			}

			//add next link
			r = malloc(sizeof(struct RecordLink));
			r->record = &pRecords[i];
			r->next = NULL;
		}
	}
	displayRecordsInHash(hashtable, TABLE_SIZE);
	return 0;
}