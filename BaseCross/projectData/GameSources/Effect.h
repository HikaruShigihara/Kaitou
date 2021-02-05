/*!
@file Effect.h
@brief �G�t�F�N�g�֘A
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class RingEffect : GameObject {
	public:
		struct InitParams
		{
			std::wstring textureKey; //���\�[�X
			int sides; // ������
			float height; // ����
			float topRadius; // ��̔��a
			float bottomRadius; // ���̔��a
			Col4 topColor; // ��̐F
			Col4 bottomColor; // ���̐F
			Vec2 uvOffsetSpeed; // UV�A�j���[�V����
			float textureLoops; // �e�N�X�`��U���W

			InitParams(const wstring& textureKey, int sides, float height, float topRadius, float bottomRadius, const Col4& topColor, const Col4& bottomColor, const Vec2& speed, float textureLoops)
				: textureKey(textureKey), sides(sides), height(height), topRadius(topRadius), bottomRadius(bottomRadius), topColor(topColor), bottomColor(bottomColor), uvOffsetSpeed(speed), textureLoops(textureLoops)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float topRadius, float bottomRadius, const Col4& topColor, const Col4& bottomColor, const Vec2& speed)
				: InitParams(textureKey, sides, height, topRadius, bottomRadius, topColor, bottomColor, speed, 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius)
				: InitParams(textureKey, sides, height, radius, radius, Col4(1.0f), Col4(1.0f), Vec2(0.0f), 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius, const Col4& color)
				: InitParams(textureKey, sides, height, radius, radius, color, color, Vec2(0.0f), 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius, const Col4& color, const Vec2& uvOffsetSpeed)
				: InitParams(textureKey, sides, height, radius, radius, color, color, uvOffsetSpeed, 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius, const Col4& topColor, const Col4& bottomColor, const Vec2& uvOffsetSpeed)
				: InitParams(textureKey, sides, height, radius, radius, topColor, bottomColor, uvOffsetSpeed, 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float topRadius, float bottomRadius)
				: InitParams(textureKey, sides, height, topRadius, bottomRadius, Col4(1.0f), Col4(1.0f), Vec2(0.0f), 1.0f)
			{
			}

			InitParams()
				: InitParams(L"", 30, 1.0f, 1.0f, 1.0f, Col4(1.0f), Col4(1.0f), Vec2(0.0f), 1.0f)
			{
			}

		};

	private:
		std::vector<VertexPositionColorTexture> vertices;

		InitParams params;

	public:
		RingEffect(const std::shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}

		RingEffect(const std::shared_ptr<Stage>& stage, const RingEffect::InitParams& initParams)
			: GameObject(stage), params(initParams)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

	};

}
//end basecross
