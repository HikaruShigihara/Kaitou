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
		//Vec3 m_Respawn = Vec3(0.0f, 3.0f, 0.0f);
		bool m_clearflag = false;
		float time;
		Vec3 GetPlayerMoveVec() const;

		wstring m_clear = wstring(L"Clear.png");

		float m_WalkSpeed = 6.7f;
		void PlayerMove();
		void Respawn();
		void DrawStrings();
	public:
		Player(
			const shared_ptr<Stage>& StagePtr,
			//Vec3& scale,
			//Vec3& rotation,
			Vec3& position
			) :
			GameObject(StagePtr),
			//m_Scale(scale),
			//m_Rotation(rotation),
			m_Position(position)
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

		bool GetClearFlag() {
			return m_clearflag;
		}
	};

}
//end basecross

