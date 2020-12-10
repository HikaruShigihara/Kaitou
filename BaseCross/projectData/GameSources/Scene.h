/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	enum GameStageKey {
		title,
		stageSelect,
		game,
		result,
		Max
	};

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		vector<wstring> m_stageName;

		void CreateResourses();
		void FindFile(wstring dir);

		wstring m_stageKey[GameStageKey::Max];
		GameStageKey m_gameStageKey;


	public:

		Scene() {};
		virtual ~Scene() {};
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		int m_SelectStageNumber;
		int m_StarNumber;
		bool m_Start;
		int m_star[10];
		int SetStageStar(int StageNumber,int StarQuantity);
		int GetStageStar(int StageNumber);
		int GetStarNumber();
		int SetStarNumber(int star);
		int GetSelectNumber();
		int SetSelectNumber(int select);

		void SetGameStage(GameStageKey key) {
			m_gameStageKey = key;
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), m_stageKey[m_gameStageKey]);
		}
	};

}

//end basecross
