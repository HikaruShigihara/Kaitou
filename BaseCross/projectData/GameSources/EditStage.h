/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	class EditStage : public Stage {
		//XML���[�_�[
		unique_ptr<XmlDocReader> m_XmlDocReader;
	public:
		//�\�z�Ɣj��
		EditStage() :Stage() {}
		virtual ~EditStage() {}

		virtual void OnCreate()override;

	};
}