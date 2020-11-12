/*!
@file ResultStage.h
@brief ƒŠƒUƒ‹ƒg
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
