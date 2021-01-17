/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Player::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(m_Scale);	//���a25�Z���`�̋���
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//�Փ˔����t����
		auto ptrColl = AddComponent<CollisionCapsule>();
		//ptrColl->SetMakedHeight(3.0f);
		//ptrColl->SetMakedSize(Vec3(2.0f, 5.0f, 2.0f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();
		AddTag(L"Player");

		//GetStage()->SetCollisionPerformanceActive(true);
		//GetStage()->SetUpdatePerformanceActive(true);
		//GetStage()->SetDrawPerformanceActive(true);
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//auto psPtr = AddComponent<RigidbodyBox>(param);
		//psPtr->SetAutoTransform(false);
		//psPtr->SetDrawActive(true);

		//�����������
		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.3f, 0.2f, 0.3f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.8f, 0.0f)
		);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"player_Walk_Motion.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"player_Walk_Motion.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDrawActive(true);

		ptrDraw->AddAnimation(L"Stop", 0, 20, true, 20.0f);
		ptrDraw->AddAnimation(L"Walk", 20, 20, false, 20.0f);
		ptrDraw->AddAnimation(L"Fall", 38, 40, false, 20.0f);
		
		ptrDraw->ChangeCurrentAnimation(L"Stop");

		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			ptrTrans->SetParent(NULL);
			
		}

		//��������
		SetAlphaActive(true);


		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCamera�ł���
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetEye(Vec3(0.0f, 7.0f, 0.0f));
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
	}

	Vec3 Player::GetPlayerMoveVec() const {
		Vec3 angle(0, 0, 0);
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			//fThumbLY = cntlVec[0].fThumbLY;
			//fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl['W']) {
			//�O
			fThumbLY = m_WalkSpeed;
		}
		else if (KeyState.m_bPressedKeyTbl['S']) {
			//���
			fThumbLY = -m_WalkSpeed;
		}
		if (KeyState.m_bPressedKeyTbl['D']) {
			//�E
			fThumbLX = m_WalkSpeed;
		}
		else if (KeyState.m_bPressedKeyTbl['A']) {
			//��
			fThumbLX = -m_WalkSpeed;
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
			//�O
			fThumbLY = m_WalkSpeed;
		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
			//���
			fThumbLY = -m_WalkSpeed;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			//�E
			fThumbLX = m_WalkSpeed;
		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			//��
			fThumbLX = -m_WalkSpeed;
		}


		auto ptrTransform = GetComponent<Transform>();
		if (fThumbLX != 0 || fThumbLY != 0) {
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s������������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			//�g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			//�p�x����x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
			angle *= moveSize;
			angle.y = 0.0f;

			//�J�E���g�ǉ�
			auto gamestage = dynamic_pointer_cast<GameStage>(GetStage());
			gamestage->SetCount(1);

		}
		return angle;
	}

	void Player::PlayerMove() {

		auto PtrAction = AddComponent<Action>();
		auto PtrDraw = GetComponent<BcPNTBoneModelDraw>();

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetPlayerMoveVec();
		if (PtrAction->IsArrived()) {
				PtrAction->AllActionClear();
		}

		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			//auto startpos = pos;
			pos += angle * elapsedTime * 6.0f;

			//Easing<Vec3> easing;
			//pos = easing.EaseInOut(EasingType::Exponential, pos, startpos, 0.0f, 10.0f);
			//GetComponent<Transform>()->SetPosition(pos);
			//auto ptrTrans = GetComponent<Transform>();
			auto PtrDraw = GetComponent<BcPNTBoneModelDraw>();
			PtrDraw->ChangeCurrentAnimation(L"Walk");

			//Animation(Anime::walk);
			PtrAction->AddMoveTo(0.5f, pos);
			PtrAction->SetLooped(false);
			PtrAction->Run();

			PtrAction->ReStart();

		}

		//��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}	
		//auto PtrAction = AddComponent<Action>();


	}
	void Player::Control() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PtrDraw = GetComponent<BcPNTBoneModelDraw>();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {
			m_start = true;
		}
		if (m_start) {
			auto ptrTrans = GetComponent<Transform>();

			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_Key = 0;
			}
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
				m_Key = 1;
			}
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				m_Key = 2;
			}
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
				m_Key = 3;
			}

			switch (m_Key)
			{
			case 0://B�{�^��
				PtrDraw->ChangeCurrentAnimation(L"Fall");
				break;
			case 1://X�{�^��
				PtrDraw->ChangeCurrentAnimation(L"Fall");

				break;
			case 2://A�{�^��
				PtrDraw->ChangeCurrentAnimation(L"Fall");

				break;
			case 3://Y�{�^��
				PtrDraw->ChangeCurrentAnimation(L"Fall");

				break;
			}
		}

	}
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		//auto elap = App::GetApp()->GetElapsedTime();
		//time += elap;
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (Other->FindTag(L"Goal")) {
			if (!m_clearflag) {
				auto clear = GetStage()->AddGameObject<Clear>(
					Vec2(137.0f, 64.0f),
					Vec3(0.0f, 200.0f, 0.0f),
					Vec3(3.0f),
					10,
					Col4(1.0f),
					m_clear
					);
				m_clearflag = true;
			}
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {

			}
			StarResult();
			//auto stage = App::GetApp()->GetScene<GameStage>();
			//stage->StopBGM();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);

			//if (time > 1.0f) {
			//}
		}
	}

	void Player::Respawn() {
		const float limitY = 10.0f;
		auto player = GetComponent<Transform>();
		auto pos = player->GetPosition();
		
		if (abs(pos.y) > limitY) {
			//player->SetPosition(m_Position);
			//auto gamestage = dynamic_pointer_cast<GameStage>(GetStage());
			//gamestage->resetCount();
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);

		}
	}

	void Player::OnUpdate() {
		auto cnlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cnlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {
			m_start = true;
		}
		if (m_start) {
			PlayerMove();

		}
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);		
		//auto grav = GetComponent<Gravity>();
		auto ptrTrans = GetComponent<Transform>();
		if ((cnlVec[0].wPressedButtons & XINPUT_GAMEPAD_X)||
			(cnlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y)||
			(cnlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)|| 
			(cnlVec[0].wPressedButtons & XINPUT_GAMEPAD_B))
		{
			ptrDraw->ChangeCurrentAnimation(L"Fall");

		}
		//auto ptrParent = m_Parent.lock();
		//if (cnlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
		//	a = 0;
		//	grav->SetUpdateActive(false);
		//}

		//switch (a) {
		//case 0:
		//	
		//	if (ptrParent) {
		//		ptrTrans->SetParent(ptrParent);
		//	}

		//	break;
		//}
		Respawn();
		//Control();
	}

	void Player::OnUpdate2() {
		//auto PtrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//Ptr->SetPosition(PtrPs->GetPosition());
		//auto grav = GetComponent<Gravity>();
		//grav->SetUpdateActive(true);
		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			ptrTrans->SetParent(NULL);

		}
		//DrawStrings();

	}
	void Player::DrawStrings() {
		auto Pos = GetComponent<Transform>()->GetPosition();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring str = PositionStr;

		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);

	}


	void Player::StarResult() {
		auto gamestage = dynamic_pointer_cast<GameStage>(GetStage());
		auto a = gamestage->GetCount();
		auto SelectNumber=App::GetApp()->GetScene<Scene>()->GetSelectNumber();
	
		if (a<m_StarQuantityLow[SelectNumber]) {
			App::GetApp()->GetScene<Scene>()->SetStageStar(SelectNumber, 3);
		}
		if (m_StarQuantityLow[SelectNumber] < a&&a < m_StarQuantityHigh[SelectNumber]) {
			App::GetApp()->GetScene<Scene>()->SetStageStar(SelectNumber, 2);

		}
		if (m_StarQuantityHigh[SelectNumber] < a) {
			App::GetApp()->GetScene<Scene>()->SetStageStar(SelectNumber, 1);

		}


	}
}
//end basecross

