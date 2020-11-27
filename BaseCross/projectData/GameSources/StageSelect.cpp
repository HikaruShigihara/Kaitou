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

		m_Banana=
			AddGameObject<StageSelect_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_StageSelect_test
			);
		m_Gorira=
			AddGameObject<StageSelect_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_StageSelect_test2
			);


	}

	void StageSelect::BoolCheck() {
		m_Banana->SetDrawActive(false);
		m_Gorira->SetDrawActive(false);

	}

	void StageSelect::OnCreate() {
		try {
			m_StageSelectNumber = 0;
			m_StageQuantity = 2;
			CreateViewLight();
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

	void StageSelect::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			m_StageSelectNumber += 1;
		}
		switch (m_StageSelectNumber)
		{
			case 0:
				BoolCheck();
				m_Banana->SetDrawActive(true);
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
				}

				break;
			case 1:
				BoolCheck();
				m_Gorira->SetDrawActive(true);
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
				}

				break;


		}
		if (m_StageSelectNumber >= m_StageQuantity)
		{
			m_StageSelectNumber = 0;
		}

	}


}
//end basecross
