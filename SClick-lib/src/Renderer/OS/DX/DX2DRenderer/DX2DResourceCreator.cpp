#include "pch.h"
#include "DX2DResourceCreator.h"

namespace Core::Renderer::Internal
{
	DX2DResourceCreator::DX2DResourceCreator(HWND p_handle): m_factory(nullptr), m_renderTarget(nullptr),
		m_bitmap(nullptr), m_brush(nullptr), m_handle(p_handle)
	{}
	DX2DResourceCreator::~DX2DResourceCreator()
	{
		Shutdown();
	}

    ID2D1Factory* DX2DResourceCreator::GetFactory() const
    {
        return m_factory;
    }

	ID2D1HwndRenderTarget* DX2DResourceCreator::GetRenderTarget() const
	{
		return m_renderTarget;
	}

	ID2D1Bitmap* DX2DResourceCreator::GetBitmap() const
	{
		return m_bitmap;
	}

	ID2D1SolidColorBrush* DX2DResourceCreator::GetBrush() const
	{
		return m_brush;
	}

	HRESULT DX2DResourceCreator::Init()
	{
		HRESULT hr = S_OK;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);

		if (hr != S_OK)
			return hr;

		RECT rc;
		GetClientRect(m_handle, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		hr = m_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_handle, size), &m_renderTarget);

		if (hr != S_OK)
			return hr;

		hr = m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &m_brush);

		if (hr != S_OK)
			return hr;

		return hr;
	}

	void DX2DResourceCreator::Shutdown()
	{
		if (m_factory)
		{
			m_factory->Release();
			m_factory = nullptr;
		}

		if (m_renderTarget)
		{
			m_renderTarget->Release();
			m_renderTarget = nullptr;
		}

		if (m_bitmap)
		{
			m_bitmap->Release();
			m_bitmap = nullptr;
		}

		if (m_brush)
		{
			m_brush->Release();
			m_brush = nullptr;
		}
	}
}
