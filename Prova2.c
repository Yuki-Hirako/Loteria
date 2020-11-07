#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#define l 25
//erro na linha 178, e 251 dois param�tros pra um %d s�.

bool VerificaNulos (int *);

int main (){
	setlocale (LC_ALL, "PORTUGUESE");
	FILE *jog, *res, *final;
	char aux [4];
	bool nulos;
	int loteria[l][6], j=0, i=0, aux2;
	int resul[6], acertos[l], nJogados[60], x=0, pontos=0, a6=0, a5=0, a4=0, mais, menos;
	float premio, premio6, premio5, premio4;
	
	jog = fopen ("jogos.txt", "r");
	// Percorre o arquivo de jogos.txt converte pra int e preenche a matriz "loteria";		
	while (fgets (aux,4,jog) != NULL){
		aux2 = atoi (aux);
		loteria [j][i] = aux2;  
		i++;
		if (i==6){
			i=0;
			j++;
		}	
	}
	fclose(jog);
	
	// Mostra a matriz "loteria" que pegou os valores do arquivo jogos.txt;
	/*for (j=0; j<l; j++){
		printf ("Jogo %d: ", j+1);
		for (i=0; i<6; i++){
			printf ("%3d ", loteria[j][i]); 
		}
		printf ("\n");
	}*/
	
	res = fopen ("resultado.txt", "r");
	i=0;
	// Percorre o arquivo de resultado.txt converte pra int e preenche o vetor de "resul[]";
	while (fgets (aux,4,jog) != NULL){
		aux2 = atoi (aux);
		resul[i] = aux2;  
		i++;
	}
	fclose(res);
	
	// Mostra o vetor "resul" que pegou os valores do arquivo resultado.txt;
	/*printf ("\n\nRESULTADO:");
	for (i=0;i<6;i++){
		printf("%3d ", resul[i]);
		acertos[i]==0;
	}*/
	
	//Recebe o valor do pr�mio a ser dividido entre os acertadores
	printf ("Valor do pr�mio: R$");
	scanf ("%f", &premio);
	
	//Conta quantos acertos teve em cada jogo e armazena no vetor "acertos[]"
	//Cada linha da matriz "Loteria[][]" representa um jogo diferente, ent�o para o vetor "acertos[]",
	//cada posi��o armazena quantos pontos foram obtidos por jogos
	//------ LOTERIA -----
	//EX: C [0] [1] [2] [3] [4] [5]
	//L [0] 03  09  12  35  43  53
	//	
	// ----- ACERTOS ---- 
	//	[0] [1] [2] ...
	//V  6  ... ... 
	for (j=0;j<l;j++){
		pontos=0;
		for (x=0;x<6;){
			if (loteria[j][i] == resul[x]){
				pontos++;
				x++;
				i=0;
			}else {
				i++;
				if(i==6){
					x++;
					i=0;
				}
			}
		}
		acertos[j]=pontos;	
	}
	
	//Mostra quantos acertos cada jogador conseguiu
	/*printf ("\n\n");
	for (i=0;i<l;i++){
		printf("\nJogador %d acertou: %3d ",i+1, acertos[i]);
	}*/
	
	//Conta quantos jogos tiveram 6, 5 e 4 acertos e armazena em "a6", "a5", e "a4" respectivamente
	for (i=0;i<l;i++){
		if (acertos[i]==6){
			a6++;
		}else if (acertos[i]==5) {
				a5++;
			}else if (acertos[i]==4){
				 	a4++;	
				}
	}
	
	//Mostra quantos jogos tiveram 6, 5 e 4 acertos
	printf("\nJogos com 6 acertos: %3d ", a6);
	printf("\nJogos com 5 acertos: %3d ", a5);
	printf("\nJogos com 4 acertos: %3d ", a4);
	
	for (i=0;i<60;i++){
		nJogados [i]=0;
	}
	
	//Conta quantas vezes cada n�mero da loteria se repete e armazena no vetor de "nJogados[60]"
	//Cada posi��o do vetor representa um n�mero da loteria, onde: 
	//posi��o [0] armazena quantas vezes o n�mero 1 foi jogado, 
	//posi��o [1] armazena quantas vezes o n�mero 2 foi jogado,
	//e assim por diante at� a posi��o [59]. 
	for (j=0;j<l;j++){
		for (x=0,i=0;i<6;x++){
			if (loteria[j][i]==x+1){
				nJogados[x]++;
				x=0;
				i++;	
			}
		}
	}
	
	//Mostra quantas vezes os n�meros de 01 a 60 se repetiram (TABULADO)
	printf ("\n\nQuantas vezes os n�meros de 01 a 60 se repetem:\n");
	for (j=0;j<6;j++){
		printf (" | N�mero | Repete | ");
	}
	printf ("\n");
	i=1;
	for (j=0;j<10;){
		printf (" |%-8d|%7dx| ", i+j, nJogados[(i+j)-1]);
		i+=10;
		if ((i+j)>=61){
			printf ("\n");
			j++;
			i=1;
		}
	}
	
	//Verifica qual o n�mero mais jogado
	aux2=nJogados[0];
	for (i=0;i<60;i++){
		if (nJogados[i]>aux2){
			aux2=nJogados[i];
			mais=i+1;
		}
	}
	//Verifica qual o n�mero menos jogado
	aux2=nJogados[0];
	for (i=0;i<60;i++){
		if (nJogados[i]<aux2){
			aux2=nJogados[i];
			menos=i+1;
		}
	}
	
	//Mostra os n�meros mais e menos jogados
	printf ("\n\nO n�mero mais jogado � o %d, e o menos jogado � o %d", mais, menos);
	
	
	//Chama a fun��o "VerificaNulos" para verificar se h� algum n�mero (entre 01 e 60) que n�o apareceu em nenhum jogo 
	nulos = VerificaNulos(nJogados);
	//Se a fun��o retornar "false" quer dizer que H� NULOS
	if (!nulos){
		printf ("\n\nO(s) n�mero(s) ");
		for (i=0;i<60;i++){
			if (nJogados[i]==0){
				printf ("%d, ", i+1);
			}
		}
		printf ("n�o aparece(m) em nenhum jogo!\n");
	}else {
		printf ("\n\nTodos os n�meros de 01 � 60 foram jogados!\n");
	}
	
	//Calcula e mostra o valor do pr�mio que cada acertador ir� receber
	if (a6!=0){
		if (a6>1){
			premio6=(premio*0.85)/a6;
			printf ("\n%d jogadores receber�o R$%.2f cada (6 acertos)", a6, premio6);
		}else {
			premio6=(premio*0.85);
			printf ("\n%d jogador receber� R$%.2f (6 acertos)", a6, premio6);
		}
	}else{
		premio6=(premio*0.85);
		printf ("\nNenhum jogo com 6 acertos! Pr�mio de R$%.2f acumulado!!!", premio6);
	}
	
	if (a5!=0){
		if (a5>1){
			premio5=(premio*0.10)/a5;
			printf ("\n%d jogadores receber�o R$%.2f cada (5 acertos)", a5, premio5);
		}else {
			premio5=(premio*0.10);
			printf ("\n%d jogador receber� R$%.2f (5 acertos)", a5, premio5);
		}
	}else{
		premio5=(premio*0.10);
		printf ("\nNenhum jogo com 5 acertos! Pr�mio de R$%.2f acumulado!!!", premio5);
	}
			
	if (a4!=0){
		if (a4>1){
			premio4=(premio*0.05)/a4;
			printf ("\n%d jogadores receber�o R$%.2f cada (4 acertos)\n\n\n", a4, premio4);
		}else {
			premio4=(premio*0.05);
			printf ("\n%d jogador receber� R$%.2f (4 acertos)\n\n\n", a4, premio4);
		}
	}else{
		premio4=(premio*0.05);
		printf ("\nNenhum jogo com 4 acertos! Pr�mio de R$%.2f acumulado!!!\n\n\n", premio4);
	}
	
	system("pause");
					
	//Armazena as informa��es no arquivo SAIDA.txt
	final = fopen ("SAIDA.txt", "a+");
	fprintf (final, "Acertaram 6 n�meros: %d", a6);
	fprintf (final, "\nAcertaram 5 n�meros: %d", a5);
	fprintf (final, "\nAcertaram 4 n�meros: %d", a4);
	fprintf (final, "\n\nQuantas vezes os n�meros de 01 a 60 se repetem:\n");
	for (j=0;j<6;j++){
		fprintf (final, " | N�mero | Repete | ");
	}
	fprintf (final, "\n");
	i=1;
	for (j=0;j<10;){
		fprintf (final, " |%-8d|%7dx| ", i+j, nJogados[(i+j)-1]);
		i+=10;
		if ((i+j)>=61){
			fprintf (final, "\n");
			j++;
			i=1;
		}
	}
	fprintf (final, "\n\nO n�mero mais jogado � o %d, e o menos jogado � o %d", mais, menos);
	if (!nulos){
		fprintf (final, "\n\nO(s) n�mero(s) ");
		for (i=0;i<60;i++){
			if (nJogados[i]==0){
				fprintf (final, "%d, ", i+1);
			}
		}
		fprintf (final, "n�o aparece(m) em nenhum jogo!");
	}else {
		fprintf (final, "\n\nTodos os n�meros de 01 � 60 foram jogados!");
	}	
	
	if (a6!=0){
		if (a6>1){
			premio6=(premio*0.85)/a6;
			fprintf (final, "\n%d jogadores receber�o R$%.2f cada (6 acertos)", a6, premio6);
		}else {
			premio6=(premio*0.85);
			fprintf (final, "\n%d jogador receber� R$%.2f (6 acertos)", a6, premio6);
		}
	}else{
		premio6=(premio*0.85);
		fprintf (final, "\nNenhum jogo com 6 acertos! Pr�mio de R$%.2f acumulado!!!", premio6);
	}
	
	if (a5!=0){
		if (a5>1){
			premio5=(premio*0.10)/a5;
			fprintf (final, "\n%d jogadores receber�o R$%.2f cada (5 acertos)", a5, premio5);
		}else {
			premio5=(premio*0.10);
			fprintf (final, "\n%d jogador receber� R$%.2f (5 acertos)", a5, premio5);
		}
	}else{
		premio5=(premio*0.10);
		fprintf (final, "\nNenhum jogo com 5 acertos! Pr�mio de R$%.2f acumulado!!!", premio5);
	}
			
	if (a4!=0){
		if (a4>1){
			premio4=(premio*0.05)/a4;
			fprintf (final, "\n%d jogadores receber�o R$%.2f cada (4 acertos)", a4, premio4);
		}else {
			premio4=(premio*0.05);
			fprintf (final, "\n%d jogador receber� R$%.2f (4 acertos)", a4, premio4);
		}
	}else{
		premio4=(premio*0.05);
		fprintf (final, "\nNenhum jogo com 4 acertos! Pr�mio de R$%.2f acumulado!!!", premio4);
	}
	fclose(final);
		
	return 0;
}

bool VerificaNulos(int *nJogados){
	int i;
	bool b=true;
	for(i=0;i<60;i++){
		if (nJogados[i]==0){
			b=false;
		}	
	}
	return b;
}
