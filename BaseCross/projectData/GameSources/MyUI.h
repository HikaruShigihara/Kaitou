#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_Base :public GameObject {
		Vec2 m_Vertex;
		float m_size;
		Vec3 m_pos;
		Vec3 m_scale;
		Col4 m_color;
		int m_layer;
		wstring m_textures;

	public:

		UI_Base(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			GameObject(StagePtr),
			m_Vertex(vertex),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer),
			m_color(color),
			m_textures(textures)

		{}
		~UI_Base() {}
		void Draw();

	};

	class Title_UI : public UI_Base {
	public:

		Title_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Title_UI() {}

		virtual void OnCreate() override;

	};


	class StageSelect_UI : public UI_Base {
	public:

		StageSelect_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~StageSelect_UI() {}

		virtual void OnCreate() override;

	};

	class Result_UI : public UI_Base {
	public:

		Result_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Result_UI() {}

		virtual void OnCreate() override;
	};

	class Game_Back : public UI_Base {
	public:

		Game_Back(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Game_Back() {}

		virtual void OnCreate() override;
	};
	class Clear : public UI_Base {
	public:

		Clear(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Clear() {}

		virtual void OnCreate() override;
	};

	class Number_UI : public GameObject {
		int m_place;	//à 
		int m_Score;	//êîéö
		std::vector<VertexPositionColorTexture> vertices;
		std::vector<uint16_t> indices;

		Vec2 m_vertex;
		float m_size;
		Vec3 m_pos;
		Vec3 m_scale;
		Col4 m_color;
		int m_layer;
		wstring m_textures;


	public:
		Number_UI(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures,
			int place,
			int score

		)
			: GameObject(StagePtr),
			m_vertex(vertex),
			m_pos(pos),
			m_scale(scale),
			m_layer(layer),
			m_color(color),
			m_textures(textures),
			m_place(static_cast<int>(place)),
			m_Score(score)

		{
		}
		~Number_UI() {}


		void OnCreate() override;
		void OnUpdate2() override;

		int GetCount() {
			return m_Score;
		}
	};

	class Cloud : public UI_Base {
	public:

		Cloud(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Cloud() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class Title_Kai : public UI_Base {
		float time;
	public:

		Title_Kai(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Title_Kai() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class Result_Star1 : public UI_Base {
		float time;
	public:

		Result_Star1(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Result_Star1() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	class Result_Star2 : public UI_Base {
		float time;
	public:

		Result_Star2(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Result_Star2() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class Result_Star3 : public UI_Base {
		float time;
	public:

		Result_Star3(const shared_ptr<Stage>& StagePtr,
			const Vec2& vertex,
			const Vec3& pos,
			const Vec3& scale,
			const int& layer,
			const Col4& color,
			const wstring& textures
		) :
			UI_Base(
				StagePtr,
				vertex,
				pos,
				scale,
				layer,
				color,
				textures
			)
		{}
		~Result_Star3() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}