/*!
@file TitleStage.cpp
@brief �^�C�g��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleStage::CreateUI() {
		AddGameObject<Title_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			0,
			Col4(1.0f),
			m_title
			);

	}

	void TitleStage::CreateStage() {
		AddGameObject<FixedBox>(
			Vec3(10.0f, 1.0f, 10.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
			);
	}

	void TitleStage::CreatePlayer() {
		AddGameObject<Player>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f),
			Vec3(0, 1.50f, 0)
			);
	}
	
	void TitleStage::OnCreate() {
		try {
			//�������Z�L��
			SetPhysicsActive(true);

			CreateViewLight();
			//CreateUI();
			CreateStage();
			CreatePlayer();
			//�V�[���J�ڂ̎d��(OnUpdate��)
			//App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::stageSelect);

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
