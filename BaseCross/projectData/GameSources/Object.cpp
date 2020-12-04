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
		ptrShadow->SetMeshResource(L"Grass.bmf");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"Grass.bmf");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDrawActive(true);


		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			//auto posTarget = ptrParent->GetComponent<Transform>()->GetPosition();
			//posTarget += m_VecToParent;
			//ptrTransform->SetPosition(posTarget);
			auto posTarget = ptrParent->GetComponent<Transform>()->GetRotation();
			posTarget += m_VecToParent;
			ptrTransform->SetRotation(posTarget);
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

		ptrColl->SetFixed(true);


		//タグをつける
		AddTag(L"Goal");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"red.png");

		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			//auto posTarget = ptrParent->GetComponent<Transform>()->GetPosition();
			//posTarget += m_VecToParent;
			//ptrTransform->SetPosition(posTarget);
			auto posTarget = ptrParent->GetComponent<Transform>()->GetRotation();
			posTarget += m_VecToParent;
			ptrTransform->SetRotation(posTarget);
			ptrTransform->SetParent(ptrParent);

		}
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//PsBoxParam param(ptrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);

	}

	void FixedBox::SeekParent() {
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

	void FixedBox::OnUpdate() {
		SeekParent();
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
	void Goal::OnUpdate() {
		SeekParentGoal();
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

		ptrDraw->SetDrawActive(true);

		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			auto posTarget = ptrParent->GetComponent<Transform>()->GetPosition();
			posTarget += m_VecToParent;
			ptrTransform->SetPosition(posTarget);
			//auto posTarget = ptrParent->GetComponent<Transform>()->GetRotation();
			//posTarget += m_VecToParent;
			//ptrTransform->SetRotation(posTarget);
			ptrTransform->SetParent(ptrParent);

		}

		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
	}

	void ParentBox::MoveBox() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto elap = App::GetApp()->GetElapsedTime();
		m_time += elap;
		
		auto ptrTrans = GetComponent<Transform>();
		auto quat = ptrTrans->GetQuaternion();
		auto rot = ptrTrans->GetRotation();
		auto angleX = quat.x * (180.0f / XM_PI);
		auto angleZ = quat.z * (180.0f / XM_PI) * 3;

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			m_Key = 0;
			m_Keycount++;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
			m_Key = 1;
			m_Keycount++;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			m_Key = 2;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
			m_Key = 3;
		}

		switch (m_Key)
		{
		case 0://B
			if (m_Keycount == 1) {
				if (angleZ < 120.1f) {
					
					quat.z += m_movevalue * elap;
					ptrTrans->SetQuaternion(quat);
				}
			}
			else if (m_Keycount == 2) {
				if (angleZ < 172.0f) {
					quat.z += m_movevalue * elap;
					ptrTrans->SetQuaternion(quat);
					
				}
				else {
					rot.z = 1.0f;
					ptrTrans->SetQuaternion(quat);
				}
			}
			else if (m_Keycount == 3) {

				//if (angleZ == 60.0f) {
				//	quat.normalize();
				//	quat.z += m_movevalue * elap;
				//	ptrTrans->SetQuaternion(quat);
				//}
				
			}
			break;
		case 1://X
			if (m_Keycount == 1) {
				if (angleZ > -40.0f) {
					quat.z -= m_movevalue * elap;
					ptrTrans->SetQuaternion(quat);
				}

			}
			else if (m_Keycount == 2) {
				if (angleZ > -40.0f) {
					quat.z -= m_movevalue * elap;
					ptrTrans->SetQuaternion(quat);
				}
			}
			break;
		case 2://A
			if (angleX > -40.0f) {
				quat.x -= m_movevalue * elap;
				ptrTrans->SetQuaternion(quat);

			}
			break;
		case 3://Y
			if (angleX < 40.0f) {
				quat.x += m_movevalue * elap;
				ptrTrans->SetQuaternion(quat);
			}
			break;

		}


	}

	void ParentBox::OnUpdate() {
		MoveBox();
	}

	void ParentBox::DrawStrings() {
		auto quat = GetComponent<Transform>()->GetQuaternion();
		auto rot = quat.z * (180.0f / XM_PI) *3;
		auto Rot = GetComponent<Transform>()->GetRotation();

		wstring RotationStr(L"Rotation:\t");
		//RotationStr += L"X=" + Util::FloatToWStr(rot.x, 6, Util::FloatModify::Fixed) + L",\t";
		//RotationStr += L"Y=" + Util::FloatToWStr(rot.y, 6, Util::FloatModify::Fixed) + L",\t";
		RotationStr += L"Z=" + Util::FloatToWStr(rot, 6, Util::FloatModify::Fixed) + L"\n";

		wstring str = RotationStr;

		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);

	}

	void ParentBox::OnUpdate2() {
		DrawStrings();
	}
}