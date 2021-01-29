#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void UI_Base::Draw() {

		float X = m_Vertex.x / 2.0f;
		float Y = m_Vertex.y / 2.0f;

		vector<VertexPositionColorTexture> vertices;
		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices.push_back(VertexPositionColorTexture(Vec3(-X, Y, 0), color, Vec2(0.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(X, Y, 0), color, Vec2(1.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(-X, -Y, 0), color, Vec2(0.0f, 1.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(X, -Y, 0), color, Vec2(1.0f, 1.0f)));

		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetTextureResource(m_textures);
		SetDrawLayer(m_layer);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		SetAlphaActive(true);

	}

	//テキスト
	void UI_Text::OnCreate() {
		SetDrawLayer(m_layer);
		auto text = AddComponent<StringSprite>();
		text->SetTextAlignment(m_textAlignment);
		text->SetFont(m_fontName, m_fontSize);
		text->SetTextRect(m_rect);
		text->SetFontColor(m_color);
		text->SetText(m_text);
		if (m_isBk) text->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	void UI_Text::UpdateText(const wstring value) {
		auto text = GetComponent<StringSprite>();
		text->SetText(value);
	}
	void UI_Text::Remove() {
		GetStage()->RemoveGameObject<GameObject>(GetThis<UI_Text>());
	}

	void Mask_UI::OnCreate() {
		Draw();
	}

	void Title_UI::OnCreate() {
		Draw();
	}

	void StageSelect_UI::OnCreate() {
		Draw();
	}

	void Result_UI::OnCreate() {
		Draw();
	}

	void Game_Back::OnCreate() {
		Draw();
	}

	void Clear::OnCreate() {
		Draw();
	}

	void Operation_UI::OnCreate() {
		Draw();
	}

	void Number_UI::OnCreate() {
		float score = static_cast<float>(m_Score / m_place % 10);
		float Width = 69.1f / 691.0f;	//各数字の幅をテクスチャ座標に変換

		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices = {
			{Vec3(0,    0, 0), color, Vec2((score + 0) * Width, 0.0f)}, // 頂点１
			{Vec3(50,    0, 0), color, Vec2((score + 1) * Width, 0.0f)}, // 頂点２
			{Vec3(0, -100, 0), color, Vec2((score + 0) * Width, 1.0f)}, // 頂点３
			{Vec3(50, -100, 0), color, Vec2((score + 1) * Width, 1.0f)}, // 頂点４

		};
		indices = { 0, 1, 2, 2, 1, 3 };
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetTextureResource(m_textures);
		SetDrawLayer(m_layer);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);

		SetAlphaActive(true);
	}

	void Number_UI::OnUpdate2() {
		auto gamestage = dynamic_pointer_cast<GameStage>(GetStage());

		float n = static_cast<float>(gamestage->GetCount() / m_place % 10); // 表示したい数字
		float w = 69.1f / 691.0f; // 各数字の幅をテクスチャ座標に変換する

		vertices[0].textureCoordinate.x = (n + 0) * w;
		vertices[1].textureCoordinate.x = (n + 1) * w;
		vertices[2].textureCoordinate.x = (n + 0) * w;
		vertices[3].textureCoordinate.x = (n + 1) * w;
		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->UpdateVertices(vertices); // 頂点データを更新する

	}
	void Cloud::OnCreate() {
		Draw();
		auto PtrAction = AddComponent<Action>();

		PtrAction->AddMoveBy(0.1f, Vec3(5.0f, 0, 0));
		PtrAction->SetLooped(true);
		//アクション開始
		PtrAction->Run();
	}
	void Cloud::OnUpdate() {
		auto PtrAction = AddComponent<Action>();
		auto trans = GetComponent<Transform>();
		auto pos = trans->GetPosition();
		if (pos.x >= 1200.0f) {
			PtrAction->AddMoveTo(0.000001f, Vec3(-1200.0f, pos.y, 0.0f));
			PtrAction->AddMoveTo(45.0f, Vec3(1200.0f, pos.y, 0.0f));
		}
	}

	void Cloud_Small::OnCreate() {
		Draw();
		auto PtrAction = AddComponent<Action>();

		PtrAction->AddMoveBy(0.1f, Vec3(2.5f, 0, 0));
		PtrAction->SetLooped(true);
		//アクション開始
		PtrAction->Run();
	}
	void Cloud_Small::OnUpdate() {
		auto PtrAction = AddComponent<Action>();
		auto trans = GetComponent<Transform>();
		auto pos = trans->GetPosition();
		if (pos.x >= 1200.0f) {
			PtrAction->AddMoveTo(0.000001f, Vec3(-1200.0f, pos.y, 0.0f));
			PtrAction->AddMoveTo(45.0f, Vec3(1200.0f, pos.y, 0.0f));
		}
	}


	void Title_Kai::OnCreate() {
		Draw();
	}
	void Title_Kai::OnUpdate() {
		auto PtrAction = AddComponent<Action>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		time += elapsedTime;
		PtrAction->AddRotateBy(3.0f, Vec3(0.0f, 0.0f, XM_PI));

		PtrAction->SetLooped(true);
		if (time >= 2.0f) {
			PtrAction->Run();

		}
		if (time >= 3.0f) {
			PtrAction->Stop();
			time = 0;
		}
	}

	void Result_Star1::OnCreate() {
		SetDrawActive(false);

		Draw();	
	}
	void Result_Star1::OnUpdate() {	
		auto PtrAction = AddComponent<Action>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		time += elapsedTime;


		PtrAction->AddScaleTo(0.3f, Vec3(1.0f));

		if (time >= 1.0f) {

			SetDrawActive(true);
			PtrAction->Run();

		}


	}

	void Result_Star2::OnCreate() {
		SetDrawActive(false);

		Draw();
	}
	void Result_Star2::OnUpdate() {
		auto PtrAction = AddComponent<Action>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		time += elapsedTime;


		PtrAction->AddScaleTo(0.3f, Vec3(1.0f));

		if (time >= 2.0f) {

			SetDrawActive(true);
			PtrAction->Run();

		}


	}

	void Result_Star3::OnCreate() {
		SetDrawActive(false);

		Draw();
	}
	void Result_Star3::OnUpdate() {
		auto PtrAction = AddComponent<Action>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		time += elapsedTime;


		PtrAction->AddScaleTo(0.3f, Vec3(1.0f));

		if (time >= 3.0f) {

			SetDrawActive(true);
			PtrAction->Run();

		}


	}

	void Title_Arrow::OnCreate() {
		Draw();	
		auto PtrAction = AddComponent<Action>();
		auto pos = GetComponent<Transform>()->GetPosition();

		PtrAction->AddMoveTo(1.0f, Vec3(pos.x, -250.0f, 0.0f));
		PtrAction->AddMoveTo(1.0f, Vec3(pos.x, -280.0f, 0.0f));
		PtrAction->SetLooped(true);
		PtrAction->Run();

	}
	void Title_Arrow::OnUpdate() {

	}

	


	void StageSelect_ArrowRight::SetTexture(const wstring& textures) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetTextureResource(textures);

	}
	void StageSelect_ArrowRight::OnCreate() {
		
		Draw();
		auto PtrAction = AddComponent<Action>();
		PtrAction->AddMoveTo(1.0f, Vec3(680.0f, 0.0f, 0.0f));
		PtrAction->AddMoveTo(1.0f, Vec3(650.0f, 0.0f, 0.0f));
		PtrAction->SetLooped(true);

		PtrAction->Run();


	}

	void StageSelect_ArrowLeft::SetTexture(const wstring& textures) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetTextureResource(textures);

	}
	void StageSelect_ArrowLeft::OnCreate() {

		Draw();
		auto PtrAction = AddComponent<Action>();
		PtrAction->AddMoveTo(1.0f, Vec3(-680.0f, 0.0f, 0.0f));
		PtrAction->AddMoveTo(1.0f, Vec3(-650.0f, 0.0f, 0.0f));
		PtrAction->SetLooped(true);

		PtrAction->Run();


	}


	void StageSlect_Star::SetTexture(const wstring& textures) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetTextureResource(textures);

	}
	void StageSlect_Star::OnCreate() {

		Draw();


	}

}
