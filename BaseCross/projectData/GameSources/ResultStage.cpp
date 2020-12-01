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
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-1,
			Col4(1.0f),
			m_Result_image
			);

		//AddGameObject<Result_UI>(
		//	Vec2(190.0f, 180.0f),
		//	Vec3(19.0f, 107.0f, 0.0f),
		//	Vec3(x),
		//	0,
		//	Col4(1.0f),
		//	m_Result_StarOnly
		//	);
		AddGameObject<Result_UI>(
			Vec2(190.0f, 180.0f),
			Vec3(297.0f, 107.0f, 0.0f),
			Vec3(1.0f),
			0,
			Col4(1.0f),
			m_Result_StarOnly
			);
		AddGameObject<Result_UI>(
			Vec2(190.0f, 180.0f),
			Vec3(-259.0f, 107.0f, 0.0f),
			Vec3(1.0f),
			0,
			Col4(1.0f),
			m_Result_StarOnly
			);

		m_Start =
			AddGameObject<Title_UI>(
				Vec2(581.0f, 132.0f),
				Vec3(-600.0f, -400.0f, 0.0f),
				Vec3(1.0f),
				-1,
				Col4(1.0f),
				m_titleflame
				);
		m_Select =
			AddGameObject<Title_UI>(
				Vec2(581.0f, 132.0f),
				Vec3(0.0f, -400.0f, 0.0f),
				Vec3(1.0f),
				-1,
				Col4(1.0f),
				m_titleflame
				);
		//m_End =
		//	AddGameObject<Title_UI>(
		//		Vec2(581.0f, 132.0f),
		//		Vec3(600.0f, -400.0f, 0.0f),
		//		Vec3(1.0f),
		//		-1,
		//		Col4(1.0f),
		//		m_titleflame
		//		);
		AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(-600.0f, -420.0f, 0.0f),
			Vec3(0.8f),
			-2,
			Col4(1.0f),
			m_next
			);
		AddGameObject<Title_UI>(
			Vec2(581.0f, 132.0f),
			Vec3(10.0f, -420.0f, 0.0f),
			Vec3(0.8f),
			-2,
			Col4(1.0f),
			m_Selectlogo
			);
		//AddGameObject<Title_UI>(
		//	Vec2(581.0f, 132.0f),
		//	Vec3(620.0f, -420.0f, 0.0f),
		//	Vec3(0.8f),
		//	-2,
		//	Col4(1.0f),
		//	m_Endlogo
		//	);

		m_StartLogoObject =
			AddGameObject<Title_UI>(
				Vec2(581.0f, 132.0f),
				Vec3(-600.0f, -420.0f, 0.0f),
				Vec3(1.0f),
				0,
				Col4(1.0f),
				m_next
				);
		m_SelectLogoObject =
			AddGameObject<Title_UI>(
				Vec2(581.0f, 132.0f),
				Vec3(10.0f, -420.0f, 0.0f),
				Vec3(1.0f),
				0,
				Col4(1.0f),
				m_Selectlogo
				);
		//m_EndLogoObject =
		//	AddGameObject<Title_UI>(
		//		Vec2(581.0f, 132.0f),
		//		Vec3(620.0f, -420.0f, 0.0f),
		//		Vec3(1.0f),
		//		0,
		//		Col4(1.0f),
		//		m_Endlogo
		//		);

	}

	void ResultStage::OnCreate() {
		try {
			CreateViewLight();
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::stageSelect);
		}

		m_Star01=
			AddGameObject<Result_UI>(
			Vec2(190.0f, 180.0f),
			Vec3(19.0f, 107.0f, 0.0f),
			Vec3(x),
			0,
			Col4(1.0f),
			m_Result_StarOnly
			);

		if (x > 0) {
			x -= 0.01f;

		}
		//m_Star01->
	}

}
//end basecross
