#include "pch.h"
#include "Graph.h"
// SalesmanTrackGreedy =========================================================

CTrack SalesmanTrackGreedy(CGraph& graph, CVisits& visits)
{
	CTrack cami(&graph);

	// Sigui v la primera visita de la llista de visites
	CVertex* vActual = visits.m_Vertices.front();

	// Candidats= tots els v�rtex de la llista de visites menys el primer i l'�ltim.
	std::list<CVertex*> candidats = visits.m_Vertices;
	candidats.pop_front();
	candidats.pop_back();

	CTrack auxTrack(&graph);
	while (!candidats.empty())
	{
		// Aplicant el algorisme de Dijkstra calcular les distancies de tots els v�rtexs del graf a v.
		DijkstraQueue(graph, vActual);

		// Seleccionar vNext com el v�rtex pertanyent a Candidats amb distancia m�nima.
		CVertex* vNext = candidats.front();
		double min_dist = std::numeric_limits<double>::max();
		for (CVertex* it : candidats)
		{
			if (it->m_DijkstraDistance < min_dist)
			{
				min_dist = it->m_DijkstraDistance;
				vNext = it;
			}
		}

		// Afegir el cam� de v a v1 al resultat.
		auxTrack.Clear();

		auxTrack.AddFirst(vNext->m_pDijkstraPrevious);
		while (auxTrack.m_Edges.front()->m_pOrigin != vActual)
		{
			// Si l'ultima aresta que tenim no surt de vActual, anem afegint les anteriors fins a tenir el cami complet de vActual -> vNext
			auxTrack.AddFirst(auxTrack.m_Edges.front()->m_pOrigin->m_pDijkstraPrevious);
		}
		cami.Append(auxTrack);

		// Treure v1 de Candidats
		candidats.remove(vNext);

		vActual = vNext;
	}
	// Anar del �ltim candidat seleccionat al v�rtex final de la llista de visites.
	DijkstraQueue(graph, vActual);	// Aplicant el algorisme de Dijkstra calcular les distancies de tots els v�rtexs del graf a v.
	CVertex* vFinal = visits.m_Vertices.back();

	auxTrack.Clear();
	auxTrack.AddFirst(vFinal->m_pDijkstraPrevious);
	while (auxTrack.m_Edges.front()->m_pOrigin != vActual)
	{
		// Si l'ultima aresta que tenim no surt de vActual, anem afegint les anteriors fins a tenir el cami complet de vActual -> vFinal
		auxTrack.AddFirst(auxTrack.m_Edges.front()->m_pOrigin->m_pDijkstraPrevious);

	}
	cami.Append(auxTrack);



	return cami;
}
