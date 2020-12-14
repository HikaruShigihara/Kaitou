/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//XMLリーダー
		unique_ptr<XmlDocReader> m_XmlDocReader;


		shared_ptr<GameObjectGroup> m_group;
		shared_ptr<GameObject> m_fixedbox;
		shared_ptr<GameObject> m_Parentbox;
		shared_ptr<GameObject> m_numbers[3];
		shared_ptr<GameObject> m_Target;
		shared_ptr<GameObject> m_Goal;
		shared_ptr<GameObject> m_player;
		shared_ptr<GameObject> m_mask;
		shared_ptr<GameObject> m_text;
		wstring m_back;
		wstring m_number_UI;
		wstring m_mask_UI;
		wstring m_goal;
		wstring m_text_UI1,m_text_UI2;

		wstring m_cloud,m_cloud1, m_cloud2, m_cloud3, m_cloud4;
		wstring m_clear;
		bool m_clearflag;
		float m_position;
		int m_number;
		//ビューの作成
		void CreateViewLight();
		//ボックスの作成
		void CreateUI();
		void CreateBack();
		void CreateCloud();
		void CreateMask();
		//XMLのオブジェクトの作成
		void CreateXmlObjects();

	public:
		//構築と破棄
		GameStage() : Stage(),
			m_back(L"Blue_Back.png"),
			m_number_UI(L"number.png"),
			m_goal(L"red.png"),
			m_mask_UI(L"Base.png"),
			m_cloud1(L"Cloud Parts 1.png"),
			m_cloud2(L"Cloud Parts 2.png"),
			m_cloud3(L"Cloud Parts 3.png"),
			m_cloud4(L"Cloud Parts 4.png"),
			m_cloud(L"Cloud.png"),
			m_clear(L"Clear.png"),
			m_text_UI1(L"スタートボタンで開始！"),
			m_text_UI2(L"歩数"),
			m_number(000),
			m_position(0.65f)
		{}
		virtual ~GameStage() {}
		//初期化
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

