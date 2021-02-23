#include "grafo.h"

#define INFINITO 10000000

// Construtor da classe Grafo
Grafo::Grafo(int q_pontos, int q_trechos, std::vector<int> atrat_p)
{
    std::pair<int, int> par;
    quant_pontos = q_pontos;
    quant_trechos = q_trechos;
    custo_total = 0;
    atrat_pontos = atrat_p;
    rotas.resize(quant_pontos);
    
    // Valores iniciais que serao substituidos
    par.first = INFINITO;
    par.second = 0;
    
    // Loop para setar valores para que seja possivel acessar as
    // estruturas atraves do metodo at()
    for (int i = 0; i < quant_pontos; i++)
    {
        dict[i] = par; 
        pais_custo.push_back(par);
        explorados.push_back(false);
        incidentes.push_back(1);
    }
}
void Grafo::InsereTrecho(int u, int v, std::pair<int, int> custo_atrat)
{
    TipoAresta aresta;
    aresta.second.first = custo_atrat.first;
    aresta.second.second = custo_atrat.second;

    // Insere a aresta na lista de adjascencia do vertice u
    aresta.first.first = u;
    aresta.first.second = v;
    rotas.at(u).push_back(aresta);
    
    // Insere a aresta na lista de adjascencia do vertice v
    aresta.first.first = v;
    aresta.first.second = u;
    rotas.at(v).push_back(aresta);
}
void Grafo::ConstroiCiclovia()
{
    int pai, custo;
    int vertice_u = 0;
    CustomFila fila;
    TipoAresta aresta;

    // A raiz nao possui pai e portanto esses valores iniciais podem ser desconsiderados
    aresta.first.first = -2;
    aresta.first.second = vertice_u;
    aresta.second.first = 0;
    aresta.second.second = 0;
    pais_custo.at(vertice_u).first = 0;
    fila.push(aresta);
    
    // Pecorre o grafo ate todos os possiveis trechos tenham sido verificados
    while (!fila.empty())
    {
        vertice_u = fila.top().first.second;
        pai = fila.top().first.first;
        custo = fila.top().second.first;
        fila.pop();
        
        // Caso o vertice ja tenha sido retirado da fila indica que a melhor
        // aresta ja foi encontrada e portanto a atual n deve ser considerada
        if (explorados.at(vertice_u))
            continue;
        pais_custo.at(vertice_u).first = pai;
        pais_custo.at(vertice_u).second = custo;
        explorados.at(vertice_u) = true;
        
        // Acumula o custo das arestas escolhidas
        custo_total += pais_custo.at(vertice_u).second;

        // Percorre pela lista de adjascencia do vertice atual
        for (TipoAresta aresta : rotas.at(vertice_u))
        {
            // Caso o proximo vertice ja esteja na fila com uma aresta de custo menor
            // entao nao eh necessario incluir a aresta atual
            if (aresta.second.first > dict[aresta.first.second].first)
                continue;
            // Caso o custo das arestas eh o mesmo porem a atratividade da atual nao eh
            // maior do que a que se encontra na fila, entao a aresta atual pode ser ignorada
            else if (aresta.second.first == dict[aresta.first.second].first && aresta.second.second <= dict[aresta.first.second].second)
                continue;
            
            // Atualiza os valores no dicionario pois uma aresta melhor foi encontrada
            dict[aresta.first.second].first = aresta.second.first;
            dict[aresta.first.second].second = aresta.second.second;

            // A aresta adicionada pela propriedade da fila de prioridade sera retirada
            // antes de uma outra aresta que incide em um mesmo vertice
            fila.push(aresta);
        }
    }
}
void Grafo::ImprimeSaida()
{
    int atrat_acum = 0;

    // O no raiz nao possui pai
    incidentes.at(0)--;
    
    // Laco para calcular a atratividade acumulada do caminho encontrado
    // e calcular a quantidade de arestas incidentes em todos os vertices do grafo
    for (int i = 1; i < quant_pontos; i++)
    {
        atrat_acum += atrat_pontos.at(pais_custo.at(i).first) + atrat_pontos.at(i);
        incidentes.at(pais_custo.at(i).first)++;
    }

    // Imprime custo total e atratividade acumulada da ciclovia
    std::cout << custo_total << " " << atrat_acum << std::endl;

    // Imprime a quantidade de arestas incidentes em cada vertice
    for (int i = 0; i < quant_pontos; i++)
        std::cout << incidentes.at(i) << " ";
    std::cout << std::endl;

    // Imprime cada par de vertices e o custo correspondente a todas as arestas
    // que compoe a ciclovia encontrada
    for (int i = 1; i < quant_pontos; i++)
        std::cout << i << " " << pais_custo.at(i).first << " " << pais_custo.at(i).second << std::endl;
}

// Metodos auxiliares criados durante os testes relizados ao longo da implementacao
void Grafo::ImprimeGrafo()
{
    for (int i = 0; i < quant_pontos; i++)
    {
        std::list<TipoAresta> lista = rotas.at(i);
        std::cout << "Arestas do vertice " << i << ": ";
        for(auto aresta : lista)
            std::cout << "(" << aresta.first.first << "," << aresta.first.second << ")/" << aresta.second.first << "/" << aresta.second.second << " ";
        std::cout << std::endl;
    }
}
void Grafo::ImprimeFila(CustomFila q) 
{ 
    CustomFila f = q; 
    std::cout << "Fila:"; 
    while (!f.empty())
    { 
        std::cout << " (" << f.top().first.first << "," << f.top().first.second << ")/" << f.top().second.first << "/" << f.top().second.second; 
        f.pop(); 
    } 
    std::cout << std::endl; 
} 