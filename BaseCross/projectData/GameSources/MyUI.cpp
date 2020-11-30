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

		PtrAction->AddMoveBy(0.1f, Vec3(10.0f, 0, 0));

		PtrAction->SetLooped(true);
		//アクション開始
		PtrAction->Run();
	}
	void Cloud::OnUpdate() {


	}
}
