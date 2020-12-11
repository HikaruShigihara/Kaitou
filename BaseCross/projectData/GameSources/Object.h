#pragma once
#include "stdafx.h"

namespace basecross {

	class FixedBox : public GameObject {
		Vec3 m_scale = Vec3(0.65f);
		//Vec3 m_Rotation;
		Vec3 m_Position;

		weak_ptr<GameObject> m_Parent;
		Vec3 m_VecToParent;

		void SeekParent();

	public:
		//ç\ízÇ∆îjä¸
		FixedBox(const shared_ptr<Stage>& StagePtr,
			//const Vec3& Scale,
			//const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<GameObject>& Parent,
			const Vec3& VecToParent

		) : 
			GameObject(StagePtr),
			//m_Scale(Scale),
			//m_Rotation(Rotation),
			m_Position(Position),
			m_Parent(Parent),
			m_VecToParent(VecToParent)

		{}


		virtual ~FixedBox()
		{}
		//èâä˙âª
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		weak_ptr<GameObject> m_Parent;
		Vec3 m_VecToParent;

		void SeekParentGoal();
		
	public:
		//ç\ízÇ∆îjä¸
		Goal(const shared_ptr<Stage>& StagePtr,
			//const Vec3& Scale,
			//const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<GameObject>& Parent,
			const Vec3& VecToParent

		) :
			GameObject(StagePtr),
			//m_Scale(Scale),
			//m_Rotation(Rotation),
			m_Position(Position),
			m_Parent(Parent),
			m_VecToParent(VecToParent)

		{}

		virtual ~Goal()
		{}
		//èâä˙âª
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


	class ParentBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_TotalRot = 0.0f;
		float m_RotSpan = 0.02f;
		Quat qt;
		float x = 2.0f;
		int m_Key = 5;
		int m_Keycount = NULL;
		bool m_start;
		int m_flag = 0;
		float m_time;
		float m_movevalue = 0.5f;

		void MoveBox();
		//void DrawStrings();
	public:
		//ç\ízÇ∆îjä¸
		ParentBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position

		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position)

		{}

		virtual ~ParentBox()
		{}
		//èâä˙âª
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//virtual void OnUpdate2() override;
	};
}