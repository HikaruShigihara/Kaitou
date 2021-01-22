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


		shared_ptr<GameObjectGroup> m_group;
		shared_ptr<GameObject> m_fixedbox;
		shared_ptr<GameObject> m_Parentbox;
		shared_ptr<GameObject> m_numbers[3];
		shared_ptr<GameObject> m_Target;
		shared_ptr<GameObject> m_Goal;
		shared_ptr<GameObject> m_Switch;
		shared_ptr<GameObject> m_player;
		shared_ptr<GameObject> m_mask;
		shared_ptr<GameObject> m_text, m_text2, m_text_joken1, m_text_joken2, m_text_joken3;
		wstring m_back;
		wstring m_number_UI;
		wstring m_mask_UI;
		wstring m_text_UI1, m_text_UI2;
		wstring m_text_UI_joken1_Before[5] = { L"24",L"4",L"8" ,L"4", L"4"};
		wstring m_text_UI_joken2_Before[5] = { L"48",L"8",L"16" ,L"8", L"4" };
		wstring m_text_UI_joken3_Before[5] = { L"72",L"12",L"24" ,L"12", L"4" };

		wstring m_operation_UI1, m_operation_UI2;
		wstring m_text_UI_joken1_After, m_text_UI_joken2_After, m_text_UI_joken3_After;
		wstring m_cloud,m_cloud1, m_cloud2, m_cloud3, m_cloud4;

		wstring m_clear;
		bool m_clearflag;
		float m_position;
		int m_number;
		//�r���[�̍쐬
		void CreateViewLight();
		//�{�b�N�X�̍쐬
		void CreateUI();
		void CreateOperation_UI();
		void CreateBack();
		void CreateCloud();
		void CreateEffect();
		void CreateMask();
		//XML�̃I�u�W�F�N�g�̍쐬
		void CreateXmlObjects();

	public:
		//�\�z�Ɣj��
		GameStage() : Stage(),
			m_back(L"Blue_Back.png"),
			m_number_UI(L"number.png"),
			m_mask_UI(L"Base.png"),
			m_cloud1(L"Cloud Parts 1.png"),
			m_cloud2(L"Cloud Parts 2.png"),
			m_cloud3(L"Cloud Parts 3.png"),
			m_cloud4(L"Cloud Parts 4.png"),
			m_cloud(L"Cloud.png"),
			m_clear(L"Clear.png"),
			m_operation_UI1(L"Ten_Key.png"),
			m_operation_UI2(L"Analog_Stick.png"),
			m_text_UI1(L"�X�^�[�g�{�^���ŊJ�n�I"),
			m_text_UI2(L"����"),
			m_text_UI_joken1_After(L"���ȓ��ŃN���A"),
			m_text_UI_joken2_After(L"���ȓ��ŃN���A"),
			m_text_UI_joken3_After(L"���ȓ��ŃN���A"),
			m_number(000),
			m_position(0.65f)
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
	};
}
//end basecross

