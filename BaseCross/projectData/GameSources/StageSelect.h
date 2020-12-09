/*!
@file StageSelect.h
@brief ステージセレクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class StageSelect : public Stage {

		void CreateViewLight();
		void CreateUI();
		void BoolCheck();

		wstring m_StageSelect_image;
		wstring m_StageSelect_Stage01,m_StageSelect_Stage02,m_StageSelect_Stage03;
		wstring m_StageSelect_Arrow,m_StageSelect_Arrow_yellow;
		wstring m_BlackStar;


	public :
		int m_StageQuantity;//ステージの個数
		float time;
		std::shared_ptr<basecross::StageSelect_UI> m_Stage01,m_Stage02,m_Stage03;
		std::shared_ptr<basecross::StageSelect_ArrowRight> m_StageArrowRight;
		std::shared_ptr<basecross::StageSelect_ArrowLeft> m_StageArrowLeft;
		int m_StageSelectNumber;

		StageSelect() : Stage(),
			m_StageSelect_image(L"StageSelect 3.png"),
			m_StageSelect_Stage01(L"red.jpg"),
			m_StageSelect_Stage02(L"blue22.jpg"),
			m_StageSelect_Stage03(L"yellow.jpg"),
			m_StageSelect_Arrow(L"Select_Arrow_2.png"),
			m_StageSelect_Arrow_yellow(L"Select_Arrow_yellow.png"),
			m_BlackStar(L"Black_Star.png")
		{}



		

		virtual ~StageSelect() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void PlaySE(wstring key, float vol) {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}


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
