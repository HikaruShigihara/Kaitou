/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Player::OnCreate() {
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_Scale);	//直径25センチの球体
		ptr->SetRotation(m_Rotation);
		ptr->SetPosition(m_Position);

		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();

		//各パフォーマンスを得る
		//GetStage()->SetCollisionPerformanceActive(true);
		//GetStage()->SetUpdatePerformanceActive(true);
		//GetStage()->SetDrawPerformanceActive(true);

		//重力をつける
		auto ptrGra = AddComponent<Gravity>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//WorldMatrixをもとにRigidbodySphereのパラメータを作成
		PsSphereParam param(ptr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//RigidbodySphereコンポーネントを追加
		auto psPtr = AddComponent<RigidbodySphere>(param);
		//自動的にTransformを設定するフラグは無し
		psPtr->SetAutoTransform(false);
		psPtr->SetDrawActive(true);

		//文字列をつける
		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetFogEnabled(true);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"Blue.png");
		SetAlphaActive(true);
	}

	Vec3 Player::GetPlayerMoveVec() const {
		Vec3 angle(0, 0, 0);
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//if (KeyState.m_bPushKeyTbl['W']) {
		//	//前
		//	fThumbLY = 1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['S']) {
		//	//後ろ
		//	fThumbLY = -1.0f;
		//}
		//if (KeyState.m_bPushKeyTbl['D']) {
		//	//右
		//	fThumbLX = 1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['A']) {
		//	//左
		//	fThumbLX = -1.0f;
		//}

		if (KeyState.m_bPressedKeyTbl['W']) {
			//前
			fThumbLY = 2.5f;
		}
		else if (KeyState.m_bPressedKeyTbl['S']) {
			//後ろ
			fThumbLY = -2.5f;
		}
		if (KeyState.m_bPressedKeyTbl['D']) {
			//右
			fThumbLX = 2.5f;
		}
		else if (KeyState.m_bPressedKeyTbl['A']) {
			//左
			fThumbLX = -2.5f;
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
		}
		return angle;
	}

	void Player::Respawn() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		if (pos.y <= -1.0f) {
			ptrTrans->SetPosition(m_Position);

		}

	}

	void Player::PlayerMove() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetPlayerMoveVec();
		auto Vec = GetPlayerMoveVec();
		auto PtrPs = GetComponent<RigidbodySphere>();
		auto Velo = PtrPs->GetLinearVelocity();
		Velo.x = Vec.x * 5.0f;
		Velo.z = Vec.z * 5.0f;
		PtrPs->SetLinearVelocity(Velo);
		//回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}

	}

	void Player::OnUpdate() {
		auto pos = GetComponent<Transform>()->GetPosition();
		Respawn();
		PlayerMove();
	}

	void Player::OnUpdate2() {
		//auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//auto trans = GetComponent<Transform>();
		//auto pos = trans->GetPosition();

		//if (KeyState.m_bPushKeyTbl['W']) {
		//	trans->SetPosition(Vec3(0.0f, 0.0f, 2.0f));
		//}

		auto PtrPs = GetComponent<RigidbodySphere>();
		auto Ptr = GetComponent<Transform>();
		Ptr->SetPosition(PtrPs->GetPosition());

	}
}
//end basecross

