#pragma once

#ifdef WINDOWS

#include <d3d11_1.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <dxgi.h>
#include <d2d1_1helper.h>

#include <string>

#include "../../../../y_Utility/Utility.h"
#include "../../../../DataTypes/DataTypes.h"


namespace SClick::Core::Renderer::Internal
{
	class DX2DResourceCreator
	{
	private:
		ID3D11Device*			m_3DDevice;
		ID3D11DeviceContext*	m_3DContext;
		ID3D11Texture2D*		m_backbuffer;

		ID2D1Factory1*			m_factory;
		ID2D1Device*			m_device;
		ID2D1DeviceContext*		m_context;
		ID2D1Bitmap1*			m_renderTargetBitmap;
		ID2D1SolidColorBrush*	m_brush;

		IDXGIFactory2*			m_dxgiFactory;
		IDXGIDevice1*			m_dxgiDevice;
		IDXGISwapChain1*		m_swapchain;
		IDXGISurface*			m_dxgiBackbuffer;
		IDXGIAdapter*			m_adapter;

		HWND m_handle;

	public:
		DX2DResourceCreator(HWND p_handle);
		DX2DResourceCreator();
		~DX2DResourceCreator();

	public:
		DataType::ErrorHandling::Result<int, DataType::ErrorHandling::TemplateFriendlyString<255>> Init();
		void Shutdown();

	public:
		ID2D1DeviceContext* GetContext() const;
		IDXGISwapChain1* GetSwapChain() const;
		ID2D1SolidColorBrush* GetBrush() const;
		HWND GetHandle();
		ID2D1SolidColorBrush* EditBrush(DataType::Color color) const;
	};
}

#endif 