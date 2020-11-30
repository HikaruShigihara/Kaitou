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
		wstring m_Result_image;
		wstring m_Result_Star1;
		wstring m_Result_Star2;
		wstring m_Result_Star3;
		wstring m_Result_StarOnly;

	public:
		float x = 1.0f;
		std::shared_ptr<basecross::Result_UI> m_Star01;
		std::shared_ptr<basecross::Result_UI> m_Star02;
		std::shared_ptr<basecross::Result_UI> m_Star03;

		ResultStage() : Stage(),
			m_Result_image(L"Result.png"),
			m_Result_Star1(L"Star_1.png"),
			m_Result_Star2(L"Star_2.png"),
			m_Result_Star3(L"Star_3.png"),
			m_Result_StarOnly(L"StarOnly.png")
			
		{}

		virtual ~ResultStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
