/*!
@file StageSelect.h
@brief ステージセレクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class StageSelect : public Stage {

		int m_Stagenumber = 1;
		bool m_stageNameFlag = true;

		void CreateViewLight();
		void CreateUI();
		void BoolCheck();
		void CreateText();

		wstring m_StageSelect_image;
		wstring m_StageSelect_Stage01,m_StageSelect_Stage02,m_StageSelect_Stage03,
			m_StageSelect_Stage04, m_StageSelect_Stage05, m_StageSelect_Stage06;
		wstring m_StageSelect_Arrow,m_StageSelect_Arrow_yellow;
		wstring m_Star,m_BlackStar,m_starframe;
		wstring m_StageText;

		wstring m_textA;
		wstring m_textB;

	public :
		int m_StageQuantity;//ステージの個数
		float time;
		std::shared_ptr<basecross::StageSelect_UI> m_Stage01,m_Stage02,m_Stage03, m_Stage04, m_Stage05, m_Stage06 ;
		std::shared_ptr<basecross::StageSelect_ArrowRight> m_StageArrowRight;
		std::shared_ptr<basecross::StageSelect_ArrowLeft> m_StageArrowLeft;
		std::shared_ptr<basecross::StageSlect_Star> m_star1,m_star2,m_star3;
		shared_ptr<GameObject> m_StageNumber;
		int m_StageSelectNumber;

		StageSelect() : Stage(),
			m_StageSelect_image(L"StageSelect 3.png"),
			m_StageSelect_Stage01(L"Stage1.png"),
			m_StageSelect_Stage02(L"Stage2.png"),
			m_StageSelect_Stage03(L"Stage3.png"),
			m_StageSelect_Stage04(L"Stage4.png"),
			m_StageSelect_Stage05(L"Stage5.png"),
			m_StageSelect_Stage06(L"Stage6.png"),
			m_StageSelect_Arrow(L"Select_Arrow_2.png"),
			m_StageSelect_Arrow_yellow(L"Select_Arrow_yellow.png"),
			m_starframe(L"Star_Frame.png"),
			m_Star(L"StarOnly.png"),
			m_BlackStar(L"Black_Star.png"),
			m_StageText(L"ステージ"),
			m_textA(L"A：決定！"),
			m_textB(L"B：タイトルに戻る")

		{}



		

		virtual ~StageSelect() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		void StarDisplay();




	};


	//class SelectStageClass : public GameObject {
	//public:
	//	//構築と破棄
	//	SelectStageClass(const shared_ptr<Stage>& StagePtr
	//	) :
	//		GameObject(StagePtr)
	//	{}

	//	virtual ~SelectStageClass()
	//	{}
	//	//初期化
	//	int SelectStage();

	//};

}
//end basecross
