/*!
@file TitleStage.h
@brief タイトル.hなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage : public Stage {
		
		shared_ptr<SoundItem> m_bgm;

		void CreateViewLight();

	public:
		TitleStage() : Stage(),
			m_bgm(NULL)


		{}
		
		virtual ~TitleStage() {}

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;

		//SEの関数
		void PlaySE(wstring key, float vol) {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}

		//BGM
		void PlayBGM(wstring key, float vol) {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

		//BGMを止める
		void StopBGM() {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			bgm->Stop(m_bgm);
		}

		//シーン遷移の仕方
		//App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::stageSelect);


	};

}
//end basecross
