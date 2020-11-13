/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {
	public:
		Player(const shared_ptr<Stage>& StagePtr) :
			GameObject(StagePtr)
		{}

		virtual ~Player() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		//virtual void OnUpdate() override;
		//virtual void OnUpdate2() override;


	};

}
//end basecross

