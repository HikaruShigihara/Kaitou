#pragma once
#include "stdafx.h"

namespace basecross {

	class FixedBox : public GameObject {
		weak_ptr<GameObject> m_Parent;
		Vec3 m_VecToParent;

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//ç\ízÇ∆îjä¸
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) : 
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position)
		{}

		virtual ~FixedBox()
		{}
		//èâä˙âª
		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
		void SeekParent();
	};

}