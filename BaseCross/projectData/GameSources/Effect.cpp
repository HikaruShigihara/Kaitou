/*!
@file Effect.cpp
@brief �G�t�F�N�g�֘A
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void RingEffect::OnCreate()
	{
		// ���_�f�[�^�̍쐬����
		for (int i = 0; i < params.sides + 1; i++) // 1�����Ė߂��Ă��āA�o���_�ɂ����_���K�v�Ȃ��߁A���������1�񑽂����[�v����
		{
			float fSides = static_cast<float>(params.sides); // �~�̕�������float�^�ɕϊ�����
			float radian = XMConvertToRadians(i * 360.0f / fSides); // ���_��z�u����p�x���Z�o����
			vertices.push_back({ Vec3(params.topRadius * cosf(radian), params.height, params.topRadius * sinf(radian)), params.topColor, Vec2(i / fSides, 0.0f) }); // ��̒��_
			vertices.push_back({ Vec3(params.bottomRadius * cosf(radian), 0.0f, params.bottomRadius * sinf(radian)), params.bottomColor, Vec2(i / fSides, params.textureLoops) }); // ���̒��_
		}

		// ���[�v�����̃x�[�X�ɂ���C���f�b�N�X
		uint16_t baseIndices[] = {
			1, 0, 2,
			1, 2, 3,
		};

		// �x�[�X�C���f�b�N�X�����Ƃɒ��_�C���f�b�N�X���쐬����
		std::vector<uint16_t> indices;
		for (int i = 0; i < params.sides; i++)
		{
			for (auto baseIndex : baseIndices)
			{
				indices.push_back(baseIndex + 2 * i); // �x�[�X�C���f�b�N�X���Q�����炵�Đݒ肵�Ă���
			}
		}

		// �h���[�R���|�[�l���g��ǉ�����
		auto drawComp = AddComponent<BcPCTStaticDraw>(); // Bc�n�̃R���|�[�l���g���ƁA���_�̐F�ŃA���t�@�u�����h���Ă����
		drawComp->CreateOriginalMesh(vertices, indices); // ��L�̐ݒ�����ƂɃ��b�V���𐶐�����
		drawComp->SetOriginalMeshUse(true); // �Ǝ����b�V��(�v���O�������ō쐬)���g�p���邱�Ƃ�錾����
		if (params.textureKey != L"") // �e�N�X�`�����g�p����ꍇ�̐ݒ�
		{
			drawComp->SetTextureResource(params.textureKey); // �g�p����e�N�X�`����ݒ肷��
		}
		drawComp->SetBlendState(BlendState::Additive); // ���Z���������悤�ɐݒ肷��
		drawComp->SetDepthStencilState(DepthStencilState::Read); // ���̔|���Ɗ����Ȃ��悤�ɂ���]
		if (params.textureLoops > 1.0f || params.uvOffsetSpeed.length() != 0.0f) // ���[�v�A�j���[�V������g��UV���g�p����ꍇ�̓e�N�X�`�����J��Ԃ��ɑΉ��ł���悤�ɐݒ肷��
		{
			drawComp->SetSamplerState(SamplerState::AnisotropicWrap); // �e�N�X�`���A�j���[�V�����p�Ƀ��[�v�\��t���ł���悤�ɂ���
		}

		SetAlphaActive(true); // ���ߏ�����L���ɂ���
	}

	void RingEffect::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		for (auto& vertex : vertices) // �e�N�X�`���A�j���[�V����������
		{
			vertex.textureCoordinate += delta * params.uvOffsetSpeed; // ���ׂĂ̒��_��UV��b���ł��炷
		}

		auto drawComp = GetComponent<BcPCTStaticDraw>();
		drawComp->UpdateVertices(vertices); // �X�V���ꂽ���_�f�[�^���ēK�p����
	}
}
//end basecross
