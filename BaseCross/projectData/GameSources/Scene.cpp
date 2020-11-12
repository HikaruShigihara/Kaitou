
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Scene::CreateResourses() {
		wstring dataDir;
		//media�f�B���N�g���擾�p
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
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//���\�[�X�쐬
			CreateResourses();

			//�ύX�ŃV�[���J��
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
