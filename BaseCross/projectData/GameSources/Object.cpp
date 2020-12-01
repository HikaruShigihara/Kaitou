#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//初期化
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);


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
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
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

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::Auto);	
		ptrColl->SetMakedSize(Vec3(2.0f, 2.0f, 2.0f));
		ptrColl->SetFixed(true);

		auto ptrParent = m_Parent.lock();
		if (ptrParent) {
			//auto posTarget = ptrParent->GetComponent<Transform>()->GetPosition();
			//posTarget += m_VecToParent;
			//ptrTransform->SetPosition(posTarget);
			//auto posTarget = ptrParent->GetComponent<Transform>()->GetRotation();
			//posTarget += m_VecToParent;
			//ptrTransform->SetRotation(posTarget);

		}
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//PsBoxParam param(ptrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeActive);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);

	}
	void Goal::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
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
		//if (ptrParent) {
		//	auto posTarget = ptrParent->GetComponent<Transform>()->GetPosition();
		//	posTarget += m_VecToParent;
		//	ptrTransform->SetPosition(posTarget);
		//	//auto posTarget = ptrParent->GetComponent<Transform>()->GetRotation();
		//	//posTarget += m_VecToParent;
		//	//ptrTransform->SetRotation(posTarget);

		//}
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		//PsBoxParam param(ptrTransform->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeActive);
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
			ptrTrans->SetQuaternion(mat.quatInMatrix());
		}
	}

	void FixedBox::OnUpdate() {
		SeekParent();
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
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPCTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetAlpha(true);

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}
	void ParentBox::OnUpdate() {
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PtrAction = AddComponent<Action>();
		PtrAction->AddRotateBy(1.0f, Vec3(0, 0, 90));
		PtrAction->SetLooped(false);

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {

			PtrAction->Run();

		}

	}
}