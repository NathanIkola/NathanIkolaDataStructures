//**************************************
// graph.h
//
// Declaration for my graph data
// structure
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************
#pragma once

#include <vector>
#include "node.h"

namespace nids
{
	// enum class for deciding what kind of neighbor relationship to add
	enum class NeighborType
	{
		NEIGHBOR_DIRECTED,
		NEIGHBOR_UNDIRECTED
	};

	template<typename GraphDataType>
	class Graph final
	{
	public:
		inline Graph() noexcept : m_currentId(0), m_nodes(), m_freeList() {};
		Graph(const Graph&) = delete;
		Graph& operator=(const Graph&) = delete;
		inline ~Graph() noexcept
		{
			// clean up the memory from the nodes vector
			while (m_nodes.size() > 0)
			{
				delete m_nodes[0];
				m_nodes.erase(m_nodes.begin());
			}
		}

		//**********************************
		// Size accessor method
		//
		// Returns:	number of nodes in the graph
		//**********************************
		inline size_t Size() const noexcept { return m_nodes.size(); }

		//**********************************
		// Node creation method
		//
		// Returns:	ID of the new node
		//**********************************
		node_id AddNode(GraphDataType data) noexcept;

		//**********************************
		// Node deletion method
		//**********************************
		inline void DeleteNode(node_id id) noexcept
		{
			assert(id < m_nodes.size());
			assert(m_nodes[id] != nullptr);
			delete m_nodes[id];
			m_nodes[id] = nullptr;
			m_freeList.push_back(id);
		}

		//*************************************
		// Node accessor by data method
		//
		// Returns:	vector of matching node ID's
		//*************************************
		std::vector<unsigned long> GetNodes(GraphDataType data) noexcept;

		//*************************************
		// Node accessor by ID
		//
		// Returns:	Node that matches ID
		//*************************************
		Node<GraphDataType>* GetNode(node_id id) noexcept;

		//*************************************
		// Node neighbor adding method
		//
		// Adds neighbor to subject
		// 
		// Arguments:
		//	subject, neighbor: node ID's
		//	relationship: NeighborType value for
		//				  directed / undirected
		//*************************************
		void AddNeighbor(node_id subject, node_id neighbor, NeighborType relationship = NeighborType::NEIGHBOR_UNDIRECTED) noexcept;

		//*************************************
		// Node neighbor remover
		//
		// Removes neighbor from subject
		//
		// Arguments
		//	subject, neighbor: node ID's
		//	relationship: NeighborType value for
		//				  directed / undirected
		//*************************************
		void RemoveNeighbor(node_id subject, node_id neighbor, NeighborType relationship = NeighborType::NEIGHBOR_UNDIRECTED) noexcept;
	private:
		// value for keeping track of node ID's as they are generated
		node_id m_currentId;

		// list of the nodes in this graph
		std::vector<Node<GraphDataType>*> m_nodes;

		// list of open indexes from the delete function
		std::vector<node_id> m_freeList;
	};

	//**********************************
	// Node creation method
	template<typename GraphDataType>
	node_id Graph<GraphDataType>::AddNode(GraphDataType data) noexcept
	{
		// if we have no spare ID's free, use the last one
		if (m_freeList.size() == 0)
		{
			m_nodes.push_back(new Node<GraphDataType>(m_nodes.size(), data));
			return m_nodes.size() - 1;
		}

		node_id id = m_freeList[0];
		m_freeList.erase(m_freeList.begin());
		m_nodes[id] = new Node<GraphDataType>(id, data);
		return id;
	}

	//**************************************
	// Node accessor by data method
	template<typename GraphDataType>
	std::vector<node_id> Graph<GraphDataType>::GetNodes(GraphDataType data) noexcept
	{
		std::vector<node_id> matchingNodes;

		// look for any applicable nodes and add them to the list
		for (Node<GraphDataType>* node : m_nodes)
			if (node->GetData() == data) matchingNodes.push_back(node->ID());

		return matchingNodes;
	}

	//**************************************
	// Node accessor by ID
	template<typename GraphDataType>
	Node<GraphDataType>* Graph<GraphDataType>::GetNode(node_id id) noexcept
	{
		// check that the argument is good
		assert(id < m_nodes.size());
		assert(m_nodes[id] != nullptr);

		return m_nodes[id];
	}

	//**************************************
	// Node neighbor adding method
	template<typename GraphDataType>
	void Graph<GraphDataType>::AddNeighbor(node_id subject, node_id neighbor, NeighborType relationship) noexcept
	{
		// ensure we have good arguments
		assert(subject != neighbor);

		Node<GraphDataType>* subjectNode = GetNode(subject);
		Node<GraphDataType>* neighborNode = GetNode(neighbor);

		// if we are adding in an undirected mode also add subject to neighbor
		if (relationship == NeighborType::NEIGHBOR_UNDIRECTED)
			neighborNode->AddNeighbor(subjectNode);
		subjectNode->AddNeighbor(neighborNode);
	}

	//*************************************
	// Node neighbor remover
	template<typename GraphDataType>
	void Graph<GraphDataType>::RemoveNeighbor(node_id subject, node_id neighbor, NeighborType relationship) noexcept
	{
		// ensure we have good arguments
		assert(subject != neighbor);

		Node<GraphDataType>* subjectNode = GetNode(subject);
		Node<GraphDataType>* neighborNode = GetNode(neighbor);

		// if we are removing in an undirected mode also remove from neighbor
		if (relationship == NeighborType::NEIGHBOR_UNDIRECTED)
			neighborNode->RemoveNeighbor(subjectNode);
		subjectNode->RemoveNeighbor(neighborNode);
	}
}