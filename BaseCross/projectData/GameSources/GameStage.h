/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//XMLリーダー
		unique_ptr<XmlDocReader> m_XmlDocReader;

		//ビューの作成
		void CreateViewLight();
		//ボックスの作成
		void CreateFixedBox();
		//XMLのオブジェクトの作成
		void CreateXmlObjects();

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		//virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
//	class MoveBox : public GameObject;
//--------------------------------------------------------------------------------------
	class MoveBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		MoveBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~MoveBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

}
//end basecross

