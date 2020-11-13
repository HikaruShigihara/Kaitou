/*!
@file GameStage.h
@brief ゲームステージ
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	class EditStage : public Stage {
		//XMLリーダー
		unique_ptr<XmlDocReader> m_XmlDocReader;
	public:
		//構築と破棄
		EditStage() :Stage() {}
		virtual ~EditStage() {}

		virtual void OnCreate()override;

	};
}