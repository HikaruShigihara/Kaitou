/*!
@file ResultStage.h
@brief ���U���g
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
		wstring m_SelectArrow;

		wstring m_nextStage_text, m_stageSelect_text, m_backTitle_text;
		shared_ptr<GameObject> m_text_next, m_text_stageselect, m_text_backtitle;
		shared_ptr<GameObject> m_text_next2, m_text_stageselect2, m_text_backtitle2;
	public:
		int m_SelectChoices;
		int m_SelectQuantity;//�I�����̌�
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
		std::shared_ptr<basecross::Title_Arrow> m_SelectArrowNumber1;
		std::shared_ptr<basecross::Title_Arrow> m_SelectArrowNumber2;
		std::shared_ptr<basecross::Title_Arrow> m_SelectArrowNumber3;



		ResultStage() : Stage(),
			m_Result_image(L"Result.png"),
			m_Result_Star1(L"Star_1.png"),
			m_Result_Star2(L"Star_2.png"),
			m_Result_Star3(L"Star_3.png"),
			m_Result_StarOnly(L"StarOnly.png"),
			m_titleflame(L"Frame.png"),
			m_Selectlogo(L"SelectStage.png"),
			m_Nextlogo(L"next.png"),
			m_Endlogo(L"Titlelogo.png"),
			m_SelectArrow(L"Select_Arrow.png"),

			m_nextStage_text(L"���̃X�e�[�W"),
			m_stageSelect_text(L"�X�e�[�W�Z���N�g"),
			m_backTitle_text(L"�^�C�g���ɖ߂�")

		{}

		virtual ~ResultStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
