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

	//--------------------------------------------------------------------------------------
	//	class MoveBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	//MoveBox::MoveBox(const shared_ptr<Stage>& StagePtr,
	//	const Vec3& Scale,
	//	const Vec3& Rotation,
	//	const Vec3& Position
	//) :
	//	GameObject(StagePtr),
	//	m_Scale(Scale),
	//	m_Rotation(Rotation),
	//	m_Position(Position)
	//{
	//}
	//MoveBox::~MoveBox() {}

	//������
	//void MoveBox::OnCreate() {
	//	auto ptrTransform = GetComponent<Transform>();
	//	ptrTransform->SetScale(m_Scale);
	//	ptrTransform->SetRotation(m_Rotation);
	//	ptrTransform->SetPosition(m_Position);
	//	//OBB�Փ�j�����t����
	//	auto ptrColl = AddComponent<CollisionObb>();
	//	ptrColl->SetSleepActive(true);
	//	//�e������
	//	auto shadowPtr = AddComponent<Shadowmap>();
	//	shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
	//	//�`�揈��
	//	auto ptrDraw = AddComponent<BcPNTStaticDraw>();
	//	ptrDraw->SetFogEnabled(true);
	//	ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
	//	ptrDraw->SetOwnShadowActive(true);
	//}

	void GameStage::CreateFixedBox() {
		auto goal = AddGameObject<Goal>(
			Vec3(0.45f, 0.45f, 0.45f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.2f, 2.2f)
			);
		
		//AddGameObject<ParentBox>(
		//	Vec3(0.25f, 0.25f, 0.25f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 1.0f, 0.0f)
		//	);

	}
	void GameStage::CreateXmlObjects() {
		//�e
		//m_Parentbox = AddGameObject<ParentBox>(
		//	Vec3(0.25f, 0.25f, 0.25f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 1.0f, 0.0f)
		//	);
		//SetSharedGameObject(L"ParentBox", m_Parentbox);
		//m_Parentbox->AddTag(L"ParentBox");


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

		
		for (int f = 0; f < 2; f++) {
			switch (f) {
			case 0:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map1");
				break;
			case 1:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map2");
				break;
			}
		
			wstring MapStr = XmlDocReader::GetText(CellmapNode);
			vector<wstring> LineVec;
			//�ŏ��Ɂu���s�v���f���~�^�Ƃ���������̔z��ɂ���
			Util::WStrToTokenVector(LineVec, MapStr, L'\n');

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
						//shared_ptr<GameObject> ptrTarget = GetSharedGameObject<FixedBox>(L"Player");
						AddGameObject<FixedBox>(
						Vec3(0.1f, 0.1f, 0.1f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(XPos*0.43f, f*0.43f, ZPos*0.43f)
							//ptrTarget,
							//Vec3(0,0,0)
							);
					//Group = GetSharedObjectGroup(L"FixedBoxes");
					m_group->IntoGroup(m_fixedbox);
					}
					else if (Tokens[j] == L"2") {
						//shared_ptr<GameObject> ptrTarget = GetSharedGameObject<FixedBox>(L"Player");
						AddGameObject<FixedBox>(
						Vec3(0.1f, 0.1f, 0.1f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(XPos*0.25f, 0.5f, ZPos*0.25f)
						//ptrTarget,
						//Vec3(0,0,0)
						);
					//Group = GetSharedObjectGroup(L"FixedBoxes");
					m_group->IntoGroup(m_fixedbox);

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
	}

	void GameStage::CreateUI() {
		//Number
		for (int i = 0; i < 3; i++) {	//���[�v���Ō��ύX
			float n = static_cast<float>(i);
			m_numbers[i] = AddGameObject<Number_UI>(
				Vec2(500.0f, 100.0f),
				Vec3(600.0f * 0.5f - n * 64.0f - 64.0f, 460.0f * 0.5f, 0.0f),
				Vec3(1.5f, 1.5f, 1.5f),
				1,
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

	}

	void GameStage::CreatePlayer() {
		AddGameObject<Player>(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0, 2, 0)
			);
	}

	void GameStage::MoveStage() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//auto stageGroup = GetSharedObjectGroup(L"FixedBoxes");
		//std::vector<std::shared_ptr<FixedBox>> fixedboxes;
		//for (auto& v : stageGroup->GetGroupVector()) {
		//	auto shptr = v.lock();
		//	if (shptr) {
		//		auto fixedBox = dynamic_pointer_cast<FixedBox>(shptr);
		//		if (fixedBox) {
		//			fixedboxes.push_back(fixedBox);
		//		}
		//	}
		//}
		////FixedBoxes���g���������̏���
		//auto i = fixedboxes.size();
		//auto stageTrans = fixedboxes[i]->GetComponent<Transform>();
		//if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {


		//}
		//auto gameObjects = GetGameObjectVec();
		//auto GroupPtr = dynamic_pointer_cast<GameObject>(m_group);
		//auto PtrAction = m_fixedbox->AddComponent<Action>();
		//PtrAction->AddRotateBy(1.0f, Vec3(0, 0, 90));
		//PtrAction->SetLooped(false);

		//if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {

		//	PtrAction->Run();

		//}
		//if (KeyState.m_bPushKeyTbl['W']) {
		//	PtrAction->Run();

		//}


	}

	void GameStage::OnCreate() {
		try {
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//XML�̓ǂݍ���
			m_XmlDocReader.reset(new XmlDocReader(DataDir + L"xml/test.xml"));
			CreateFixedBox();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateXmlObjects();
			CreatePlayer();
			CreateBack();
			CreateCloud();
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		MoveStage();
		
	}

	void GameStage::OnUpdate2() {
		for (int i = 0; i < 3; i++) {
			m_numbers[i]->SetDrawActive(true);
		}
	}
}
//end basecross
