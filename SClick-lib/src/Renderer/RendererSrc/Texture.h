#pragma once

#include <cstdint>

#include "../../DataTypes/DataTypes.h"

namespace SClick::Core::Renderer
{ 
	struct Texture
	{
	public:
		const std::uint32_t m_familiarUuid;
		DataType::Rect m_rect;
		DataType::Color m_color;

	public:
		Texture(const std::uint32_t p_uuid);
	};
}
