/*!
@file TitleStage.cpp
@brief タイトル
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
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
	void TitleStage::CreateCloud() {
		//auto cloud = AddGameObject<Cloud>(
		//	Vec2(1920.0f, 1080.0f),
		//	Vec3(-1000.0f, 0.0f, 0.0f),
		//	Vec3(1.0f),
		//	-98,
		//	Col4(1.0f),
		//	m_cloud
		//	);
		//auto pos = cloud->GetComponent<Transform>()->GetPosition();
		//if (pos.x >= 1000.0f) {
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(-1000.0f, 300.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud1
			);

		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(-1500.0f, 0.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud2
			);
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(-300.0f, -300.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud3
			);
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(-500.0f, 0.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud4
			);
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud4
			);
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(500.0f, 300.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud2
			);
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(0.0f, 300.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud1
			);
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(500.0f, -300.0f, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud1
			);
		AddGameObject<Cloud>(
			Vec2(1027.0f, 652.0f),
			Vec3(-700.0f, -300, 0.0f),
			Vec3(0.5f),
			-98,
			Col4(1.0f),
			m_cloud4
			);

	}


	void TitleStage::CreateBack() {
		//タイトルの背景
		AddGameObject<Title_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-99,
			Col4(1.0f),
			m_title
			);
		AddGameObject<Title_Kai>(
			Vec2(927.0f, 923.0f),
			Vec3(-500.0f, 100.0f, 0.0f),
			Vec3(1.0f),
			-97,
			Col4(1.0f),
			m_Kai
			);
		AddGameObject<Title_UI>(
			Vec2(902.0f, 922.0f),
			Vec3(500.0f, 100.0f, 0.0f),
			Vec3(1.0f),
			-97,
			Col4(1.0f),
			m_Tou
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


	//void TitleStage::CreateStage() {
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.0f, 0.0f, 0.0f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.25f, 0.0f, 0.0f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.50f, 0.0f, 0.0f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.75f, 0.0f, 0.0f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.75f, 0.25f, 0.0f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.50f, 0.0f, 0.25f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.75f, 0.0f, 0.25f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.25f, 0.0f, 0.25f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.0f, 0.0f, 0.25f)
	//		);
	//	AddGameObject<FixedBox>(
	//		Vec3(0.25f, 0.25f, 0.25f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(0.75f, 0.25f, 0.25f)
	//		);

	//}

	
	void TitleStage::OnCreate() {
		try {
			m_SelectChoices = 0;
			m_SelectQuantity = 3;
			//物理演算有効
			//SetPhysicsActive(true);

			CreateViewLight();
			CreateUI();
			CreateBack();
			CreateCloud();
			//CreateStage();
			//シーン遷移の仕方(OnUpdateに)
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
