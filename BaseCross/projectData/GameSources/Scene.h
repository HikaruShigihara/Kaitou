/*!
@file Scene.h
@brief �V�[��
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
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		vector<wstring> m_stageName;
		shared_ptr<SoundItem> m_bgm;

		void CreateResourses();
		void FindFile(wstring dir);

		wstring m_stageKey[GameStageKey::Max];
		GameStageKey m_gameStageKey;


	public:

		Scene() {};
		virtual ~Scene() {};
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		Vec3 m_getangle;
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
		Vec3 SetAngle(Vec3 angle);
		Vec3 GetAngle();

		void SetGameStage(GameStageKey key) {
			m_gameStageKey = key;
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), m_stageKey[m_gameStageKey]);
		}


		//SE�̊֐�
		void PlaySE(wstring key, float vol) {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}

		//BGM
		void PlayBGM(wstring key, float vol) {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

		//BGM���~�߂�
		void StopBGM() {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			bgm->Stop(m_bgm);
		}


	};

}

//end basecross
