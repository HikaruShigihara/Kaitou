/*!
@file TitleStage.h
@brief ƒ^ƒCƒgƒ‹.h‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage : public Stage {
		
		shared_ptr<SoundItem> m_bgm;

		void CreateViewLight();

		wstring m_title;

		void CreateUI();
		void CreateBack();
		void CreateStage();
	public:
		TitleStage() : Stage(),
			m_title(L"Title.png"),
			m_bgm(NULL)
		{}
		
		virtual ~TitleStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//SE‚ÌŠÖ”
		void PlaySE(wstring key, float vol) {
			auto se = App::GetApp()->GetXAudio2Manager();
			se->Start(key, 0, vol);
		}

		//BGM
		void PlayBGM(wstring key, float vol) {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(key, XAUDIO2_LOOP_INFINITE, vol);
		}

		//BGM‚ðŽ~‚ß‚é
		void StopBGM() {
			auto bgm = App::GetApp()->GetXAudio2Manager();
			bgm->Stop(m_bgm);
		}

	};

}
//end basecross
