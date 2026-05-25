#include "xepch.h"
#include "LayerStack.h"

void XEngine::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_LayerInsert, layer);
}

void XEngine::LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
}

void XEngine::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if(it!=m_Layers.end())
	{
		m_Layers.erase(it);
		m_LayerInsert--;
	}
}

void XEngine::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
	}
}

XEngine::LayerStack::LayerStack()
{
	m_LayerInsert = m_Layers.begin();
}

XEngine::LayerStack::~LayerStack()
{
	for(Layer* layer : m_Layers)
	{
		delete layer;
	}
}
