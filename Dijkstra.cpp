#include "pch.h"
#include "Graph.h"
#include <queue>

// =============================================================================
// Dijkstra ====================================================================
// =============================================================================

void Dijkstra(CGraph& graph, CVertex *pStart)
{	 
	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); it++)
	{
		// Inicialitzar les distancies dels vèrtex a infinit
		it->m_DijkstraDistance = std::numeric_limits<double>::max();

		// Marcar tots el vèrtex com no visitats
		it->m_DijkstraVisit = false;
	}

	pStart->m_DijkstraDistance = 0;
	CVertex* pActual = pStart;

	while (pActual != NULL)
	{
		// Recorre tots el veïns v de pActual
		for (CEdge* e : pActual->m_Edges)
		{
			// Si la distancia de v es més gran que la distancia del vèrtex actual més la longitud de
			// l’aresta que els uneix, actualitzar la distancia de v
			if ((e->m_pOrigin == pActual) && (pActual->m_DijkstraDistance + e->m_Length) < e->m_pDestination->m_DijkstraDistance)
			{
				e->m_pDestination->m_DijkstraDistance = pActual->m_DijkstraDistance + e->m_Length;
				e->m_pDestination->m_pDijkstraPrevious = e;

			}	
		}

		// Marcar pActual com visitat
		pActual->m_DijkstraVisit = true;

		// pActual = vèrtex no visitat amb distancia més petita i tornar a repetir el bucle
		double min_dist = INT_MAX;
		pActual = NULL;
		for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); it++) {
			if (!it->m_DijkstraVisit && it->m_DijkstraDistance >= 0 && it->m_DijkstraDistance < min_dist)
			{
				min_dist = it->m_DijkstraDistance;
				pActual = &(*it);
			}
		}
	}

}

// =============================================================================
// DijkstraQueue ===============================================================
// =============================================================================

void DijkstraQueue(CGraph& graph, CVertex *pStart)
{
	struct comparator {
		bool operator()(std::pair<CVertex*, double> a, std::pair<CVertex*, double> b) {
			return a.second > b.second;
		}
	};

	std::priority_queue<std::pair<CVertex*, double>, std::vector<std::pair<CVertex*, double>>, comparator> queue;

	for (std::list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); it++)
	{
		// Inicialitzar les distancies dels vèrtex a infinit
		it->m_DijkstraDistance = std::numeric_limits<double>::max();

		// Marcar tots el vèrtex com no visitats
		it->m_DijkstraVisit = false;
	}

	pStart->m_DijkstraDistance = 0;
	queue.push(std::pair<CVertex*, double>(pStart, 0));
	
	CVertex* pActual = NULL;
	while (!queue.empty())
	{
		pActual = queue.top().first;
		queue.pop();

		if (!pActual->m_DijkstraVisit)
		{
			// Recorre tots el veïns v de pActual
			for (CEdge* e : pActual->m_Edges)
			{
				// Si la distancia de v es més gran que la distancia del vèrtex actual més la longitud de
				// l’aresta que els uneix, actualitzar la distancia de v i possar-lo a la cua
				if ((e->m_pOrigin == pActual) && ((pActual->m_DijkstraDistance + e->m_Length) < e->m_pDestination->m_DijkstraDistance))
				{
					e->m_pDestination->m_DijkstraDistance = pActual->m_DijkstraDistance + e->m_Length;
					e->m_pDestination->m_pDijkstraPrevious = e;

					queue.push(std::pair<CVertex*, double>(e->m_pDestination, e->m_pDestination->m_DijkstraDistance));
				}
			}

			// Marcar pActual com visitat
			pActual->m_DijkstraVisit = true;
		}
	}
}
