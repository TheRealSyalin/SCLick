#pragma once

#include "sclick/datatypes/datatypes.h"

namespace SClick::Core::Renderer
{
	void SCRender_Init(void* windowHandle);
	void SCRender_Shutdown();
	int SCRender_GetStatus();

	void SCRender_BeginDraw();
	void SCRender_EndDraw();
	void SCRender_ClearFrame();
	void SCRender_PresentFrame();
	void SCRender_DrawRect(DataType::Rect rect, DataType::Color color);
	void SCRender_DrawElipse();
	void SCRender_DrawLine();
	//void SCRender_LayerToBitmap(RenderLayer layer);
}