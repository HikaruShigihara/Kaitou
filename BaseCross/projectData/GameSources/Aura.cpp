#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Aura::OnCreate()
	{
		for (int i = 0; i < params.sides + 1; i++)
		{
			float fSides = static_cast<float>(params.sides);
			float radian = XMConvertToRadians(i * 360.0f / fSides); 
			vertices.push_back({ Vec3(params.topRadius * cosf(radian), params.height, params.topRadius * sinf(radian)), params.topColor, Vec2(i / fSides, 0.0f) }); // è„ÇÃí∏ì_
			vertices.push_back({ Vec3(params.bottomRadius * cosf(radian), 0.0f, params.bottomRadius * sinf(radian)), params.bottomColor, Vec2(i / fSides, params.textureLoops) }); // â∫ÇÃí∏ì_
		}


		uint16_t baseIndices[] = {
			1, 0, 2,
			1, 2, 3,
		};

		std::vector<uint16_t> indices;
		for (int i = 0; i < params.sides; i++)
		{
			for (auto baseIndex : baseIndices)
			{
				indices.push_back(baseIndex + 2 * i);
			}
		}

		auto drawComp = AddComponent<BcPCTStaticDraw>(); 
		drawComp->CreateOriginalMesh(vertices, indices); 
		drawComp->SetOriginalMeshUse(true);
		if (params.textureKey != L"") 
		{
			drawComp->SetTextureResource(params.textureKey); 
		}
		drawComp->SetBlendState(BlendState::Additive); 
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		if (params.textureLoops > 1.0f || params.uvOffsetSpeed.length() != 0.0f)
		{
			drawComp->SetSamplerState(SamplerState::AnisotropicWrap);
		}

		auto ptrTransform = GetComponent<Transform>();
		auto ptrParent = m_parent.lock();
		if (ptrParent) {
			ptrTransform->SetParent(ptrParent);
		}


		SetAlphaActive(true); 
	}

	void Aura::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		for (auto& vertex : vertices)
		{
			vertex.textureCoordinate += delta * params.uvOffsetSpeed;
		}

		auto drawComp = GetComponent<BcPCTStaticDraw>();
		drawComp->UpdateVertices(vertices);
	}
}