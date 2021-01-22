#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//初期化
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(Vec3(0.0f,0.0f,0.0f));
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);

		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetMakedSize(Vec3(2.0f, 2.5f, 2.5f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//ptrColl->SetDrawActive(true);
		ptrColl->SetFixed(true);


		//タグをつける
		AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");


		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.231f, 0.231f, 0.231f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Grass_2.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"Grass_2.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDrawActive(true);


		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			ptrTransform->SetParent(ptrParent);
		}

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//PsBoxParam param(ptrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);

	}
	void Goal::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(Vec3(0.65f, 0.65f, 0.65f));
		ptrTransform->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();

		ptrColl->SetFixed(false);

		//タグをつける
		AddTag(L"Goal");
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"red.png");


		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.231f, 0.231f, 0.231f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Goal_Spot_2.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"Goal_Spot_2.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDrawActive(true);

		ptrDraw->AddAnimation(L"Close", 0, 1, true, 20.0f);
		ptrDraw->AddAnimation(L"Open", 0, 20, false, 20.0f);

		ptrDraw->ChangeCurrentAnimation(L"Close");


		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			ptrTransform->SetParent(ptrParent);
		}
		
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//PsBoxParam param(ptrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);

	}
	void Goal::SeekParentGoal() {
		auto ptrTrans = GetComponent<Transform>();
		//auto pos = ptrTrans->GetPosition();
		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			auto matParent = ptrParent->GetComponent<Transform>()->GetWorldMatrix();
			matParent.scaleIdentity();
			Mat4x4 mat;
			mat.affineTransformation(
				Vec3(1.0),
				Vec3(0.0),
				Vec3(0.0),
				m_VecToParent
			);
			mat *= matParent;

			//auto posTarget = mat.transInMatrix();
			//auto v = Lerp::CalculateLerp(pos, posTarget, 0.0f, 1.0f, 0.2f, Lerp::rate::Linear);
			//ptrTrans->SetPosition(v);
			//ptrTrans->SetQuaternion(mat.quatInMatrix());
		}

	}
	void Goal::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
			ptrDraw->ChangeCurrentAnimation(L"Open");

		}
	}

	void Goal::OnUpdate() {
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

		SeekParentGoal();
	}

	void FixedBox::SeekParent() {
		auto ptrTrans = GetComponent<Transform>();
		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			auto matParent = ptrParent->GetComponent<Transform>()->GetWorldMatrix();
			matParent.scaleIdentity();
			Mat4x4 mat;
			mat.affineTransformation(
				Vec3(1.0),
				Vec3(0.0),
				Vec3(0.0),
				m_VecToParent
			);
			mat *= matParent;

			//ptrTrans->SetQuaternion(mat.quatInMatrix());

		}
	}

	void FixedBox::OnUpdate() {
		SeekParent();
	}


	void SwitchBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(Vec3(0.65f, 0.65f, 0.65f));
		ptrTransform->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		
		ptrColl->SetFixed(false);
		

		//GetStage()->SetCollisionPerformanceActive(true);
		//GetStage()->SetUpdatePerformanceActive(true);
		//GetStage()->SetDrawPerformanceActive(true);

		//タグをつける
		AddTag(L"Switch");

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.231f, 0.231f, 0.231f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Switch.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"Switch.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDrawActive(true);

		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			ptrTransform->SetParent(ptrParent);
		}

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
	}

	void SwitchBox::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto trans = GetComponent<Transform>();
		//auto a = shared_ptr<SwitchMoveBox>();
		if (Other->FindTag(L"Player")) {
			auto stage = dynamic_pointer_cast<GameStage>(GetStage());
			auto gameobject = stage->GetGameObjectVec();
			for (auto obj : gameobject) {
				auto movebox = dynamic_pointer_cast<SwitchMoveBox>(obj);
				if (movebox) {
					movebox->MoveBoxCheck(1);
				}

			}
		}
		//a->MoveBoxCheck(1);


	}

	void ParentBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"ParentBox");
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPCTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		
		ptrDraw->SetDrawActive(false);


		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
	}

	void ParentBox::MoveBox() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
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
			Quat spanQtZp(Vec3(0, 0, 1.0), m_RotSpan);
			Quat spanQtZm(Vec3(0, 0, -1.0), m_RotSpan);
			Quat spanQtXp(Vec3(1.0, 0, 0), m_RotSpan);
			Quat spanQtXm(Vec3(-1.0, 0, 0), m_RotSpan);

			switch (m_Key)
			{
			case 0://Bボタン
				qt = ptrTrans->GetQuaternion();
				qt *= spanQtZm;
				ptrTrans->SetQuaternion(qt);
				m_TotalRot += m_RotSpan;
				if (m_TotalRot > (XM_PI / 2.0f)) {

					m_TotalRot = 0.0f;
					m_RotSpan = m_RotSpan;
					m_Key = 99;

				}
				break;
			case 1://Xボタン
				qt = ptrTrans->GetQuaternion();
				qt *= spanQtZp;
				ptrTrans->SetQuaternion(qt);
				m_TotalRot += m_RotSpan;
				if (m_TotalRot > (XM_PI / 2.0f)) {
					m_TotalRot = 0.0f;
					m_RotSpan = m_RotSpan;
					m_Key = 99;
				}
				break;
			case 2://Aボタン
				qt = ptrTrans->GetQuaternion();
				qt *= spanQtXm;
				ptrTrans->SetQuaternion(qt);
				m_TotalRot += m_RotSpan;
				if (m_TotalRot > (XM_PI / 2.0f)) {
					m_TotalRot = 0.0f;
					m_RotSpan = m_RotSpan;
					m_Key = 99;
				}
				break;
			case 3://Yボタン
				qt = ptrTrans->GetQuaternion();
				qt *= spanQtXp;
				ptrTrans->SetQuaternion(qt);

				m_TotalRot += m_RotSpan;
				if (m_TotalRot > (XM_PI / 2.0f)) {
					m_TotalRot = 0.0f;
					m_RotSpan = m_RotSpan;
					m_Key = 99;
				}
				break;
			}
		}
	}

	void ParentBox::OnUpdate() {
		MoveBox();
	}

	//void ParentBox::DrawStrings() {
	//	auto ptrTrans = GetComponent<Transform>();
	//	auto quat = GetComponent<Transform>()->GetQuaternion();
	//	auto rot = quat.z * ( 0.2f/ XM_2PI );
	//	auto Rot = GetComponent<Transform>()->GetRotation();

	//	wstring RotationStr(L"Rotation:\t");
	//	//RotationStr += L"X=" + Util::FloatToWStr(rot.x, 6, Util::FloatModify::Fixed) + L",\t";
	//	//RotationStr += L"Y=" + Util::FloatToWStr(rot.y, 6, Util::FloatModify::Fixed) + L",\t";
	//	RotationStr += L"Z=" + Util::FloatToWStr(Rot.z, 6, Util::FloatModify::Fixed) + L"\n";

	//	wstring str = RotationStr;

	//	auto PtrString = GetComponent<StringSprite>();
	//	PtrString->SetText(str);

	//}

	//void ParentBox::OnUpdate2() {
	//	DrawStrings();
	//}


	void SwitchMoveBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);

		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetMakedSize(Vec3(2.0f, 2.5f, 2.5f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//ptrColl->SetDrawActive(true);
		ptrColl->SetFixed(true);


		//タグをつける
		AddTag(L"SwitchMoveBox");
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");


		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.231f, 0.231f, 0.231f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Stone_Block_2.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"Stone_Block_2.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDrawActive(true);
		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			ptrTransform->SetParent(ptrParent);
		}



		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//PsBoxParam param(ptrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);

		

	}
	void SwitchMoveBox::OnUpdate() {
		if (m_a == 1) {
			auto Trans = GetComponent<Transform>();
			auto pos = Trans->GetPosition();
			totalmove += movevalue;
			if (totalmove <= 0.65f) {
				Trans->SetPosition(pos.x - movevalue , pos.y, pos.z);
			}
		}

	}
	int SwitchMoveBox::MoveBoxCheck(int a)
	{
		m_a = a;
		return 0;
	}

	void GravityBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);

		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetMakedSize(Vec3(2.0f, 2.5f, 2.5f));
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//ptrColl->SetDrawActive(true);
		//CollisionSphere衝突判定を付ける
		//重力をつける
		auto PtrGra = AddComponent<Gravity>();

		//タグをつける
		AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");


		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.231f, 0.231f, 0.231f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Grass_2.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"Grass_2.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDrawActive(true);


		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			ptrTransform->SetParent(ptrParent);
		}

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//PsBoxParam param(ptrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);
	}
	void GravityBox::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			if (count == 0) {
				auto PtrAction = AddComponent<Action>();
				auto a = App::GetApp()->GetScene<Scene>()->GetAngle();
				auto Pos = GetComponent<Transform>()->GetPosition();
				float elapsedTime = App::GetApp()->GetElapsedTime();
				Pos += Vec3(a.x * 0.098, a.y, a.z*0.098);
				PtrAction->AddMoveTo(1.0f,Pos);
				PtrAction->Run();
				count = 1;
			}
		}
	}


}