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
		//�\�z�Ɣj��
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

		void SeekParentGoal();
		
	public:
		//�\�z�Ɣj��
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
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class SwitchBox : public GameObject	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		weak_ptr<GameObject> m_Parent;
		Vec3 m_VecToParent;


	public:
		//�\�z�Ɣj��
		SwitchBox(const shared_ptr<Stage>& StagePtr,
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

		virtual ~SwitchBox()
		{}
		//������
		virtual void OnCreate() override;

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
		//virtual void OnUpdate2() override;
	};

	class SwitchButton : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		weak_ptr<GameObject> m_Parent;
		Vec3 m_VecToParent;


	public:
		//�\�z�Ɣj��
		SwitchButton(const shared_ptr<Stage>& StagePtr,
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

		virtual ~SwitchButton()
		{}
		 void OnCollisionEnter(shared_ptr<GameObject>& Other, shared_ptr<GameObject>& a) ;

		//������
		virtual void OnCreate() override;
	};



}