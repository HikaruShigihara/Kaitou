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
		auto PtrCamera = ObjectFactory::Create<Camera>();
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
	MoveBox::MoveBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	MoveBox::~MoveBox() {}

	//������
	void MoveBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetSleepActive(true);
		//�e������
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//�`�揈��
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
	}

	void GameStage::CreateFixedBox() {
		AddGameObject<MoveBox>(
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
			);

	}
	void GameStage::CreateXmlObjects() {
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
			case 1:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map1");

			case 2:
				CellmapNode = m_XmlDocReader->GetSelectSingleNode(L"field/maps/map2");
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
					AddGameObject<MoveBox>(
						Vec3(0.25f, 0.25f, 0.25f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(XPos*0.25, f*0.25f, ZPos*0.25));

					}
					else if (Tokens[j] == L"2") {
					AddGameObject<MoveBox>(
						Vec3(0.25f, 0.25f, 0.25f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(XPos*0.25, 0.5f, ZPos*0.25));
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
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
