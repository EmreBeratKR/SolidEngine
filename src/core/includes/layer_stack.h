#pragma once


#include <vector>


#include "fwd.h"


namespace Engine
{
	class LayerStack
	{
	public:
		void OnUpdate();
		void OnRender();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

	private:
		std::vector<Layer*> m_Layers;
	};
}