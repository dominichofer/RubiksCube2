#pragma once
#include <cstdint>
#include <functional>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Returns a map from nodes to the edges that lead to them,
// with the restriction that the shortest path to the node has a length between min_length and max_length.
// Arguments:
// - min_length: the minimum length of the shortest path
// - max_length: the maximum length of the shortest path
// - origin: the node from which to start the search
// - edges: the edges of the graph
// - traverse: a function that takes a node and an edge and returns the node reached by traversing the edge
template <typename Node, typename Edge, typename Traverse>
std::unordered_map<Node, std::vector<Edge>> path_to_neighbours(
	int min_length,
	int max_length,
	const Node& origin,
	const std::vector<Edge>& edges,
	const Traverse& traverse)
{
	std::unordered_map<Node, std::vector<Edge>> all = { { origin, {} } };
	std::unordered_map<Node, std::vector<Edge>> latent;
	std::vector<Node> current = { origin };
	for (int order = 1; order <= max_length; ++order)
	{
		latent.clear();
		#pragma omp parallel
		{
			std::unordered_map<Node, std::vector<Edge>> latent_local;
			#pragma omp for nowait
			for (int64_t i = 0; i < static_cast<int64_t>(current.size()); ++i)
				for (const Edge& edge : edges)
				{
					Node n = traverse(current[i], edge);
					if (all.contains(n))
						continue;
					auto inserted = latent_local.insert({ n, all[current[i]] });
					if (inserted.second)
						inserted.first->second.push_back(edge);
				}
			#pragma omp critical
			latent.merge(latent_local);
		}
		if (order != max_length)
		{
			current.clear();
			current.reserve(latent.size());
			for (const auto& [node, _] : latent)
				current.push_back(node);
		}
		all.merge(latent);
	}
	for (auto it = all.begin(); it != all.end();)
	{
		if (it->second.size() < min_length)
			it = all.erase(it);
		else
			++it;
	}
	return all;
}

// Returns a set of nodes that are neighbours of the origin node,
// with the restriction that the shortest path to the node has a length between min_length and max_length.
// Arguments:
// - min_length: the minimum length of the shortest path
// - max_length: the maximum length of the shortest path
// - origin: the node from which to start the search
// - edges: the edges of the graph
// - traverse: a function that takes a node and an edge and returns the node reached by traversing the edge
template <typename Node, typename Edge, typename Traverse>
std::unordered_set<Node> neighbours(
	int min_length,
	int max_length,
	const Node& origin,
	const std::vector<Edge>& edges,
	const Traverse& traverse)
{
	std::unordered_set<Node> set, short_set, latent;
	std::vector<Node> current = { origin };
	if (min_length == 0)
		set.insert(origin);
	else
		short_set.insert(origin);
	for (int order = 1; order <= max_length; ++order)
	{
		latent.clear();
		#pragma omp parallel
		{
			std::unordered_set<Node> latent_local;
			#pragma omp for nowait
			for (int64_t i = 0; i < static_cast<int64_t>(current.size()); ++i)
				for (const Edge& edge : edges)
				{
					Node n = traverse(current[i], edge);
					if (set.contains(n) || short_set.contains(n))
						continue;
					latent_local.insert(n);
				}
			#pragma omp critical
			latent.merge(latent_local);
		}
		if (order != max_length)
		{
			current.clear();
			current.reserve(latent.size());
			for (const Node& node : latent)
				current.push_back(node);
		}
		if (order < min_length)
			short_set.merge(latent);
		else
			set.merge(latent);
	}
	return set;
}

//template <typename Node, typename Edge>
//class RandomGenerator
//{
//	std::mt19937_64 rng;
//	Node origin;
//	std::vector<Edge> edges;
//	std::function<Node(const Node&, const Edge&)> traverse;
//	std::uniform_int_distribution<std::size_t> dist;
//public:
//	RandomGenerator(
//		Node origin,
//		std::vector<Edge> edges,
//		std::function<Node(const Node&, const Edge&)> traverse,
//		unsigned int seed = std::random_device{}())
//		: rng(seed)
//		, origin(std::move(origin))
//		, edges(std::move(edges))
//		, traverse(std::move(traverse))
//	{
//		dist = std::uniform_int_distribution<std::size_t>(0, this->edges.size() - 1);
//	}
//
//	Edge edge()
//	{
//		return edges[dist(rng)];
//	}
//
//	Node node(int path_length)
//	{
//		Node node = origin;
//		for (int i = 0; i < path_length; i++)
//			node = traverse(node, edge());
//		return node;
//	}
//};

