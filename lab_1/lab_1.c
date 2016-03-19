#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//numero de letras a se considerar
#define NUM_LETTERS 26
//constante mágica que converte uma letra pra seu respectivo índice em um vetor
#define LETTER_TO_IDX 65
//tamanho máximo da entrada
#define MAX_INPUT_LEN 1000

//soma todos os valores de um vetor de inteiros
int sum(int* array, int n)
{
	int i;
	int result = 0;

	for(i=0; i<n; i++)
		result += array[i];

	return result;
}

//determina o número mínimo de pilhas a se usar para o problema dos conteiners
int min_num(const char* seq, int seq_size)
{
	int i, j, index;
	int letters[NUM_LETTERS];

	memset(letters, 0, NUM_LETTERS*sizeof(int));

	for(i=0; i<seq_size; i++)
	{
		index = seq[i] - LETTER_TO_IDX;

		//verifica se já há uma pilha para a letra da vez.
		//verifica também se é possível empilha-la em uma pilha já existente
		for(j=index; j<NUM_LETTERS; j++)
			if(letters[j])
			{
				letters[j] = 0;
				letters[index] = 1;
				break;
			}

		if(j == NUM_LETTERS)
			letters[index] = 1;
	}

	return sum(letters, NUM_LETTERS);
}

int main()
{
	int num;
	char input[MAX_INPUT_LEN+1];

	scanf("%s", input);
	num = min_num(input, strlen(input));
	printf("%d\n", num);
	
	return 0;
}
