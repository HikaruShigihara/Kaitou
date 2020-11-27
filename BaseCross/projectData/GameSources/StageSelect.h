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
		wstring m_StageSelect_test;
		wstring m_StageSelect_test2;

	public :
		int m_StageSelectNumber;
		int m_StageQuantity;//ステージの個数
		std::shared_ptr<basecross::StageSelect_UI> m_Gorira;
		std::shared_ptr<basecross::StageSelect_UI> m_Banana;


		StageSelect() : Stage(),
			m_StageSelect_image(L"StageSelect 2.png"),
			m_StageSelect_test(L"Banana.jpg"),
			m_StageSelect_test2(L"00.jpg") {}



		

		virtual ~StageSelect() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	
}
//end basecross
