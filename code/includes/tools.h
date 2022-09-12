/*
constante de préprocesseur qui permet de ne pas inclure de 
manière infinie, d'inclure les fichiers dans le bon ordre.
*/
#ifndef __TOOLS__H__
#define __TOOLS__H__

// Structure qui va permettre de stocker les données récupérées.
typedef struct Data
{
	int   aged;     // Stock l'âge.
	char  prof[10]; // Stock la profession.
	float surf;     // Stock la surface.
}Data;

// Structure qui va permettre de stocker les données de la fonction par index.
typedef struct ValueIndexArray
{
    unsigned int *value;
    unsigned int *index;
    unsigned int  size;
} ArrayIndex;

// Structure qui va permettre de stocker les données de la fonction par dichotomie.
typedef struct ValueDichoArray
{
	bool find;			// vaut faux tant que la valeur "val" n'aura pas été trouvée.
	unsigned int id;	// indice de début.
	unsigned int idEnd; // indice de fin.
	unsigned int idMid; // indice de "milieu".
} ArrayDicho;

// Structure qui va permettre de stocker les données de la fonction pour mélanger.
typedef struct ValueshufflerArray
{
	unsigned int line;  // nombre de ligne.
    unsigned int index; // valeur aléatoire.
} Arrayshuffler;

// Prototype des fonctions.	
void Get_data_in(Data *data, char *line);
void Call_tri(Data *dataArray, clock_t timer);
void shuffler(Data *dataArray);

void Sort_data_Bubble(Data *dataArray);
void Sort_data_insertion(Data *dataArray);
void Quick_sort(Data *dataArray, unsigned int size);
void Sort_selection(Data *dataArray, unsigned int taille);


void Print_ArrayIndex(ArrayIndex data);
void Free_ArrayIndex(ArrayIndex data);
void freeCloseFile(Data *dataArray, FILE *registerFile, FILE *getDataTranscriptFile, FILE *sortTranscriptFile);

Data* Find_entity(Data *dataArray, const char *toFind);
ArrayIndex Find_entity_index(Data *dataArray);
bool Find_entity_dicho(Data *dataArray, const char *toFind);
// float Interpole(Data *dataArray, unsigned int i, unsigned int j, const char *toFind);
#endif