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
		//App::GetApp()->GetAssetsDirectory(dataDir);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		FindFile(dataDir);
		FindFile(mediaDir + L"Textures/");
		FindFile(mediaDir + L"Model/");
		FindFile(mediaDir + L"BGM/");


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
				//音だった場合
				if (exe == L".wav") {
					wstring wav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, wav);
				}


				//例外(bmf)
				if (exe == L".bmf") {
					// 例外登録
					//ボーンモデルの場合
					if ((fileName == L"player_Walk_Motion.bmf")||
						(fileName == L"Goal_Spot_2.bmf")
						){
						auto modelMesh = MeshResource::CreateBoneModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
					else
						//スタティックモデル
					{
						auto modelMesh = MeshResource::CreateStaticModelMesh(dir, fileName);
						App::GetApp()->RegisterResource(fileName, modelMesh);
					}
				}

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

	int Scene::SetSelectNumber(int select)
	{
		m_SelectStageNumber = select;
		return 0;
	}

	int Scene::GetSelectNumber() 
	{
		return m_SelectStageNumber;
	}
	int Scene::SetStarNumber(int star)
	{
		m_StarNumber = star;
		return 0;
	}

	int Scene::GetStarNumber()
	{
		return m_StarNumber;
	}

	int Scene::SetStageStar(int StageNumber, int StarQuantity)
	{
		m_star[StageNumber] = StarQuantity;
		return 0;
	}

	int Scene::GetStageStar(int StageNumber)
	{
		auto a = m_star[StageNumber];
		return a;
	}
}
//end basecross
