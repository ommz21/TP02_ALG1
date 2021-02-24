#include "headers/grafo.h"

int main()
{
    // Declaracao das variaveis para lidar com a entrada do programa
    int quant_pontos, quant_trechos;
    std::vector<int> atrat_pontos;
    int atrat;

    // Leitura da quantidade de pontos de interesse e trechos possiveis
    std::cin >> quant_pontos >> quant_trechos;
    
    // Leitura dos valores turisticos de cada ponto de interesse
    for (int i = 0; i < quant_pontos; i++)
    {
        std::cin >> atrat;
        atrat_pontos.push_back(atrat);
    }

    // Cria o grafo para representar a cidade
    Grafo cidade(quant_pontos, quant_trechos, atrat_pontos);
    
    for (int i = 0; i < quant_trechos; i++)
    {
        int vertice_u, vertice_v, custo_aresta, soma_atrat;
        std::pair<int, int> aresta;
        
        // Leitura de um possivel trecho com seu respectivo custo
        std:: cin >> vertice_u >> vertice_v >> custo_aresta;
        
        // Calcula a atratividade do trecho somando as atratividades
        // dos dois pontos de interesses
        soma_atrat = atrat_pontos[vertice_u] + atrat_pontos[vertice_v];
        
        // Insere a aresta no grafo
        aresta.first = custo_aresta;
        aresta.second = soma_atrat;
        cidade.InsereTrecho(vertice_u, vertice_v, aresta);
    }
    // Determina a ciclovia a ser construida
    cidade.ConstroiCiclovia();

    cidade.ImprimeSaida();
    return 0;
}