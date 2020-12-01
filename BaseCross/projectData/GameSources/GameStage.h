/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//XML���[�_�[
		unique_ptr<XmlDocReader> m_XmlDocReader;

		shared_ptr<SoundItem> m_bgm;

		shared_ptr<GameObjectGroup> m_group;
		shared_ptr<GameObject> m_fixedbox;
		shared_ptr<GameObject> m_Parentbox;
		shared_ptr<GameObject> m_numbers[3];
		shared_ptr<GameObject> m_Target;
		
		wstring m_back;
		wstring m_number_UI;
		wstring m_goal;

		wstring m_cloud,m_cloud1, m_cloud2, m_cloud3, m_cloud4;
		wstring m_clear;
		bool m_clearflag;
		Vec3 m_scale, m_rotation, m_position;
		int m_number;
		//�r���[�̍쐬
		void CreateViewLight();
		//�{�b�N�X�̍쐬
		void CreateFixedBox();
		void CreateUI();
		void CreatePlayer();
		void MoveStage();
		void CreateBack();
		void CreateCloud();

		//XML�̃I�u�W�F�N�g�̍쐬
		void CreateXmlObjects();

	public:
		//�\�z�Ɣj��
		GameStage() : Stage(),
			m_back(L"Blue_Back.png"),
			m_number_UI(L"number.png"),
			m_goal(L"red.png"),
			m_cloud1(L"Cloud Parts 1.png"),
			m_cloud2(L"Cloud Parts 2.png"),
			m_cloud3(L"Cloud Parts 3.png"),
			m_cloud4(L"Cloud Parts 4.png"),
			m_cloud(L"Cloud.png"),
			m_clear(L"Clear.png"),
			m_number(000),
			m_scale(0.13f),
			m_rotation(0.0f),
			m_position(0.6f),
			m_bgm(NULL)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;

		int GetCount() const {
			return m_number;
		}

		void SetCount(int i){
			m_number += i;
		}
		void resetCount() {
			m_number = 0;
		}
		void PlayBGM(wstring key, float vol) {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

	};

	//--------------------------------------------------------------------------------------
//	class MoveBox : public GameObject;
//--------------------------------------------------------------------------------------
	//class MoveBox : public GameObject {
	//	Vec3 m_Scale;
	//	Vec3 m_Rotation;
	//	Vec3 m_Position;
	//public:
	//	//�\�z�Ɣj��
	//	MoveBox(const shared_ptr<Stage>& StagePtr,
	//		const Vec3& Scale,
	//		const Vec3& Rotation,
	//		const Vec3& Position
	//	);
	//	virtual ~MoveBox();
	//	//������
	//	virtual void OnCreate() override;
	//	//����
	//};

}
//end basecross

