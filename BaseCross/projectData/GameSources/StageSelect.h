/*!
@file StageSelect.h
@brief �X�e�[�W�Z���N�g
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
