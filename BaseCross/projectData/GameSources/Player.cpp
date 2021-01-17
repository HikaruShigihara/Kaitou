/*!
@file Player.cpp
@brief プレイヤーなど実体
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Player::OnCreate() {
		//初期位置などの設定
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(m_Scale);	//直径25センチの球体
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//衝突判定を付ける
		auto ptrColl = AddComponent<CollisionCapsule>();
		//ptrColl->SetMakedHeight(3.0f);
		//ptrColl->SetMakedSize(Vec3(2.0f, 5.0f, 2.0f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//重力をつける
		auto ptrGra = AddComponent<Gravity>();
		AddTag(L"Player");

		//GetStage()->SetCollisionPerformanceActive(true);
		//GetStage()->SetUpdatePerformanceActive(true);
		//GetStage()->SetDrawPerformanceActive(true);
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//auto psPtr = AddComponent<RigidbodyBox>(param);
		//psPtr->SetAutoTransform(false);
		//psPtr->SetDrawActive(true);

		//文字列をつける
		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.3f, 0.2f, 0.3f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.8f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"player_Walk_Motion.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);


		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//描画するメッシュを設定
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

		//透明処理
		SetAlphaActive(true);


		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetEye(Vec3(0.0f, 7.0f, 0.0f));
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
	}

	Vec3 Player::GetPlayerMoveVec() const {
		Vec3 angle(0, 0, 0);
		//コントローラの取得
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
			//前
			fThumbLY = m_WalkSpeed;
		}
		else if (KeyState.m_bPressedKeyTbl['S']) {
			//後ろ
			fThumbLY = -m_WalkSpeed;
		}
		if (KeyState.m_bPressedKeyTbl['D']) {
			//右
			fThumbLX = m_WalkSpeed;
		}
		else if (KeyState.m_bPressedKeyTbl['A']) {
			//左
			fThumbLX = -m_WalkSpeed;
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
			//前
			fThumbLY = m_WalkSpeed;
		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
			//後ろ
			fThumbLY = -m_WalkSpeed;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			//右
			fThumbLX = m_WalkSpeed;
		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			//左
			fThumbLX = -m_WalkSpeed;
		}


		auto ptrTransform = GetComponent<Transform>();
		if (fThumbLX != 0 || fThumbLY != 0) {
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			angle.y = 0.0f;

			//カウント追加
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

		//回転の計算
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
			case 0://Bボタン
				PtrDraw->ChangeCurrentAnimation(L"Fall");
				break;
			case 1://Xボタン
				PtrDraw->ChangeCurrentAnimation(L"Fall");

				break;
			case 2://Aボタン
				PtrDraw->ChangeCurrentAnimation(L"Fall");

				break;
			case 3://Yボタン
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

