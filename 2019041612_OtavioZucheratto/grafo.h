#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>

typedef std::pair<std::pair<int, int>, std::pair<int, int>> TipoAresta;

// Funcao de comparacao para criar uma fila de prioridade personalizada
struct CustomComp 
{
    bool operator()(const TipoAresta &aresta_a, const TipoAresta &aresta_b) const 
    {
        // Primeiro criterio eh o custo dos trechos analisados 
        if (aresta_a.second.first < aresta_b.second.first) 
            return false;
        else if (aresta_a.second.first > aresta_b.second.first)
            return true;

        // Para trechos com o mesmo custo eh avaliado qual possui a maior atratividade
        else if (aresta_a.second.second > aresta_b.second.second)
            return false;
        else
            return true;
    }
};

typedef std::priority_queue<TipoAresta, std::vector<TipoAresta>, CustomComp> CustomFila;

/*Assinatura dos atributos e metodos da classe Grafo*/
class Grafo
{
    public:
        Grafo(int q_pontos, int q_trechos, std::vector<int> atrat_p);
        void InsereTrecho(int u, int v, std::pair<int, int> custo_atrat);
        void ConstroiCiclovia();
        void ImprimeSaida();
        void ImprimeGrafo();
        void ImprimeFila(CustomFila q);
        
    private:
        int quant_pontos, quant_trechos, custo_total;
        std::vector<int> atrat_pontos;
        std::vector<std::list<TipoAresta>> rotas;
        std::map<int, std::pair<int, int>> dict;
        std::vector<std::pair<int, int>> pais_custo;
        std::vector<bool> explorados;
        std::vector<int> incidentes;
};

#endif /* GRAFO_H */