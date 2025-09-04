#include "pch.h"
#include "sclick\renderer\sclickrendercalls.h"
#include "dx2dresourcecreator.h"

//TODO: Look into ways to batch render operations together
//TODO: Need a way to create a buffer you can draw to separate from Backbuffer

namespace SClick::Core::Renderer
{
	namespace //-----INTERNAL-----//
	{
		enum SClickRenderErrorCodes
		{
			None = 0,
			ResourceCreationError = 1,
			DrawError = 2
		};

		struct SClickRenderError
		{
			SClickRenderErrorCodes currentCode = SClickRenderErrorCodes::None;
		} RenderError;

		SClick::Core::Renderer::Internal::DX2DResourceCreator resources;
	}

	void SCRender_Init(void* window)
	{
		resources = { (HWND)window };

		auto result = resources.Init();
		if (!result)
		{
			RenderError.currentCode = SClickRenderErrorCodes::None;
			return;
		}

		result.GetError().Print();
		RenderError.currentCode = SClickRenderErrorCodes::ResourceCreationError;
	}

	void SCRender_Shutdown()
	{
		resources.Shutdown();
	}

	int SCRender_GetStatus()
	{
		using SClick::Core::Renderer::SClickRenderErrorCodes;

		auto code = RenderError.currentCode;
		switch (code)
		{
		case (None):
			break;
		case (ResourceCreationError):
			std::cout << "SClick failed to construct render resources" << std::endl;
			break;
		case (DrawError):
			std::cout << "SClick Failed to draw" << std::endl;
		}
		return code;
	}

	void SCRender_BeginDraw()
	{
		resources.GetContext()->BeginDraw();
	}

	void SCRender_EndDraw()
	{
		resources.GetContext()->EndDraw();
	}

	void SCRender_ClearFrame()
	{
		resources.GetContext()->Clear(D2D1::ColorF(D2D1::ColorF::DimGray, 1.0f));
	}

	void SCRender_PresentFrame()
	{
		//TODO: Look into Present1s present parameters to optimize presentation.
		//This currently takes a minimum of 5ms, thats too long just for presenting the frame
		DXGI_PRESENT_PARAMETERS parameters = { 0 };
		resources.GetSwapChain()->Present1(1, 0, &parameters);
	}

	void SCRender_DrawRect(DataType::Rect rect, DataType::Color color)
	{
		resources.GetBrush()->SetColor(D2D1::ColorF((float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, (float)color.a / 255.0f));
		resources.GetContext()->FillRectangle(D2D1::Rect(rect.xPos, rect.yPos, rect.width, rect.height), resources.GetBrush());
	}
}
