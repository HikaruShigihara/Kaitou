
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Scene::CreateResourses() {
		wstring dataDir;
		//mediaディレクトリ取得用
		App::GetApp()->GetAssetsDirectory(dataDir);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		FindFile(dataDir);
		FindFile(mediaDir + L"Texters/");
		FindFile(mediaDir + L"Sound/SE/");
		FindFile(mediaDir + L"Sound/BGM/");
	}

	void Scene::FindFile(wstring dir) {

	}

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//リソース作成
			CreateResourses();

			//変更でシーン遷移
			SetGameStage(GameStageKey::title);

		}
		catch (...) {
			throw;
		}
	}

	//Scene::~Scene() {
	//}

	void Scene::OnEvent(const shared_ptr<Event>& event) {

		switch (m_gameStageKey)
		{
		case GameStageKey::title:
			ResetActiveStage<TitleStage>();
			break;
		case GameStageKey::stageSelect:
			ResetActiveStage<StageSelect>();
			break;
		case GameStageKey::game:
			ResetActiveStage<GameStage>();
			break;
		case GameStageKey::result:
			ResetActiveStage<ResultStage>();
			break;
		}

	}

}
//end basecross
