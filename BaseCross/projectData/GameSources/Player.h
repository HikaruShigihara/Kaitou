/*!
@file Player.h
@brief �v���C���[�Ȃ�
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
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		//virtual void OnUpdate() override;
		//virtual void OnUpdate2() override;


	};

}
//end basecross

