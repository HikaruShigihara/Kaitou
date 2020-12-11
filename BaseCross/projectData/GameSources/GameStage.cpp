/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
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

	void GameStage::CreateXmlObjects() {

		//�e
		m_Parentbox = AddGameObject<ParentBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 1.0f, 0.0f)
			);
		SetSharedGameObject(L"ParentBox", m_Parentbox);
		m_Parentbox->AddTag(L"ParentBox");
		//�S�[��
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
				L"GameStage/CellMap��������܂���",
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
			//�ŏ��Ɂu���s�v���f���~�^�Ƃ���������̔z��ɂ���
			Util::WStrToTokenVector(LineVec, MapStr, L'\n');

			
			//[,]��10�ŋ�؂���@�H

			for (size_t i = 0; i < 10; i++) {
				//�g�[�N���i�J�����j�̔z��
				vector<wstring> Tokens;

				//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
				Util::WStrToTokenVector(Tokens, LineVec[i], L',');
				for (size_t j = 0; j < 10; j++) {
					//X��Z�̈ʒu���v�Z
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
						//�X�^�[�g
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
							//�e�q�֌W��
							//,m_Target
						);
													

					}
					else if (Tokens[j] == L"3") {
						//�S�[��
						m_Target = GetSharedGameObject<ParentBox>(L"ParentBox");
						m_Target = AddGameObject<Goal>(
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
					//	//�g�[�N���i�J�����j�̔z��
					//	vector<wstring> Tokens;
					//	//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
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
		for (int i = 0; i < 3; i++) {	//���[�v���Ō��ύX
			float n = static_cast<float>(i);
			m_numbers[i] = AddGameObject<Number_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(1300.0f * 0.5f - n * 64.0f - 64.0f, 1000.0f * 0.5f, 0.0f),
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
		//�Q�[���̕�
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
		m_text = AddGameObject<UI_Text>(
			L"���C���I",
			100.0f,
			Col4(1.0f, 1.0f, 1.0f, 1.0f),
			Rect2D<float>(0.0f, 0.0f, 1920.0f, 500.0f),
			StringSprite::TextAlignment::m_Center,
			m_text_UI,
			5,
			false
			);

	}

	void GameStage::OnCreate() {
		try {
			SetPhysicsActive(true);
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto a = App::GetApp()->GetScene<Scene>()->GetSelectNumber();
			//m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/Stage10.xml"));
			
			//XML�̓ǂݍ���
			switch (a) {
			case 0:
				m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/stage12.xml"));
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
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateXmlObjects();
			CreateMask();
			CreateBack();
			CreateCloud();
			CreateUI();
			
			App::GetApp()->GetScene<Scene>()->StopBGM();
			App::GetApp()->GetScene<Scene>()->PlayBGM(L"hikousen.wav", 0.3f);
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
		}
	}

	void GameStage::OnUpdate2() {
		for (int i = 0; i < 3; i++) {
			m_numbers[i]->SetDrawActive(true);
		}
	}
}
//end basecross
