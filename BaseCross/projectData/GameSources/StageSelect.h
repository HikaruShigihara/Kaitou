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

		wstring m_StageSelect_image;
	public:
		StageSelect() : Stage(),
			m_StageSelect_image(L"StageSelect 2.png")



		{}

		virtual ~StageSelect() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	
}
//end basecross
