#include "Gate.h"
#include "Shaders/ShadersHelper.h"

StarGate::StarGate()
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_gateVertices, sizeof(s_gateVertices))
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_gateTriList, sizeof(s_gateTriList))
	);

	m_ProgramHandle = ShadersHelper::LoadProgram("vs_cubes", "fs_cubes");
}

InnerRing::InnerRing()
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_ringVertices, sizeof(s_ringVertices))
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_ringTriList, sizeof(s_ringTriList))
	);

	m_ProgramHandle = ShadersHelper::LoadProgram("vs_cubes", "fs_cubes");
}