#include "pch.h"
#include "Graph.h"
#include <queue>
#include <iostream>
#include <iomanip> 

#include <random>
#include <chrono>

// SalesmanTrackProbabilistic ==================================================
unsigned seed;
CTrack SalesmanTrackProbabilistic(CGraph& graph, CVisits& visits)
{
	seed = 745451611; // habra que fijarla para optimizar nota

	// Calcul preliminar: precalcular tots els camins entre visites
	vector<vector<CTrack>> taulaCamins;

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
		taulaCamins.push_back(caminsOptims_vvj);
	}

	// Es fan un ser n�mero d�intents i ens quedem amb l�ordre de visites que te el cam� m�s curt. El n�mero d�intents pot dependre del n�mero de visites.
	double millorCost = std::numeric_limits<double>::max();
	vector<int> millorOrdre;

	int n_intents = visits.GetNVertices() * 10'000;
	cout << "n intents: " << n_intents << endl;

	// Crear un ordre de visites aleatori.
	vector<int> ordre;

	// Emplenar el vector amb nombres consecutius
	for (int i = 0; i < visits.GetNVertices(); i++)
		ordre.push_back(i);

	for (int intent = 0; intent < n_intents; intent++)
	{
		// Ordenar aleatoriament
		seed = seed++;
		std::shuffle(ordre.begin() + 1, ordre.end() - 1, std::default_random_engine(seed));
		//cout << "ordre:" << ordre[1] << ordre[2] << ordre[3] << endl;

		// Calcular cost
		float cost = 0;
		for (vector<int>::iterator it = ordre.begin(); std::next(it) != ordre.end(); it++)
		{
			int i = *it;
			int j = *std::next(it);

			cost += taulaCamins[i][j].Length();
		}

		if (cost < millorCost)
		{
			millorCost = cost;
			millorOrdre = ordre;
		}

		// Gradient Descent
		int n = ordre.size();
		vector<int> ordre_bk = ordre;
		// Generem una s�rie de intercanvis de visites. Per cada intercanvi generem un nou ordre i
		// ens quedem amb el que correspon al cam� m�s curt
		for (int i = 1; i < n - 2; ++i) for (int j = i + 1; j < n - 1; ++j)
		{
			ordre = ordre_bk;
			// generar nova configuraci� intercanviant les visites de les posicions i < ->j.
			swap(ordre[i], ordre[j]);

			// Calcular cost
			float cost = 0;
			for (vector<int>::iterator it = ordre.begin(); std::next(it) != ordre.end(); it++)
			{
				int i = *it;
				int j = *std::next(it);

				cost += taulaCamins[i][j].Length();
			}

			if (cost < millorCost)
			{

				millorCost = cost;
				millorOrdre = ordre;
			}
			else
			{
				//Si en el pas anterior hem aconseguit un cam� m�s curt, repetim el pas anterior.
				// Si no hem aconseguir un cam� m�s curt parem el descens del gradient i ens quedem amb el millor ordre.


				break;


			}
		}

	}

	// Formar CTrack del millor cam� obtingut
	CTrack cami(&graph);
	for (vector<int>::iterator it = millorOrdre.begin(); std::next(it) != millorOrdre.end(); it++)
	{
		int i = *it;
		int j = *std::next(it);

		cami.Append(taulaCamins[i][j]);
	}

	
	return cami;
}
