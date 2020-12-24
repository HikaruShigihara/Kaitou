/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {
		Vec3 m_Scale = Vec3(0.3f, 0.5f, 0.3f);
		Vec3 m_Rotation = Vec3(0.0f);
		Vec3 m_Position;

		weak_ptr<GameObject> m_Parent;

		//Vec3 m_Respawn = Vec3(0.0f, 3.0f, 0.0f);
		bool m_clearflag = false;
		bool m_start;
		float time;
		float runtime;
		int a,b=0;
		Vec3 GetPlayerMoveVec() const;

		wstring m_clear = wstring(L"Clear.png");

		float m_WalkSpeed = 7.0f;
		void PlayerMove();
		void Respawn();
		void DrawStrings();
	public:
		Player(
			const shared_ptr<Stage>& StagePtr,
			Vec3& position
			//const shared_ptr<GameObject>& Parent

			) :
			GameObject(StagePtr),
			m_Position(position)
			//m_Parent(Parent)


		{}

		virtual ~Player() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		void StarResult();
		int m_StarQuantityLow[10] = { 10,10,10,10,10,10,10,10,10,10 };
		int m_StarQuantityHigh[10] = { 20,20,20,20,20,20,20,20,20,20 };

		bool GetClearFlag() {
			return m_clearflag;
		}
	};

}
//end basecross

