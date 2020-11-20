/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//Vec3 m_Respawn = Vec3(0.0f, 3.0f, 0.0f);
		Vec3 GetPlayerMoveVec() const;

		void PlayerMove();
		void StageRotate();
		void Respawn();
		void DrawStrings();
	public:
		Player(
			const shared_ptr<Stage>& StagePtr,
			Vec3& scale,
			Vec3& rotation,
			Vec3& position
			) :
			GameObject(StagePtr),
			m_Scale(scale),
			m_Rotation(rotation),
			m_Position(position)
		{}

		virtual ~Player() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;


	};

}
//end basecross

