/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Player::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_Scale);	//���a25�Z���`�̋���
		ptr->SetRotation(m_Rotation);
		ptr->SetPosition(m_Position);

		//�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(Vec3(1.0f, 2.0f, 1.0f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//PsSphereParam param(ptr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//auto psPtr = AddComponent<RigidbodySphere>(param);
		//psPtr->SetAutoTransform(false);
		//psPtr->SetDrawActive(true);

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//�e������i�V���h�E�}�b�v��`�悷��j
		//auto shadowPtr = AddComponent<Shadowmap>();
		////�e�̌`�i���b�V���j��ݒ�
		//shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		////�`��R���|�[�l���g�̐ݒ�
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		////�`�悷�郁�b�V����ݒ�
		//ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//ptrDraw->SetFogEnabled(true);
		////�`�悷��e�N�X�`����ݒ�
		//ptrDraw->SetTextureResource(L"Blue.png");
		//SetAlphaActive(true);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Player.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);


		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"Player.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//ptrDraw->AddAnimation(L"Default", 0, 20, true, 20.0f);
		//ptrDraw->ChangeCurrentAnimation(L"Default");


		//��������
		SetAlphaActive(true);


		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCamera�ł���
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(GetThis<GameObject>());
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
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		//auto angle = GetPlayerMoveVec();
		//auto Vec = GetPlayerMoveVec();
		//auto PtrPs = GetComponent<RigidbodySphere>();
		//auto Velo = PtrPs->GetLinearVelocity();
		//Velo.x = Vec.x * 5.0f;
		//Velo.z = Vec.z * 5.0f;
		//PtrPs->SetLinearVelocity(Velo);
		////��]�̌v�Z
		//if (angle.length() > 0.0f) {
		//	auto utilPtr = GetBehavior<UtilBehavior>();
		//	utilPtr->RotToHead(angle, 1.0f);
		//}
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetPlayerMoveVec();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * 6.0f;
			GetComponent<Transform>()->SetPosition(pos);
		}
		//��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
		//auto gamestage = dynamic_pointer_cast<GameStage>(GetStage());
		//gamestage->SetCount(1);
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Goal")) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::result);
		}
	}

	void Player::Respawn() {
		const float limitY = 10.0f;
		auto player = GetComponent<Transform>();
		auto pos = player->GetPosition();

		if (abs(pos.y) > limitY) {
			player->SetPosition(m_Position);
			auto gamestage = dynamic_pointer_cast<GameStage>(GetStage());
			gamestage->resetCount();

		}
	}

	void Player::StageRotate() {
		//�X�e�[�W��]
		//auto stage = 

	}

	void Player::OnUpdate() {
		PlayerMove();
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		//auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		//ptrDraw->UpdateAnimation(elapsedTime);

		Respawn();
	}

	void Player::OnUpdate2() {
		//auto PtrPs = GetComponent<RigidbodySphere>();
		//auto Ptr = GetComponent<Transform>();
		//Ptr->SetPosition(PtrPs->GetPosition());

		DrawStrings();

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
}
//end basecross

