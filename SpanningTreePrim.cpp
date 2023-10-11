#include "pch.h"
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

// =============================================================================
// SpanningTreePrim ============================================================
// =============================================================================


CSpanningTree SpanningTreePrim(CGraph& graph)
{
	struct comparator {
		bool operator()(CEdge* pE1, CEdge* pE2) {
			return pE1->m_Length > pE2->m_Length;
		}
	};
	priority_queue<CEdge*, std::vector<CEdge*>, comparator> queue;


	// Reiniciar etiqueta dels vertex que utilitzarem per a saber si ja esta a l'arbre
	for (CVertex v : graph.m_Vertices) v.m_PrimInTree = false;

	// Initialize a tree with a single vertex, chosen arbitrarily from the graph.
	CSpanningTree tree(&graph);
	graph.GetVertex(0)->m_PrimInTree = true;
	for (CEdge* e : graph.GetVertex(0)->m_Edges) queue.push(e);

	while (!queue.empty()) {
		CEdge* pE = queue.top();
		queue.pop();
		if (!pE->m_pDestination->m_PrimInTree) {
			tree.m_Edges.push_back(pE);
			pE->m_pDestination->m_PrimInTree = true;
			for (CEdge* e : pE->m_pDestination->m_Edges) queue.push(e);
		}
		
	}
	return tree;
}
