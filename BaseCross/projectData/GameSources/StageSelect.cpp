/*!
@file StageSelect.cpp
@brief ステージセレクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageSelect::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void StageSelect::CreateUI(){
		AddGameObject<StageSelect_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			0,
			Col4(1.0f),
			m_StageSelect_image
			);

		AddGameObject<StageSelect_UI>(
			Vec2(190.0f, 181.0f),
			Vec3(-400.0f, 220.0f, 0.0f),
			Vec3(0.75f),
			0,
			Col4(1.0f),
			m_BlackStar
			);

		AddGameObject<StageSelect_UI>(
			Vec2(190.0f, 181.0f),
			Vec3(-250.0f, 220.0f, 0.0f),
			Vec3(0.75f),
			0,
			Col4(1.0f),
			m_BlackStar
			);

		AddGameObject<StageSelect_UI>(
			Vec2(190.0f, 181.0f),
			Vec3(-100.0f, 220.0f, 0.0f),
			Vec3(0.75f),
			0,
			Col4(1.0f),
			m_BlackStar
			);

		m_Stage01=
			AddGameObject<StageSelect_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_StageSelect_Stage01
			);
		m_Stage02=
			AddGameObject<StageSelect_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_StageSelect_Stage02
			);

		m_Stage03=
			AddGameObject<StageSelect_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_StageSelect_Stage03
			);

		m_StageArrowRight =
			AddGameObject<StageSelect_ArrowRight>(
			Vec2(230.0f, 159.0f),
			Vec3(650.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			3,
			Col4(1.0f),
			m_StageSelect_Arrow
			);
		m_StageArrowLeft =
			AddGameObject<StageSelect_ArrowLeft>(
				Vec2(230.0f, 159.0f),
				Vec3(-650.0f, 0.0f, 0.0f),
				Vec3(-1.0f,1.0f,1.0f),
				3,
				Col4(1.0f),
				m_StageSelect_Arrow
				);




	}

	void StageSelect::BoolCheck() {
		m_Stage01->SetDrawActive(false);
		m_Stage02->SetDrawActive(false);
		m_Stage03->SetDrawActive(false);

	}
	

	void StageSelect::OnCreate() {
		try {
			m_StageSelectNumber = 0;
			m_StageQuantity = 3;
			CreateViewLight();
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}
	
	void StageSelect::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		time += elapsedTime;

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			m_StageSelectNumber += 1;
			m_StageArrowRight->SetTexture(m_StageSelect_Arrow_yellow);
			PlaySE(L"Motion-Pop36-1.wav", 0.5f);
			time = 0;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			m_StageSelectNumber -= 1;
			m_StageArrowLeft->SetTexture(m_StageSelect_Arrow_yellow);
			PlaySE(L"Motion-Pop36-1.wav", 0.5f);

			time = 0;

		}

		switch (m_StageSelectNumber)
		{
		case 0:
			BoolCheck();
			m_Stage01->SetDrawActive(true);
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->SetSelectNumber(m_StageSelectNumber);
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);

			}

			break;
		case 1:
			BoolCheck();
			m_Stage02->SetDrawActive(true);
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->SetSelectNumber(m_StageSelectNumber);
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);

			}
			break;
		case 2:
			BoolCheck();
			m_Stage03->SetDrawActive(true);
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			    App::GetApp()->GetScene<Scene>()->SetSelectNumber(m_StageSelectNumber);
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
			}

			break;


		}
		if (m_StageSelectNumber >= m_StageQuantity)
		{
			m_StageSelectNumber = 0;
		}
		if (m_StageSelectNumber < 0)
		{
			m_StageSelectNumber = m_StageQuantity - 1;
		}

		if (time >= 0.2f) {

			m_StageArrowRight->SetTexture(m_StageSelect_Arrow);
			m_StageArrowLeft->SetTexture(m_StageSelect_Arrow);
		}
	}







	//int SelectStageClass::SelectStage()
	//{
	//	auto a = shared_ptr<StageSelect>()->m_StageSelectNumber;
	//	return a;
	//}




}
//end basecross
