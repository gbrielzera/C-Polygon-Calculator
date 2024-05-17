#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Estrutura para armazenar as coordenadas
struct ponto {
    float x;
    float y;
};

// Função para ler e gravar o número de vértices
int lerVertices(FILE *arquivo) {
    int vertices;
    // Se a leitura do arquivo falhar, imprime uma mensagem de erro e encerra o programa
    if (fscanf(arquivo, "%i", &vertices) != 1) {
        printf("Falha ao ler o número de vertices.\n");
        exit(1);
    }
    return vertices;
}

// Função para ler e guardar as coordenadas em um vetor de estruturas
void lerCoord(FILE *arquivo, struct ponto vertices[], int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        // Se a leitura das coordenadas falhar, imprime uma mensagem de erro e encerra o programa
        if (fscanf(arquivo, "%f %f", &vertices[i].x, &vertices[i].y) != 2) {
            printf("Falha ao ler as coordenadas do vertice %d.\n", i);
            exit(1);
        }
    }
}

// Função para calcular a área do triângulo usando os pontos fornecidos
float AreaTriangulo(struct ponto a, struct ponto b, struct ponto c) {
    float area = (a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0;
    // Se a área calculada for negativa, converte para positiva
    if (area < 0) {
        area = area * -1;
    }
    return area;
}

// Função para calcular a área de polígonos com mais de 3 vértices
float calcularAreaPoligono(struct ponto vertices[], int numVertices) {
    float areaTotal = 0;
    // Calcula a área somando as áreas dos triângulos formados pelos vértices
    for (int i = 1; i < numVertices - 1; i++) {
        areaTotal += AreaTriangulo(vertices[0], vertices[i], vertices[i+1]);
    }
    return areaTotal;
}

int main() {

    // Abre o arquivo para leitura
    FILE *arquivo = fopen("numeros.txt", "r");
    // Se a abertura do arquivo falhar, imprime uma mensagem de erro e encerra o programa
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Lê o número de vértices do arquivo
    int numVertices = lerVertices(arquivo);
    struct ponto vertices[numVertices];
    // Lê as coordenadas dos vértices do arquivo
    lerCoord(arquivo, vertices, numVertices);
    fclose(arquivo);

    // Se o número de vértices for menor que 3, imprime uma mensagem de erro e encerra o programa
    if (numVertices < 3) {
        printf("Vertices insuficientes para formar um poligono.\n");
        exit(1);
    }

    // Calcula a área do polígono
    float area = calcularAreaPoligono(vertices, numVertices);
    // Imprime a área do polígono
    printf("A area do poligono e aproximadamente: %.2f.\n", area);

    return 0;
}