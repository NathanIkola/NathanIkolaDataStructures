//**************************************
// node.h
// 
// Declaration for my node class for
// my graph data structure
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************
#pragma once

#include <assert.h>
#include <vector>

namespace nids
{
	// simple ID data type for convenience
	using node_id = unsigned long;

	template<typename GraphDataType>
	class Node final
	{
	public:
		// all defaults should be fine for this class
		inline Node(node_id id, GraphDataType data) noexcept : m_id(id), m_data(data), m_neighbors() {}
		Node(const Node&) = default;
		Node& operator=(const Node&) = default;
		~Node() = default;

		//**********************************
		// Comparison operator
		// 
		// Uses simple pointer comparison
		//**********************************
		inline bool operator==(const Node& node) { return &node == this; }

		//**********************************
		// Data accessor method
		//**********************************
		inline GraphDataType GetData() noexcept { return m_data; }

		//**********************************
		// Data mutator method
		//**********************************
		inline void SetData(GraphDataType& data) noexcept { m_data = data; }

		//**********************************
		// Iterator accessor method
		// Returns:		First neighbor
		//**********************************
		inline typename std::vector<Node*>::iterator GetNeighborIterator() noexcept { return m_neighbors.begin(); }

		//**********************************
		// Iterator end method
		//**********************************
		inline typename std::vector<Node*>::iterator GetNeigborEnd() noexcept { return m_neighbors.end(); }

		//**********************************
		// Neighbor adding method
		//**********************************
		void AddNeighbor(Node<GraphDataType>* node) noexcept;

		//**********************************
		// Neighbor removing method
		//**********************************
		void RemoveNeighbor(Node<GraphDataType>* node) noexcept;

		//**********************************
		// ID accessor method
		//**********************************
		inline node_id ID() const noexcept { return m_id; }
	private:
		// this is the id of this node
		node_id m_id;

		// this will be the payload of the node
		GraphDataType m_data;

		// list of the neighbors adjacent to this node
		std::vector<Node*> m_neighbors;
	};

	// use this for shorthand to refer to the iterator we get
	template<typename GraphDataType>
	using node_iter = typename std::vector<class Node<GraphDataType>*>::iterator;

	//**************************************
	// Neighbor adding method
	template<typename GraphDataType>
	void Node<GraphDataType>::AddNeighbor(Node<GraphDataType>* node) noexcept
	{
		// ensure we have good arguments
		assert(node != nullptr);
		assert(node != this);

		// look for this node in our list
		for (Node<GraphDataType>* n : m_neighbors)
			assert(n != node);

		// otherwise add it to our list
		m_neighbors.push_back(node);
	}

	//**************************************
	// Neighbor removing method
	template<typename GraphDataType>
	void Node<GraphDataType>::RemoveNeighbor(Node<GraphDataType>* node) noexcept
	{
		// ensure we have good arguments
		assert(node != nullptr);

		// look for this node in our list
		for (auto iter = m_neighbors.begin(); iter != m_neighbors.end(); ++iter)
			if (*iter == node)
			{
				m_neighbors.erase(iter);
				return;
			}

		// if we get here we attempted to delete a node
		// which was not in our list
		assert(false);
	}
}