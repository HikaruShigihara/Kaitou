/*!
@file ResultStage.cpp
@brief リザルト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
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

	void ResultStage::CreateUI() {

		AddGameObject<Result_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(-600.0f, -400.0f, 0.0f),
			Vec3(0.8f),
			-3,
			Col4(1.0f),
			m_titleflame
			);
		AddGameObject<Result_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(0.0f, -400.0f, 0.0f),
			Vec3(0.8f),
			-3,
			Col4(1.0f),
			m_titleflame
			);
		AddGameObject<Result_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(600.0f, -400.0f, 0.0f),
			Vec3(0.8f),
			-3,
			Col4(1.0f),
			m_titleflame
			);


			AddGameObject<Result_UI>(
				Vec2(1920.0f, 1080.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.0f),
				-4,
				Col4(1.0f),
				m_Result_image
				);
			m_Start =
				AddGameObject<Result_UI>(
					Vec2(581.0f, 132.0f),
					Vec3(-600.0f, -400.0f, 0.0f),
					Vec3(1.0f),
					-1,
					Col4(1.0f),
					m_titleflame
					);
			m_Select =
				AddGameObject<Result_UI>(
					Vec2(581.0f, 132.0f),
					Vec3(0.0f, -400.0f, 0.0f),
					Vec3(1.0f),
					-1,
					Col4(1.0f),
					m_titleflame
					);
			m_End =
				AddGameObject<Result_UI>(
					Vec2(581.0f, 132.0f),
					Vec3(600.0f, -400.0f, 0.0f),
					Vec3(1.0f),
					-1,
					Col4(1.0f),
					m_titleflame
					);
			m_SelectArrowNumber1 =
				AddGameObject<Title_Arrow>(
					Vec2(256.0f, 256.0f),
					Vec3(-600.0f, -280.0f, 0.0f),
					Vec3(0.4f),
					1,
					Col4(1.0f),
					m_SelectArrow
					);
			m_SelectArrowNumber2 =
				AddGameObject<Title_Arrow>(
					Vec2(256.0f, 256.0f),
					Vec3(-10.0f, -280.0f, 0.0f),
					Vec3(0.4f),
					1,
					Col4(1.0f),
					m_SelectArrow
					);

			m_SelectArrowNumber3 =
				AddGameObject<Title_Arrow>(
					Vec2(256.0f, 256.0f),
					Vec3(610.0f, -280.0f, 0.0f),
					Vec3(0.4f),
					1,
					Col4(1.0f),
					m_SelectArrow
					);

			///
			 m_text_next = AddGameObject<UI_Text>(
				m_FontName,
				50.0f,
				Col4(0.0f, 0.0f, 0.0f, 1.0f),
				Rect2D<float>(-1200.0f, 910.0f, 1900.0f, 800.0f),
				StringSprite::TextAlignment::m_Center,
				m_nextStage_text,
				5,
				false
				);
			 m_text_next2 = AddGameObject<UI_Text>(
				 m_FontName,
				 65.0f,
				 Col4(0.0f, 0.0f, 0.0f, 1.0f),
				 Rect2D<float>(-1200.0f, 900.0f, 1900.0f, 800.0f),
				 StringSprite::TextAlignment::m_Center,
				 m_nextStage_text,
				 5,
				 false
				 );

			 m_text_stageselect = AddGameObject<UI_Text>(
				 m_FontName,
				 50.0f,
				 Col4(0.0f, 0.0f, 0.0f, 1.0f),
				 Rect2D<float>(10.0f, 910.0f, 1900.0f, 800.0f),
				 StringSprite::TextAlignment::m_Center,
				 m_stageSelect_text,
				 5,
				 false
				 );
			 m_text_stageselect2 = AddGameObject<UI_Text>(
				 m_FontName,
				 65.0f,
				 Col4(0.0f, 0.0f, 0.0f, 1.0f),
				 Rect2D<float>(10.0f, 900.0f, 1900.0f, 800.0f),
				 StringSprite::TextAlignment::m_Center,
				 m_stageSelect_text,
				 5,
				 false
				 );

			 m_text_backtitle = AddGameObject<UI_Text>(
				 m_FontName,
				 50.0f,
				 Col4(0.0f, 0.0f, 0.0f, 1.0f),
				 Rect2D<float>(1200.0f, 910.0f, 1900.0f, 800.0f),
				 StringSprite::TextAlignment::m_Center,
				 m_backTitle_text,
				 5,
				 false
				 );
			 m_text_backtitle2 = AddGameObject<UI_Text>(
				 m_FontName,
				 65.0f,
				 Col4(0.0f, 0.0f, 0.0f, 1.0f),
				 Rect2D<float>(1200.0f, 900.0f, 1900.0f, 800.0f),
				 StringSprite::TextAlignment::m_Center,
				 m_backTitle_text,
				 5,
				 false
				 );

			 m_number = App::GetApp()->GetScene<Scene>()->m_number_scene;
			 auto wstringNumber = std::to_wstring(m_number);
			 AddGameObject<UI_Text>(
				 L"HGP創英角ﾎﾟｯﾌﾟ体",
				 100.0f,
				 Col4(1.0f),
				 Rect2D<float>(0.0f, 600.0f, 1900.0f, 800.0f),
				 StringSprite::TextAlignment::m_Center,
				 L"歩数：" + wstringNumber,
				 5,
				 false
				 );


			auto SelectNumber = App::GetApp()->GetScene<Scene>()->GetSelectNumber();
			m_StarQuantity=App::GetApp()->GetScene<Scene>()->GetStageStar(SelectNumber);
	switch (m_StarQuantity){
		case 3:
			AddGameObject<Result_Star3>(
				Vec2(190.0f, 180.0f),
				Vec3(297.0f, 107.0f, 0.0f),
				Vec3(3.0f),
				0,
				Col4(1.0f),
				m_Result_StarOnly
				);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"Shortbridge27-01.wav", 0.2f);
		case 2:
		
			AddGameObject<Result_Star2>(
				Vec2(190.0f, 180.0f),
				Vec3(19.0f, 107.0f, 0.0f),
				Vec3(3.0f),
				0,
				Col4(1.0f),
				m_Result_StarOnly
				);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"Shortbridge27-01.wav", 0.2f);

		case 1:
			AddGameObject<Result_Star1>(
				Vec2(190.0f, 180.0f),
				Vec3(-259.0f, 107.0f, 0.0f),
				Vec3(3.0f),
				0,
				Col4(1.0f),
				m_Result_StarOnly
				);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"Shortbridge27-01.wav", 0.2f);

		}

	}

	void ResultStage::BoolSet() {
		m_Start->SetDrawActive(false);
		m_Select->SetDrawActive(false);
		m_End->SetDrawActive(false);
		m_SelectArrowNumber1->SetDrawActive(false);
		m_SelectArrowNumber2->SetDrawActive(false);
		m_SelectArrowNumber3->SetDrawActive(false);


		m_text_next->SetDrawActive(false);
		m_text_stageselect->SetDrawActive(false);
		m_text_backtitle->SetDrawActive(false);
		m_text_next2->SetDrawActive(false);
		m_text_stageselect2->SetDrawActive(false);
		m_text_backtitle2->SetDrawActive(false);

	}

	void ResultStage::OnCreate() {
		try {
			CreateViewLight();
			m_SelectChoices = 0;
			m_SelectQuantity = 3;
			m_StarQuantity = 3;
			CreateUI();
			App::GetApp()->GetScene<Scene>()->StopBGM();
			App::GetApp()->GetScene<Scene>()->PlayBGM(L"after_war.wav", 0.5f);
			
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
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
			m_text_next2->SetDrawActive(true);
			m_SelectArrowNumber1->SetDrawActive(true);

			m_text_stageselect->SetDrawActive(true);
			m_text_backtitle->SetDrawActive(true);


			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->PlaySE(L"decision.wav", 0.5f);
				auto a = App::GetApp()->GetScene<Scene>()->GetSelectNumber();
				App::GetApp()->GetScene<Scene>()->SetSelectNumber(a+1);
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
			}

			break;
		case 1:
			BoolSet();
			m_Select->SetDrawActive(true);
			m_text_stageselect2->SetDrawActive(true);
			m_SelectArrowNumber2->SetDrawActive(true);

			m_text_next->SetDrawActive(true);
			m_text_backtitle->SetDrawActive(true);


			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->PlaySE(L"decision.wav", 0.5f);
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::stageSelect);
			}

			break;
		case 2:
			BoolSet();
			m_End->SetDrawActive(true);
			m_text_backtitle2->SetDrawActive(true);
			m_SelectArrowNumber3->SetDrawActive(true);

			m_text_next->SetDrawActive(true);
			m_text_stageselect->SetDrawActive(true);


			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				App::GetApp()->GetScene<Scene>()->PlaySE(L"decision.wav", 0.5f);
				App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
			}
			break;

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
