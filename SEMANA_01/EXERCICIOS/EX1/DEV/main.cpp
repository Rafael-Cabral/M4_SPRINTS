/*
Esse exercício foi pensado em conjunto com outros alunos da sala, o Gabriel Carneiro me ajudou bastante a entender 
o que estava sendo pedido.
*/


#include <iostream>
#include <string>

using namespace std;

// Aqui nós vamos armazenar as direções e o nome
char *nomeDirecoes[4] = {(char *) "Frente", (char *) "Trás", (char *) "Direita", (char *) "Esquerda"};

// Aqui nós vamos receber um valor e calcular a sua porcentagem em um intervalo
int rangeSensor(int valor, int minimo, int maximo) {
	int intervalo = maximo - minimo;
    int porcentagem = (valor*100)/intervalo;
    
	return porcentagem;
}


// Aqui nós vamos receber um valor e armazenar no vetor junto com a sua posição. Além disso, vamos
// verificar um valor máximo para ver se o valor inserido está dentro do vetor
int insereVetor(int valor, int* vetor, int valorMaximo, int posicao) {
    if (valorMaximo > posicao) {         
		vetor[posicao] = valor;  
		posicao += 1; // após inserir o valor no vetor, atualizamos a posição atual e retornamos ela
	}

	return posicao;
}

// Aqui nós vamos varificar se quer continuar ou não
int resposta() { 
    char resposta; 
	printf("Quer continuar? [s/n]");
	scanf("%c", resposta)
    if (resposta == 's' || 'S') {
        return 1;
    } else {
        return 0; 
    }
}




// Aqui nós vamos verifiar se o usuário quer continuar dirigindo e executar o loop
int dirige(int *v,int maxv){
    int vetorMaximo = maxv;
    int *vetorMov = v;

    int mapeamento = 1;
    int dirigindo = 1; 
    int posicaoAtual = 0;


    while(dirigindo) {
            printf("Mapeamento %d \n", mapeamento);
            
            int medida; 

            // Aqui nós coletamos as quatro direções e chamamos a função insereVetor
            for (int i = 0; i < 4; i++) {  
                printf("Digite a distância do robô até o lado %s: ", nomeDirecoes[i]);
                cin >> medida;
                medida = rangeSensor(medida, 0, 830);
                posicaoAtual = insereVetor(medida, vetorMov, maxVetor, posicaoAtual);
            }

        dirigindo = resposta(); // verifica se quer continuar 
        mapeamento += 1; 
    }

    return posicaoAtual;
}

// Verifica a maior distância
char* maiorDistancia(int* valorIndice, int* distancia) {
	int index = 0;         
	int maiorValor = valorIndice[0]; 

	// Passa por cada índice e verifica qual é o maior valor
	for (int i = 1; i < 4; i++) {
		if (valorIndice[i] > maiorValor) {  
			maiorValor = valorIndice[i];    
			index = i;         
		}
	}

	*distancia = maiorValor; // Maior valor encontrado                               
	return nomeDirecoes[index]; // Mostra onde está o maior valor
}

// Mostra a direção e o meior valor
void percorre(int *v,int tamPercorrido) {		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		char* direcao = maiorDistancia(&vetorMov[i], &maiorDir);  // pega a direção do maior valor
        printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}
int main(int argc, char** argv) {
   int maxVetor = 100;
   int vetorMov[maxVetor*4];
   int posAtualVet = 0;

   posAtualVet = dirige(vetorMov,maxVetor);
   percorre(vetorMov,posAtualVet);

   return 0;
}