/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	enum Anime
	{
		stop,
		walk,
		fall
	};

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
		int m_Key = 5;
		Vec3 GetPlayerMoveVec() const;
		

		wstring m_clear = wstring(L"Clear.png");
		Anime m_eAnime = Anime::stop;
		bool m_anime = true;

		float m_WalkSpeed = 7.0f;
		void Control();
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
		int m_StarQuantityLow[10] =  { 24,4,8,4,10,10,10,10,10,10 };
		int m_StarQuantityHigh[10] = { 48,8,16,8,20,20,20,20,20,20 };

		void Animation(Anime state) {
			//m_eAnime = state;
			//auto PtrDraw = GetComponent<BcPNTBoneModelDraw>();
			//if (m_eAnime == Anime::walk && m_anime) {
			//	PtrDraw->ChangeCurrentAnimation(L"Walk");
			//	m_anime = false;
			//}
			//else if (m_eAnime == Anime::stop && !m_anime) {
			//	PtrDraw->ChangeCurrentAnimation(L"Stop");
			//	m_anime = true;
			//}
			//else if (m_eAnime == Anime::fall && m_anime) {
			//	PtrDraw->ChangeCurrentAnimation(L"Fall");
			//	m_anime = true;
			//}
		}

		bool GetClearFlag() {
			return m_clearflag;
		}
	};

}
//end basecross