//template <typename Node, typename Edge>
//class DistanceTable
//{
//	std::vector<uint8_t> table;
//	std::function<uint64_t(Node)> index;
//	std::vector<Edge> edges;
//	std::function<Node(Node, Edge)> traverse;
//	int max_distance_;
//public:
//	DistanceTable(
//		const Node& origin,
//		std::vector<Edge> edges,
//		std::function<Node(Node, Edge)> traverse,
//		std::function<uint64_t(Node)> index_fkt,
//		std::size_t index_space)
//		: table(index_space, 0xFF)
//		, index(std::move(index_fkt))
//		, edges(std::move(edges))
//		, traverse(std::move(traverse))
//	{
//		table[index(origin)] = 0;
//		std::unordered_set<Node> latent;
//		std::vector<Node> current = { origin };
//		uint8_t distance = 1;
//		while (!current.empty())
//		{
//			latent.clear();
//			#pragma omp parallel
//			{
//				std::unordered_set<Node> latent_local;
//				#pragma omp for nowait
//				for (int i = 0; i < current.size(); ++i)
//					for (const Edge& edge : edges)
//					{
//						Node n = traverse(current[i], edge);
//						std::size_t i = index(n);
//						if (table[i] == 0xFF)
//						{
//							table[i] = distance;
//							latent_local.insert(n);
//						}
//					}
//				#pragma omp critical
//				latent.merge(latent_local);
//			}
//			current.clear();
//			current.reserve(latent.size());
//			for (const Node& node : latent)
//				current.push_back(node);
//			++distance;
//		}
//		max_distance_ = distance - 1;
//	}
//
//	auto begin() const { return table.begin(); }
//	auto end() const { return table.end(); }
//	int max_distance() const { return max_distance_; }
//	int operator[](const Node& node) const { return table[index(node)]; }
//
//	std::vector<Edge> solution(Node node) const
//	{
//		std::vector<Edge> path;
//		uint8_t distance = table[index(node)];
//		while (distance > 0)
//			for (const Edge& edge : edges)
//			{
//				Node n = traverse(node, edge);
//				uint8_t d = table[index(n)];
//				if (d == distance - 1)
//				{
//					path.push_back(edge);
//					node = n;
//					distance = d;
//					break;
//				}
//			}
//		return path;
//	}
//};

template <typename Node, typename Edge>
class DistanceTableSlim
{
	std::vector<uint8_t> table;
	std::function<uint64_t(Node)> index;
	std::vector<Edge> edges;
	std::function<Node(Node, Edge)> traverse;
	int max_distance_;

	void update_table(const Node& node, int depth, int max_depth, bool& changed)
	{
		uint8_t& d = table[index(node)];
		if (d <= depth)
			return;
		d = depth;
		changed = true;
		if (depth < max_depth)
			for (const Edge& edge : edges)
				update_table(traverse(node, edge), depth + 1, max_depth, changed);
	}
public:
	DistanceTableSlim(
		const Node& origin,
		std::vector<Edge> edges,
		std::function<Node(Node, Edge)> traverse,
		std::function<uint64_t(Node)> index_fkt,
		std::size_t index_space)
		: table(index_space, 0xFF)
		, index(std::move(index_fkt))
		, edges(std::move(edges))
		, traverse(std::move(traverse))
	{
		auto map = path_to_neighbours(0, 3, origin, edges, traverse);
		for (const auto& [node, path] : map)
			table[index(node)] = path.size();

		map = path_to_neighbours(4, 4, origin, edges, traverse);
		std::vector<Node> start;
		start.reserve(map.size());
		for (const auto& [node, _] : map)
			start.push_back(node);

		int max_depth = 4;
		for (bool changed = true; changed; ++max_depth)
		{
			changed = false;
			#pragma omp parallel for
			for (int i = 0; i < start.size(); ++i)
				update_table(start[i], 4, max_depth, changed);
		}
		max_distance_ = max_depth - 1;
	}

	auto begin() const { return table.begin(); }
	auto end() const { return table.end(); }
	int max_distance() const { return max_distance_; }
	int operator[](const Node& node) const { return table[index(node)]; }

	std::vector<Edge> solution(Node node) const
	{
		std::vector<Edge> path;
		uint8_t distance = table[index(node)];
		while (distance > 0)
			for (const Edge& edge : edges)
			{
				Node n = traverse(node, edge);
				uint8_t d = table[index(n)];
				if (d == distance - 1)
				{
					path.push_back(edge);
					node = n;
					distance = d;
					break;
				}
			}
		return path;
	}
};

//template <typename Node, typename Edge>
//class SolutionTable
//{
//	std::unordered_map<Node, std::vector<Edge>> table;
//	int max_distance_;
//public:
//	SolutionTable(
//		const Node& origin,
//		std::vector<Edge> edges,
//		std::function<Node(Node, Edge)> traverse,
//		int max_distance)
//		: max_distance_(max_distance)
//	{
//		table = path_to_neighbours(0, max_distance, origin, edges, traverse);
//		for (auto& [node, path] : table)
//			path = inversed(path);
//	}
//
//	std::optional<std::vector<Edge>> operator[](const Node& node) const
//	{
//		auto it = table.find(node);
//		if (it == table.end())
//			return std::nullopt;
//		return it->second;
//	}
//
//	int max_distance() const { return max_distance_; }
//};
