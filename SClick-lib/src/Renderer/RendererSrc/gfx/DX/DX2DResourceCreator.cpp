#include "pch.h"

#ifdef WINDOWS


#include "DX2DResourceCreator.h"

//TODO: Make DPI freindly

//TODO: Fix Scaling issues, Backbuffer does not resize with window

namespace SClick::Core::Renderer::Internal
{
	DX2DResourceCreator::DX2DResourceCreator(HWND p_handle): 
		m_3DDevice(nullptr),
		m_3DContext(nullptr),
		m_backbuffer(nullptr),
		m_factory(nullptr), 
		m_device(nullptr),
		m_context(nullptr),
		m_renderTargetBitmap(nullptr),
		m_brush(nullptr),
		m_dxgiFactory(nullptr),
		m_dxgiDevice(nullptr),
		m_swapchain(nullptr),
		m_dxgiBackbuffer(nullptr),
		m_adapter(nullptr),
		m_handle(p_handle)
	{}

	DX2DResourceCreator::DX2DResourceCreator() : 
		m_3DDevice(nullptr),
		m_3DContext(nullptr),
		m_backbuffer(nullptr),
		m_factory(nullptr),
		m_device(nullptr),
		m_context(nullptr),
		m_renderTargetBitmap(nullptr),
		m_brush(nullptr),
		m_dxgiFactory(nullptr),
		m_dxgiDevice(nullptr),
		m_swapchain(nullptr),
		m_dxgiBackbuffer(nullptr),
		m_adapter(nullptr),
		m_handle(NULL)
	{}

	DX2DResourceCreator::~DX2DResourceCreator()
	{
		Shutdown();
	}

	ID2D1DeviceContext* DX2DResourceCreator::GetContext() const
	{
		return m_context;
	}

	IDXGISwapChain1* DX2DResourceCreator::GetSwapChain() const
	{
		return m_swapchain;
	}

	ID2D1SolidColorBrush* DX2DResourceCreator::GetBrush() const
	{
		return m_brush;
	}

	HWND DX2DResourceCreator::GetHandle()
	{
		return m_handle;
	}

	ID2D1SolidColorBrush* DX2DResourceCreator::EditBrush(DataType::Color color) const
	{
		return nullptr;
	}

	DataType::ErrorHandling::Result<int, DataType::ErrorHandling::TemplateFriendlyString<255>> DX2DResourceCreator::Init()
	{
		DataType::ErrorHandling::Result<int, DataType::ErrorHandling::TemplateFriendlyString<255>> result = {};
		result.value = 0;

		HRESULT hr = S_OK;

		if (!m_handle)
		{
			result.isError = true;
			result.error = "No Window Handle";
			return result;
		}

		//Create DX3D device and DX3D Context
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&m_3DDevice,
			nullptr,
			&m_3DContext);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "D3D11CreateDevice Failed";
			return result;
		}

		//Create DXGI Device
		hr = m_3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgiDevice);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "m_3DDevice->QueryInterface Failed";
			return result;
		}

		//Create DXGI factory and Adapter
		m_dxgiDevice->GetAdapter(&m_adapter);

		m_adapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory));

		//Create DX2D Factory
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "D2D1CreateFactory Failed";
			return result;
		}

		//Create DX2D device
		hr = m_factory->CreateDevice(m_dxgiDevice, &m_device);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "m_factory->CreateDevice Failed";
			return result;
		}

		//Create Dx2D Device Context
		hr = m_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_context);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "m_device->CreateDeviceContext Failed";
			return result;
		}

		//Create Swap Chain
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = 0;                           
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; 
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;               
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                    
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; 
		swapChainDesc.Flags = 0;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullscreenDesc = { 0 };
		swapChainFullscreenDesc.RefreshRate = {1, 144};
		swapChainFullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;
		swapChainFullscreenDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
		swapChainFullscreenDesc.Windowed = TRUE;

		hr = m_dxgiFactory->CreateSwapChainForHwnd(m_3DDevice, m_handle, &swapChainDesc, &swapChainFullscreenDesc, nullptr, &m_swapchain);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "m_dxgiFactory->CreateSwapChainForHwnd Failed";
			return result;
		}

		hr = m_dxgiDevice->SetMaximumFrameLatency(1);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "m_dxgiDevice->SetMaximumFrameLatency Failed";
			return result;
		}

		hr = m_swapchain->GetBuffer(0, IID_PPV_ARGS(&m_backbuffer));

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "m_swapchain->GetBuffer Failed";
			return result;
		}

		auto windowDPI = GetDpiForWindow(m_handle);

		//Create Render Target and link to swapchain
		D2D1_BITMAP_PROPERTIES1 bitmapProperties =
			D2D1::BitmapProperties1(
				D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
				D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
				windowDPI,
				windowDPI
			);

		hr = m_swapchain->GetBuffer(0, IID_PPV_ARGS(&m_dxgiBackbuffer));

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = "m_swapchain->GetBuffer Failed";
			return result;
		}

		hr = m_context->CreateBitmapFromDxgiSurface(m_dxgiBackbuffer, &bitmapProperties, &m_renderTargetBitmap);

		if (hr != S_OK)
		{
			result.isError = true;
			result.error = " m_context->CreateBitmapFromDxgiSurface Failed";
			return result;
		}

		m_context->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 0.3f), &m_brush);
		m_context->SetDpi(windowDPI, windowDPI);

		m_context->SetTarget(m_renderTargetBitmap);

		return result;
	}

	void DX2DResourceCreator::Shutdown()
	{
		if (m_3DDevice)
		{
			m_3DDevice->Release();
			m_3DDevice = nullptr;
		}
		if (m_3DContext)
		{
			m_3DContext->Release();
			m_3DContext = nullptr;
		}
		if (m_backbuffer)
		{
			m_backbuffer->Release();
			m_backbuffer = nullptr;
		}
		if (m_factory)
		{
			m_factory->Release();
			m_factory = nullptr;
		}
		if (m_device)
		{
			m_device->Release();
			m_device = nullptr;
		}
		if (m_context)
		{
			m_context->Release();
			m_context = nullptr;
		}
		if (m_renderTargetBitmap)
		{
			m_renderTargetBitmap->Release();
			m_renderTargetBitmap = nullptr;
		}
		if (m_brush)
		{
			m_brush->Release();
			m_brush = nullptr;
		}
		if (m_dxgiFactory)
		{
			m_dxgiFactory->Release();
			m_dxgiFactory = nullptr;
		}
		if (m_dxgiDevice)
		{
			m_dxgiDevice->Release();
			m_dxgiDevice = nullptr;
		}
		if (m_swapchain)
		{
			m_swapchain->Release();
			m_swapchain = nullptr;
		}
		if (m_dxgiBackbuffer)
		{
			m_dxgiBackbuffer->Release();
			m_dxgiBackbuffer = nullptr;
		}
		if (m_adapter)
		{
			m_adapter->Release();
			m_adapter = nullptr;
		}
	}
}

#endif