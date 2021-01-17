/*!
@file TitleStage.h
@brief タイトル.hなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage : public Stage {
		
		void CreateViewLight();

		wstring m_title;
		wstring m_titleflame;
		wstring m_Startlogo;
		wstring m_Selectlogo;
		wstring m_Endlogo;
		wstring m_SelectArrow;

		wstring m_start_text, m_stageSelect_text, m_tutorial_text;
		wstring m_cloud1, m_cloud2, m_cloud3, m_cloud4;
		wstring m_Kai, m_Tou;

		shared_ptr<GameObject> m_start_next, m_text_stageselect, m_text_tutorial;
		shared_ptr<GameObject> m_start_next2, m_text_stageselect2, m_text_tutorial2;

		void CreateUI();
		void CreateCloud();
		void CreateBack();
		//void CreateStage();
		void BoolSet();

	public:
		int m_SelectChoices;
		int m_SelectQuantity;//選択肢の個数

		std::shared_ptr<basecross::Title_UI> m_Start;
		std::shared_ptr<basecross::Title_UI> m_Select;
		std::shared_ptr<basecross::Title_UI> m_End;
		std::shared_ptr<basecross::Title_UI> m_StartLogoObject;
		std::shared_ptr<basecross::Title_UI> m_SelectLogoObject;
		std::shared_ptr<basecross::Title_UI> m_EndLogoObject;
		std::shared_ptr<basecross::Title_Arrow> m_SelectArrowNumber1;
		std::shared_ptr<basecross::Title_Arrow> m_SelectArrowNumber2;
		std::shared_ptr<basecross::Title_Arrow> m_SelectArrowNumber3;



		TitleStage() : Stage(),
			m_title(L"Blue_Back.png"),
			m_titleflame(L"Frame.png"),
			m_Startlogo(L"Startlogo.png"),
			m_Selectlogo(L"Selectlogo.png"),
			m_Endlogo(L"Endlogo.png"),
			m_SelectArrow(L"Select_Arrow.png"),
			m_start_text(L"スタート"),
			m_stageSelect_text(L"ステージセレクト"),
			m_tutorial_text(L"チュートリアル"),
			m_cloud1(L"Cloud Parts 1.png"),
			m_cloud2(L"Cloud Parts 2.png"),
			m_cloud3(L"Cloud Parts 3.png"),
			m_cloud4(L"Cloud Parts 4.png"),
			m_Kai(L"Title text.png"),
			m_Tou(L"Title text2.png")

		{}


		virtual ~TitleStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

}
//end basecross
