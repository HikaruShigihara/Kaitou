/*!
@file ResultStage.h
@brief ���U���g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ResultStage : public Stage {

		void CreateViewLight();

	public:
		ResultStage() : Stage()


		{}

		virtual ~ResultStage() {}

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
	};

}
//end basecross
