/*!
@file ResultStage.h
@brief ƒŠƒUƒ‹ƒg
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ResultStage : public Stage {

		void CreateViewLight();
		void CreateUI();
		void BoolSet();

		wstring m_Result_image;
		wstring m_Result_Star1;
		wstring m_Result_Star2;
		wstring m_Result_Star3;
		wstring m_Result_StarOnly;
		wstring m_titleflame;
		wstring m_Nextlogo;
		wstring m_Selectlogo;
		wstring m_Endlogo;
		wstring m_next;
	public:
		int m_SelectChoices;
		int m_SelectQuantity;//‘I‘ğˆ‚ÌŒÂ”
		int m_StarQuantity;

		//float x = 1.0f;
		std::shared_ptr<basecross::Result_UI> m_Star01;
		std::shared_ptr<basecross::Result_UI> m_Star02;
		std::shared_ptr<basecross::Result_UI> m_Star03;

		std::shared_ptr<basecross::Result_UI> m_Start;
		std::shared_ptr<basecross::Result_UI> m_Select;
		std::shared_ptr<basecross::Result_UI> m_End;
		std::shared_ptr<basecross::Result_UI> m_NextLogoObject;
		std::shared_ptr<basecross::Result_UI> m_SelectLogoObject;
		std::shared_ptr<basecross::Result_UI> m_EndLogoObject;


		ResultStage() : Stage(),
			m_Result_image(L"Result.png"),
			m_Result_Star1(L"Star_1.png"),
			m_Result_Star2(L"Star_2.png"),
			m_Result_Star3(L"Star_3.png"),
			m_Result_StarOnly(L"StarOnly.png"),
			m_titleflame(L"Frame.png"),
			m_Selectlogo(L"SelectStage.png"),
			m_Nextlogo(L"next.png"),
			m_Endlogo(L"Titlelogo.png")



		{}

		virtual ~ResultStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
