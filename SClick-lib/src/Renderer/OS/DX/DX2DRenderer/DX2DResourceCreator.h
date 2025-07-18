#pragma once


#include <d3d11_1.h>
#include <d2d1.h>
#include <d2d1_1.h>

namespace Core::Renderer::Internal
{
	class DX2DResourceCreator
	{
	public:
		DX2DResourceCreator(HWND p_handle);
		~DX2DResourceCreator();

	public:
		ID2D1Factory* GetFactory() const;
		ID2D1HwndRenderTarget* GetRenderTarget() const;
		ID2D1Bitmap* GetBitmap() const;
		ID2D1SolidColorBrush* GetBrush() const;

	private:
		ID2D1Factory* m_factory;
		ID2D1HwndRenderTarget* m_renderTarget;
		ID2D1Bitmap* m_bitmap;
		ID2D1SolidColorBrush* m_brush;
		HWND m_handle;

	private:
		HRESULT Init();
		void Shutdown();
	};
}
