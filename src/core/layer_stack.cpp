#include <algorithm>


#include "layer_stack.h"


namespace Engine
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}


	void LayerStack::OnUpdate()
	{
		for (const auto& layer : m_Layers)
		{
			layer->OnUpdate();
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_Layers.push_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto position = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (position == m_Layers.end()) return;

		layer->OnDetach();
		m_Layers.erase(position);
	}
}