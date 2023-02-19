//======== Copyright (c) 2023, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Oleksandr Turtytsia <xturyt00@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"

Graph::Graph() {}

Graph::~Graph() {}

std::vector<Node *> Graph::nodes()
{

    return this->graph_nodes;
}

std::vector<Edge> Graph::edges() const
{

    return this->graph_edges;
}

Node *Graph::addNode(size_t nodeId)
{
    for (auto node : this->graph_nodes)
    {
        if (node->id == nodeId)
            return nullptr;
    }

    Node *node = new Node();
    if (node == nullptr)
    {
        std::cerr << "Allocation Error" << std::endl;
        return nullptr;
    }

    node->id = nodeId;
    this->graph_nodes.push_back(node);

    return node;
}

bool Graph::addEdge(const Edge &edge)
{
    for (auto graph_edge : this->graph_edges)
    {
        if (graph_edge == edge)
            return false;
    }

    if (this->getNode(edge.a) == nullptr)
    {
        this->addNode(edge.a);
    }

    if (this->getNode(edge.b) == nullptr)
    {
        this->addNode(edge.b);
    }

    if (edge.a == edge.b)
        return false;

    this->graph_edges.push_back(edge);

    return true;
}

void Graph::addMultipleEdges(const std::vector<Edge> &edges)
{
    for (auto edge : edges)
    {
        this->addEdge(edge);
    }
}

Node *Graph::getNode(size_t nodeId)
{
    for (auto node : this->graph_nodes)
    {
        if (node->id == nodeId)
            return node;
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge &edge) const
{
    for (auto iter : this->graph_edges)
    {
        if (edge == iter)
            return true;
    }
    return false;
}

void Graph::removeNode(size_t nodeId)
{
    Node *node_ptr;
    if ((node_ptr = this->getNode(nodeId)) == nullptr)
        throw std::out_of_range("uzel s daným id v grafu neexistuje");

    std::vector<Edge> edges;
    for (auto edge : this->graph_edges)
    {
        if (edge.a != nodeId && edge.b != nodeId)
            edges.push_back(edge);
    }
    this->graph_edges = edges;

    std::vector<Node *> nodes;
    for (auto node : this->graph_nodes)
    {
        if (node->id != nodeId)
            nodes.push_back(node);
    }

    this->graph_nodes = nodes;
    free(node_ptr);
}

void Graph::removeEdge(const Edge &edge)
{
    if (!this->containsEdge(edge))
        throw std::out_of_range("hrana v grafu neexistuje");

    std::vector<Edge> edges;
    for (auto graph_edge : this->graph_edges)
    {
        if (graph_edge != edge)
            edges.push_back(graph_edge);
    }

    this->graph_edges = edges;
}

size_t Graph::nodeCount() const
{
    return this->graph_nodes.size();
}

size_t Graph::edgeCount() const
{
    return this->graph_edges.size();
}

size_t Graph::nodeDegree(size_t nodeId) const
{
    for (auto node : this->graph_nodes)
    {
        if (node->id == nodeId)
        {
            int degree = 0;
            for (auto edge : this->graph_edges)
            {
                degree += edge.a == nodeId || edge.b == nodeId;
            }
            return degree;
        }
    }

    throw std::out_of_range("uzel s daným id v grafu neexistuje");
}

size_t Graph::graphDegree() const
{
    size_t max_degree = 0;
    for (auto node : this->graph_nodes)
    {
        max_degree = std::max(max_degree, this->nodeDegree(node->id));
    }
    return max_degree;
}

void Graph::coloring()
{

    for (auto node : this->graph_nodes)
    {
        size_t color = 1;
        if (node->color)
            continue;
        node->color = color++;
        for (auto edge : this->graph_edges)
        {
            bool begin = edge.a == node->id;
            bool end = edge.b == node->id;

            Node *n = begin ? this->getNode(edge.b) : end ? this->getNode(edge.a)
                                                          : nullptr;

            if(n==nullptr) continue;

            n->color = color++;
        }
    }
}

void Graph::clear()
{
    for (auto node : this->graph_nodes)
        delete node;
    this->graph_nodes.clear();
    this->graph_edges.clear();
}

/*** Konec souboru tdd_code.cpp ***/
