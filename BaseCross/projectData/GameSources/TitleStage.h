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

		wstring m_title;
		wstring m_titleflame;
		wstring m_Startlogo;
		wstring m_Selectlogo;
		wstring m_Endlogo;


		void CreateUI();
		void CreateBack();
		void CreateStage();
		void BoolSet();

	public:
		int m_SelectChoices;
		int m_SelectQuantity;//選択肢の個数

		std::shared_ptr<basecross::Title_UI> m_Start;
		std::shared_ptr<basecross::Title_UI> m_Select;
		std::shared_ptr<basecross::Title_UI> m_End;
		std::shared_ptr<basecross::Title_UI> m_StartLogoObject;
		std::shared_ptr<basecross::Title_UI> m_SelectLogoObject;
		std::shared_ptr<basecross::Title_UI> m_EndLogoObject;


		TitleStage() : Stage(),
			m_title(L"Title.png"),
			m_titleflame(L"Frame.png"),
			m_Startlogo(L"Startlogo.png"),
			m_Selectlogo(L"Selectlogo.png"),
			m_Endlogo(L"Endlogo.png"),
			m_bgm(NULL)
		{}


		virtual ~TitleStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

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

	};

}
//end basecross
