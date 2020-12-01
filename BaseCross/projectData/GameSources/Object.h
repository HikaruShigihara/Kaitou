#pragma once
#include "stdafx.h"

namespace basecross {

	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		weak_ptr<GameObject> m_Parent;
		Vec3 m_VecToParent;

		void SeekParent();

	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<GameObject>& Parent,
			const Vec3& VecToParent

		) : 
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_Parent(Parent),
			m_VecToParent(VecToParent)

		{}

		virtual ~FixedBox()
		{}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class Goal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		weak_ptr<GameObject> m_Parent;
		Vec3 m_VecToParent;


	public:
		//�\�z�Ɣj��
		Goal(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
			//const shared_ptr<GameObject>& Parent,
			//const Vec3& VecToParent

		) :
			GameObject(StagePtr),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position)
			//m_Parent(Parent),
			//m_VecToParent(VecToParent)

		{}

		virtual ~Goal()
		{}
		//������
		virtual void OnCreate() override;
	};


	class ParentBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
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
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
}