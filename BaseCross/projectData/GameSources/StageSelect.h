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
		wstring m_StageSelect_Stage01;
		wstring m_StageSelect_Stage02;
		wstring m_StageSelect_Stage03;
		wstring m_StageSelect_Arrow;
		wstring m_StageSelect_Arrow_yellow;


	public :
		int m_StageSelectNumber;
		int m_StageQuantity;//ステージの個数
		float time;
		std::shared_ptr<basecross::StageSelect_UI> m_Stage01;
		std::shared_ptr<basecross::StageSelect_UI> m_Stage02;
		std::shared_ptr<basecross::StageSelect_UI> m_Stage03;
		std::shared_ptr<basecross::StageSelect_ArrowRight> m_StageArrowRight;
		std::shared_ptr<basecross::StageSelect_ArrowLeft> m_StageArrowLeft;



		StageSelect() : Stage(),
			m_StageSelect_image(L"StageSelect 3.png"),
			m_StageSelect_Stage01(L"red.jpg"),
			m_StageSelect_Stage02(L"blue22.jpg"),
			m_StageSelect_Stage03(L"yellow.jpg"),
			m_StageSelect_Arrow(L"Select_Arrow_2.png"),
			m_StageSelect_Arrow_yellow(L"Select_Arrow_yellow.png")
		{}



		

		virtual ~StageSelect() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	
}
//end basecross
