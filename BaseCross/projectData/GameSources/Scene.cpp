
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
		FindFile(mediaDir + L"Textures/");
		//FindFile(mediaDir + L"Sound/SE/");
		//FindFile(mediaDir + L"Sound/BGM/");
		//FindFile(mediaDir + L"Sound/BGM/");
		
	}

	void Scene::FindFile(wstring dir) {
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;

		wstring newdir = dir + L"*.*";
		const wchar_t *dirExtension = newdir.c_str();

		hFind = FindFirstFile(dirExtension, &win32fd);

		do {
			// ������FILE_ATTRIBUTE_DIRECTORY�Ȃ�
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// �f�B���N�g�������擾
				wstring ditectoryName = win32fd.cFileName;
				// �V�����t�H���_�̏ꏊ
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// ���̒�������
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//�摜�t�@�C���������ꍇ
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// �t�@�C���̏ꏊ
					wstring texture = dir + fileName;
					// �e�N�X�`���[��o�^
					App::GetApp()->RegisterTexture(fileName, texture);
				}

				if (exe == L".wav") {
					wstring wav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, wav);
				}

				//��O����


			}
		} while (FindNextFile(hFind, &win32fd));

		// �㏈��
		FindClose(hFind);

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