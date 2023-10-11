#include "pch.h"
#include "Graph.h"
#include <set>
#include <stack>


// =============================================================================
// SalesmanTrackBacktracking ===================================================
// =============================================================================


CTrack SalesmanTrackBacktracking(CGraph& graph, CVisits& visits)
{
	CTrack CamiMesCurt(NULL);
	double LongitudCamiMesCurt = numeric_limits<double>::max();

	CVertex* pInici = visits.m_Vertices.front();

	for (CVertex& v : graph.m_Vertices)
	{
		v.m_JaHePassat = false;
		v.m_VertexToVisit = false;
	}

	for (CEdge& e : graph.m_Edges)
		e.m_Used = false;

	for(CVertex* v : visits.m_Vertices) v->m_VertexToVisit = true;

	CTrack cami(&graph);
	SalesmanTrackBacktracking(graph, cami, visits, pInici, CamiMesCurt, LongitudCamiMesCurt);
	return CamiMesCurt;
}

void SalesmanTrackBacktracking(CGraph& graph, CTrack& cami, CVisits& visits, CVertex* pActual, CTrack& CamiMesCurt, double& LongitudCamiMesCurt, int visitCount)
{
	if (cami.Length() >= LongitudCamiMesCurt)
		return;

	CVertex* pDesti = visits.m_Vertices.back();

	if (pActual->m_VertexToVisit && !pActual->m_JaHePassat)
		visitCount++;

	if (pActual == pDesti && visitCount == visits.GetNVertices()) {
			CamiMesCurt = cami;
			LongitudCamiMesCurt = cami.Length();
			return;
	}

	bool anticJaHePassat = pActual->m_JaHePassat;
	pActual->m_JaHePassat = true;
	for (CEdge* pE : pActual->m_Edges) {
		if (!pE->m_Used) {
			pE->m_Used = true;
			cami.m_Edges.push_back(pE);
			SalesmanTrackBacktracking(graph, cami, visits, pE->m_pDestination, CamiMesCurt, LongitudCamiMesCurt, visitCount);
			cami.m_Edges.pop_back();
			pE->m_Used = false;
		}
	}
	pActual->m_JaHePassat = anticJaHePassat;
}

// =============================================================================
// SalesmanTrackBacktrackingGreedy =============================================
// =============================================================================
vector<vector<CTrack>> caminsOptims;

CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{
	CTrack CamiMesCurt(NULL);
	double LongitudCamiMesCurt;

	CVertex* pInici = visits.m_Vertices.front();

	CamiMesCurt.Clear();
	LongitudCamiMesCurt = numeric_limits<double>::max();
	for (CVertex& v : graph.m_Vertices)
	{
		v.m_JaHePassat = false;
		v.m_VertexToVisit = false;
	}

	for (CEdge& e : graph.m_Edges)
	{
		e.m_Used = false;
	}

	for (CVertex* v : visits.m_Vertices) v->m_VertexToVisit = true;
	
	// Guardar en un array de dos dimensions tots els camins òptims entre vèrtexs a visitar.
	
	for (CVertex* vvi : visits.m_Vertices)
	{
		DijkstraQueue(graph, vvi);
		vector<CTrack> caminsOptims_vvj;
		for (CVertex* vvj : visits.m_Vertices)
		{
			CTrack cami_vvi_to_vvj(&graph);
			if (vvi != vvj)
			{
				CEdge* aresta = vvj->m_pDijkstraPrevious;
				cami_vvi_to_vvj.AddFirst(aresta);
				while (aresta->m_pOrigin != vvi)
				{
					
					aresta = aresta->m_pOrigin->m_pDijkstraPrevious;
					cami_vvi_to_vvj.AddFirst(aresta);
				}
			}
			caminsOptims_vvj.push_back(cami_vvi_to_vvj);
		}
		caminsOptims.push_back(caminsOptims_vvj);
	}

	CTrack cami(&graph);
	SalesmanTrackBacktrackingGreedy(graph, cami, visits, 0, pInici, CamiMesCurt, LongitudCamiMesCurt);
	return CamiMesCurt;
}

void SalesmanTrackBacktrackingGreedy(CGraph& graph, CTrack& cami, CVisits& visits, int iActual, CVertex* pActual, CTrack& CamiMesCurt, double& LongitudCamiMesCurt, int visitCount)
{
	if (cami.Length() >= LongitudCamiMesCurt)
		return;
	
	CVertex* pDesti = visits.m_Vertices.back();
	
	CTrack cami_original = cami;

	if (pActual->m_VertexToVisit)
		visitCount++;

	if (pActual == pDesti && visitCount == visits.GetNVertices()) {
		CamiMesCurt = cami;
		LongitudCamiMesCurt = cami.Length();
		return;
	}

	bool anticJaHePassat = pActual->m_JaHePassat;
	pActual->m_JaHePassat = true;

	int i = 0;
	for (CTrack tram : caminsOptims[iActual])
	{
		if (i != iActual && !tram.m_Edges.back()->m_pDestination->m_JaHePassat)
		{
			cami.Append(tram);	// push
			SalesmanTrackBacktrackingGreedy(graph, cami, visits, i, tram.m_Edges.back()->m_pDestination, CamiMesCurt, LongitudCamiMesCurt, visitCount);
			cami = cami_original;	// pop
		}
		i++;
	}
	
	pActual->m_JaHePassat = anticJaHePassat;
}