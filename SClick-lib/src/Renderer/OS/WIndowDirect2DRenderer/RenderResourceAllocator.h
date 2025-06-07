#pragma once
#include "pch.h"

struct RenderResourceAllocator
{
public:
	ID2D1Factory* ptr_factory;
	ID2D1HwndRenderTarget* ptr_renderTarget;

public:
	RenderResourceAllocator(HWND p_handle) : m_handle(p_handle) { Init(); }
	~RenderResourceAllocator() { ShutDown(); }
public:
	HWND GetHandle() { return m_handle; }

private:
	LRESULT Init()
	{

	}

	void ShutDown()
	{
		if (ptr_factory)
			(*ptr_factory).Release();
		if(ptr_renderTarget)
			(*ptr_renderTarget).Release();

		ptr_factory = nullptr;
		ptr_renderTarget = nullptr;
	}

private:
	HWND m_handle;
};
