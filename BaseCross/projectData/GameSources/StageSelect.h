/*!
@file StageSelect.h
@brief ステージセレクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageSelect : public Stage {

		void CreateViewLight();

	public:
		StageSelect() : Stage()


		{}

		virtual ~StageSelect() {}

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
	};
	
}
//end basecross
