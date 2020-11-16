
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
		FindFile(mediaDir + L"Textures/");


	}

	void Scene::FindFile(wstring dir) {
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;

		wstring newdir = dir + L"*.*";
		const wchar_t *dirExtension = newdir.c_str();

		hFind = FindFirstFile(dirExtension, &win32fd);

		do {
			// 属性がFILE_ATTRIBUTE_DIRECTORYなら
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// ディレクトリ名を取得
				wstring ditectoryName = win32fd.cFileName;
				// 新しいフォルダの場所
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// その中を検索
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//画像ファイルだった場合
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// ファイルの場所
					wstring texture = dir + fileName;
					// テクスチャーを登録
					App::GetApp()->RegisterTexture(fileName, texture);
				}

				if (exe == L".wav") {
					wstring wav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, wav);
				}

				//例外処理


			}
		} while (FindNextFile(hFind, &win32fd));

		// 後処理
		FindClose(hFind);

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
