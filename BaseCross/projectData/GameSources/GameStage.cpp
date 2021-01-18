/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 15.0f, -5.0f);
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

	void GameStage::CreateXmlObjects() {

		//親
		m_Parentbox = AddGameObject<ParentBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 1.0f, 0.0f)
			);
		SetSharedGameObject(L"ParentBox", m_Parentbox);
		m_Parentbox->AddTag(L"ParentBox");
		//ゴール
		//m_Target = GetSharedGameObject<ParentBox>(L"ParentBox");
		//m_Goal = AddGameObject<Goal>(
		//	Vec3(0.55f, 0.55f, 0.55f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(-1.98f, 1.0f, 3.2f),
		//	m_Target,
		//	Vec3(0, 0, 0)
		//	);
		//m_Goal->AddTag(L"Goal");

		m_group = CreateSharedObjectGroup(L"FixedBoxes");
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		auto CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map1");
		if (!CellmapNode) {
			throw BaseException(
				L"GameStage/CellMapが見つかりません",
				L"if (!CellmapNode)",
				L"GameStage::CreateEnemy()"
			);
		}
		
		
		auto Depth = m_XmlDocReader->GetSelectSingleNode(L"depth");
		auto Width = m_XmlDocReader->GetSelectSingleNode(L"width");

		
		for (int f = 0; f < 10; f++) {
			switch (f) {
			case 0:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map1");
				break;
			case 1:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map2");
				break;
			case 2:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map3");
				break;
			case 3:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map4");
				break;
			case 4:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map5");
				break;
			case 5:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map6");
				break;
			case 6:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map7");
				break;
			case 7:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map8");
				break;
			case 8:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map9");
				break;
			case 9:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map10");
				break;
			}
		
			wstring MapStr = XmlDocReader::GetText(CellmapNode);
			vector<wstring> LineVec;
			//最初に「改行」をデリミタとした文字列の配列にする
			Util::WStrToTokenVector(LineVec, MapStr, L'\n');

			
			//[,]を10個で区切る方法？

			for (size_t i = 0; i < 10; i++) {
				//トークン（カラム）の配列
				vector<wstring> Tokens;

				//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
				Util::WStrToTokenVector(Tokens, LineVec[i], L',');
				for (size_t j = 0; j < 10; j++) {
					//XとZの位置を計算
					float XPos = (float)((int)j - 5);
					float ZPos = (float)(5 - (int)i);
					if (Tokens[j] == L"1") {
						m_Target = GetSharedGameObject<ParentBox>(L"ParentBox");
						m_Target = AddGameObject<FixedBox>(
							Vec3(XPos*m_position, f*m_position, ZPos*m_position),
							m_Target,
							Vec3(0, 0, 0)
							);
						//Group = GetSharedObjectGroup(L"FixedBoxes");
						m_group->IntoGroup(m_fixedbox);
					}
					else if (Tokens[j] == L"2") {
						//スタート
						m_Target = GetSharedGameObject<ParentBox>(L"ParentBox");
						m_Target = AddGameObject<FixedBox>(
							//Vec3(XPos*0.25f, 0.5f, ZPos*0.25f),
							Vec3(XPos*m_position, f*m_position, ZPos*m_position),
							m_Target,
							Vec3(0, 0, 0)
							);
						//Group = GetSharedObjectGroup(L"FixedBoxes");
						m_group->IntoGroup(m_fixedbox);
						
						m_player = AddGameObject<Player>(
							Vec3(XPos*m_position, 2.0f, ZPos*m_position)
							//親子関係↓
							//,m_Target
						);
					}
					else if (Tokens[j] == L"3") {
						//ゴール
						m_Target = GetSharedGameObject<ParentBox>(L"ParentBox");
						m_Goal = AddGameObject<Goal>(
							//Vec3(XPos*0.25f, 0.5f, ZPos*0.25f),
							Vec3(XPos*m_position, f*m_position, ZPos*m_position),
							m_Target,
							Vec3(0, 0, 0)
							);
						//Group = GetSharedObjectGroup(L"FixedBoxes");
						m_group->IntoGroup(m_fixedbox);
					}
					else if (Tokens[j] == L"4") {
						//スイッチ
						m_Target = GetSharedGameObject<ParentBox>(L"ParentBox");
						m_Switch = AddGameObject<SwitchBox>(
							//Vec3(XPos*0.25f, 0.5f, ZPos*0.25f),
							Vec3(XPos*m_position, f*m_position, ZPos*m_position),
							m_Target,
							Vec3(0, 0, 0)
							);
						//Group = GetSharedObjectGroup(L"FixedBoxes");
						m_group->IntoGroup(m_fixedbox);

					}
					else if (Tokens[j] == L"5") {
						//スイッチで動くブロック
						m_Target = GetSharedGameObject<ParentBox>(L"ParentBox");
						m_Switch = AddGameObject<SwitchMoveBox>(
							//Vec3(XPos*0.25f, 0.5f, ZPos*0.25f),
							Vec3(XPos*m_position, f*m_position, ZPos*m_position),
							m_Target,
							Vec3(0, 0, 0)
							);
						//Group = GetSharedObjectGroup(L"FixedBoxes");
						m_group->IntoGroup(m_fixedbox);

					}

				}
			}
					//for (int z = 0; z < 10; z++) {
					//	//トークン（カラム）の配列
					//	vector<wstring> Tokens;
					//	//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
					//	Util::WStrToTokenVector(Tokens, LineVec[z], L',');

					//	for (int x = 0; x < 10; x++) {
					//		//float XPos = (float)((int)x - 10);
					//		//float ZPos = (float)(10 - (int)x);
					//		if (Tokens[x] == L"0") {
					//			AddGameObject<MoveBox>(
					//				Vec3(1.0f, 1.0f, 1.0f),
					//				Vec3(0.0f, 0.0f, 0.0f),
					//				Vec3(x, 0.0f, x)
					//				);
					//			
					//		}
							//else if (Tokens[x] == L"1") {
							//	AddGameObject<MoveBox>(
							//		Vec3(1.0f, 1.0f, 1.0f),
							//		Vec3(0.0f, 0.0f, 0.0f),
							//		Vec3(XPos, 0.5f, ZPos)
							//		);


							//}

							//else if (Tokens[x] == L"2") {
							//	AddGameObject<MoveBox>(
							//		Vec3(1.0f, 1.0f, 1.0f),
							//		Vec3(0.0f, 0.0f, 0.0f),
							//		Vec3(XPos, 0.5f, ZPos)
							//		);

							//}
				

			
		}
	}

	void GameStage::CreateUI() {
		//Number
		for (int i = 0; i < 3; i++) {	//ループ数で桁変更
			float n = static_cast<float>(i);
			m_numbers[i] = AddGameObject<Number_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(1500.0f * 0.5f - n * 64.0f - 64.0f, 900.0f * 0.5f, 0.0f),
				Vec3(1.5f, 1.5f, 1.5f),
				0,
				Col4(1.0f, 1.0f, 1.0f, 1.0f),
				m_number_UI,
				static_cast<int>((powf(10.0f, n))),
				static_cast<int>(m_number)
				);
			//m_numbers[i]->SetDrawActive(false);
		}

	}
	void GameStage::CreateBack() {
		//ゲームの方
		AddGameObject<Game_Back>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			-99,
			Col4(1.0f),
			m_back
			);
	}

	void GameStage::CreateCloud() {
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

				//AddGameObject<Clear>(
				//	Vec2(137.0f, 64.0f),
				//	Vec3(0.0f, 200.0f, 0.0f),
				//	Vec3(3.0f),
				//	10,
				//	Col4(1.0f),
				//	m_clear
				//);

	}
	void GameStage::CreateMask() {
		m_mask = AddGameObject<Mask_UI>(
			Vec2(1920.0f, 1080.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f),
			1,
			Col4(1.0f, 1.0f, 1.0f, 0.5f),
			m_mask_UI
			);
		m_text_joken1 = AddGameObject<UI_Text>(
			L"メイリオ",
			100.0f,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			Rect2D<float>(0.0f, 200.0f, 1820.0f, 500.0f),
			StringSprite::TextAlignment::m_Center,
			m_text_UI_joken1,
			5,
			false
			);		
		m_text_joken2 = AddGameObject<UI_Text>(
			L"メイリオ",
			100.0f,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			Rect2D<float>(0.0f, 400.0f, 1920.0f, 500.0f),
			StringSprite::TextAlignment::m_Center,
			m_text_UI_joken2,
			5,
			false
			);
		m_text_joken3 = AddGameObject<UI_Text>(
			L"メイリオ",
			100.0f,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			Rect2D<float>(160.0f, 600.0f, 1920.0f, 500.0f),
			StringSprite::TextAlignment::m_Center,
			m_text_UI_joken3,
			5,
			false
			);

		m_text = AddGameObject<UI_Text>(
			L"メイリオ",
			100.0f,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			Rect2D<float>(0.0f, 0.0f, 1920.0f, 500.0f),
			StringSprite::TextAlignment::m_Center,
			m_text_UI1,
			5,
			false
			);
		AddGameObject<UI_Text>(
			L"メイリオ",
			100.0f,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			Rect2D<float>(1300.0f, 0.0f, 1920.0f, 500.0f),
			StringSprite::TextAlignment::m_Center,
			m_text_UI2,
			0,
			false
			);

	}

	void GameStage::CreateEffect() {
		Aura::InitParams params; // オーラエフェクトに渡すパラメータをまとめた構造体（BaseCrossはAddGameObjectの際、引数が分かりづらいのでまとめると良い）
		//params.textureKey = L"aura.png";
		//params.sides = 30;
		//params.height = 1.0f;
		//params.topRadius = 1.5f;
		//params.bottomRadius = 1.0f;
		//params.topColor = Col4(1.0f, 0.0f, 1.0f, 0.0f);
		//params.bottomColor = Col4(1.0f, 0.0f, 1.0f, 1.0f);
		//params.uvOffsetSpeed = Vec2(0.1f, 0.0f);
		//params.textureLoops = 1.0f;

		auto goalpos = m_Goal->GetComponent<Transform>()->GetPosition();
		goalpos = Vec3(0.0f, 0.4f, 0.0f);
			// リスポーン地点的なエフェクト
		auto respawnArea = AddGameObject<Aura>(Aura::InitParams(L"line.png", 30, 1.5f, 0.5f, 0.5f, Col4(1.0f, 1.0f, 1.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f), 6.0f), m_Goal);
		respawnArea->GetComponent<Transform>()->SetPosition(goalpos);


	}

	void GameStage::OnCreate() {
		try {
			SetPhysicsActive(true);
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto a = App::GetApp()->GetScene<Scene>()->GetSelectNumber();
			//m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/Stage10.xml"));
			
			//XMLの読み込み
			switch (a) {
			case 0:
				m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/test10.xml"));
				break;
			case 1:
				m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/Stage2.xml"));
				break;
			case 2:
				m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/Stage3.xml"));
				break;
			case 3:
				m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/Stage4.xml"));
				break;

			}
			//ビューとライトの作成
			CreateViewLight();
			CreateXmlObjects();
			CreateMask();
			CreateBack();
			CreateCloud();
			CreateUI();
			CreateEffect();
			App::GetApp()->GetScene<Scene>()->StopBGM();
			App::GetApp()->GetScene<Scene>()->PlayBGM(L"hikousen.wav", 0.1f);
		}

		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {
			m_mask->SetDrawActive(false);
			m_text->SetDrawActive(false);
			m_text_joken1->SetDrawActive(false);
			m_text_joken2->SetDrawActive(false);
			m_text_joken3->SetDrawActive(false);
		}
	}

	void GameStage::OnUpdate2() {
		for (int i = 0; i < 3; i++) {
			m_numbers[i]->SetDrawActive(true);
		}
	}
}
//end basecross
