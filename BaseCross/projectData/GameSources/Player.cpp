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

		//衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(Vec3(1.0f, 2.0f, 1.0f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		//重力をつける
		auto ptrGra = AddComponent<Gravity>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//PsSphereParam param(ptr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//auto psPtr = AddComponent<RigidbodySphere>(param);
		//psPtr->SetAutoTransform(false);
		//psPtr->SetDrawActive(true);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		////描画コンポーネントの設定
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		////描画するメッシュを設定
		//ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//ptrDraw->SetFogEnabled(true);
		////描画するテクスチャを設定
		//ptrDraw->SetTextureResource(L"Blue.png");
		//SetAlphaActive(true);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Player.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);


		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Player.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//ptrDraw->AddAnimation(L"Default", 0, 20, true, 20.0f);
		//ptrDraw->ChangeCurrentAnimation(L"Default");


		//透明処理
		SetAlphaActive(true);


		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(GetThis<GameObject>());
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
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		//auto angle = GetPlayerMoveVec();
		//auto Vec = GetPlayerMoveVec();
		//auto PtrPs = GetComponent<RigidbodySphere>();
		//auto Velo = PtrPs->GetLinearVelocity();
		//Velo.x = Vec.x * 5.0f;
		//Velo.z = Vec.z * 5.0f;
		//PtrPs->SetLinearVelocity(Velo);
		////回転の計算
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
		//回転の計算
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
		//ステージ回転
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

