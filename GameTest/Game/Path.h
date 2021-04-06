#pragma once
#include <vector>
#include "gtk/gtk.h"
#include "Components.h"

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FORWARD,
	BACK
};


struct Path
{

	std::vector<gtk::vec3> nodes;

	void Init(const gtk::vec3& startPos)
	{
		// Clears the nodes
		nodes.clear();
		nodes.push_back(startPos);
	}

	void Add(const Direction& dir, const int& count)
	{
		using namespace gtk;

		// Ensure there's a start node
		ASSERT(nodes.size() > 0);

		// Create new nodes in the requested direction
		for (size_t i = 0; i < count; i++)
		{
			switch (dir)
			{
			case LEFT:
				nodes.push_back(vec3(nodes.back()) + vec3(-6.0f, 0.0f, 0.0f));
				break;

			case RIGHT:
				nodes.push_back(vec3(nodes.back()) + vec3(6.0f, 0.0f, 0.0f));
				break;

			case UP:
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, 6.0f, 0.0f));
				break;

			case DOWN:
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, -6.0f, 0.0f));
				break;

			case FORWARD:
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, 0.0f, 6.0f));
				break;

			case BACK:
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, 0.0f, -6.0f));
				break;
			}

		}

	}

	void CreatePathinScene(gtk::Scene& scene, gtk::RenderLayer layer, gtk::CollisionGroup colGroup)
	{
		using namespace gtk;

		int i = 0;
		for (const vec3& pos : nodes)
		{
			// Create the entities and componenets for each node
			Entity& node = scene.CreateEntity("PathNode" + std::to_string(i));
			scene.AddRenderer(node, layer, new CubeRenderer(vec3(0.9f, 0.5f, 0.2f)));
			scene.AddCollider(node, colGroup, new SphereCollider());
			node.Scale(3.0f);
			node.Pos(pos);
			i++;
		}
	}

};