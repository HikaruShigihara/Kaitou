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
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
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
			Vec2(581.0f, 132.0f),
			Vec3(-600.0f, -400.0f, 0.0f),
			Vec3(0.8f),
			-3,
			Col4(1.0f),
			m_titleflame
			);
		AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(0.0f, -400.0f, 0.0f),
			Vec3(0.8f),
			-3,
			Col4(1.0f),
			m_titleflame
			);
		AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(600.0f, -400.0f, 0.0f),
			Vec3(0.8f),
			-3,
			Col4(1.0f),
			m_titleflame
			);



		m_Start=
			AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(-600.0f, -400.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_titleflame
			);
		m_Select=
			AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(0.0f, -400.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_titleflame
			);
		m_End=
			AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(600.0f, -400.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_titleflame
			);
		AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(-600.0f, -420.0f, 0.0f),
			Vec3(0.8f),
			-2,
			Col4(1.0f),
			m_Startlogo
			);
		AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(10.0f, -420.0f, 0.0f),
			Vec3(0.8f),
			-2,
			Col4(1.0f),
			m_Selectlogo
			);
		AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(620.0f, -420.0f, 0.0f),
			Vec3(0.8f),
			-2,
			Col4(1.0f),
			m_Endlogo
			);

		m_StartLogoObject=
			AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(-600.0f, -420.0f, 0.0f),
			Vec3(1.0f),
			0,
			Col4(1.0f),
			m_Startlogo
			);
		m_SelectLogoObject=
			AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(10.0f, -420.0f, 0.0f),
			Vec3(1.0f),
			0,
			Col4(1.0f),
			m_Selectlogo
			);
		m_EndLogoObject=
			AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(620.0f, -420.0f, 0.0f),
			Vec3(1.0f),
			0,
			Col4(1.0f),
			m_Endlogo
			);


	}

	void TitleStage::CreateBack() {
		//�^�C�g���̔w�i
		AddGameObject<Title_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-99,
			Col4(1.0f),
			m_title
			);

	}

	void TitleStage::BoolSet() {
		m_Start->SetDrawActive(false);
		m_Select->SetDrawActive(false);
		m_End->SetDrawActive(false);
		m_StartLogoObject->SetDrawActive(false);
		m_SelectLogoObject->SetDrawActive(false);
		m_EndLogoObject->SetDrawActive(false);


	}


	void TitleStage::CreateStage() {
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.25f, 0.0f, 0.0f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.50f, 0.0f, 0.0f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.75f, 0.0f, 0.0f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.75f, 0.25f, 0.0f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.50f, 0.0f, 0.25f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.75f, 0.0f, 0.25f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.25f, 0.0f, 0.25f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.25f)
			);
		AddGameObject<FixedBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.75f, 0.25f, 0.25f)
			);

	}

	
	void TitleStage::OnCreate() {
		try {
			m_SelectChoices = 0;
			m_SelectQuantity = 3;
			//�������Z�L��
			SetPhysicsActive(true);

			CreateViewLight();
			CreateUI();
			CreateBack();
			//CreateStage();
			//�V�[���J�ڂ̎d��(OnUpdate��)
			//App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::stageSelect);

		}
		catch (...) {
			throw;
		}
	}
	
	void TitleStage::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			m_SelectChoices += 1;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			m_SelectChoices -= 1;
		}

		switch (m_SelectChoices)
		{
		case 0:
			BoolSet();
			m_Start->SetDrawActive(true);
			m_StartLogoObject->SetDrawActive(true);

			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
			}

			break;
		case 1:
			BoolSet();
			m_Select->SetDrawActive(true);
			m_SelectLogoObject->SetDrawActive(true);

			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::stageSelect);
			}

			break;
		case 2:

			BoolSet();
			m_End->SetDrawActive(true);
			m_EndLogoObject->SetDrawActive(true);

			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
			}

		}
		
		if (m_SelectChoices >= m_SelectQuantity)
		{
			m_SelectChoices = 0;
		}
		if (m_SelectChoices < 0)
		{
			m_SelectChoices = m_SelectQuantity - 1;
		}

	}
}
//end basecross
