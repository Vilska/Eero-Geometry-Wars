#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Math.h"

namespace Eero {

	struct TransformComponent
	{
		Vec2 Pos = { 0.0f, 0.0f };
		Vec2 Velocity = { 0.0f, 0.0f };
		float Angle = 0.0f;

		TransformComponent(const Vec2& pos, const Vec2& velocity, float angle)
			: Pos(pos), Velocity(velocity), Angle(angle) {}
	};

	struct ShapeComponent
	{
		sf::CircleShape Circle;

		ShapeComponent(float radius, int points, const Vec3& fillColor, const Vec3& outlineColor, float thickness)
			: Circle(radius, points)
		{
			Circle.setFillColor(sf::Color(fillColor.x, fillColor.y, fillColor.z));
			Circle.setOutlineColor(sf::Color(outlineColor.x, outlineColor.y, outlineColor.z));
			Circle.setOutlineThickness(thickness);
			Circle.setOrigin(radius, radius);
		}

		int GetPointCount()
		{
			return Circle.getPointCount();
		}

		const Vec3& GetFillColor()
		{
			return { (float)Circle.getFillColor().r, (float)Circle.getFillColor().g, (float)Circle.getFillColor().b };
		}

		const Vec3& GetOutlineColor()
		{
			return { (float)Circle.getOutlineColor().r, (float)Circle.getOutlineColor().g, (float)Circle.getOutlineColor().b };
		}
	};

	struct CollisionComponent
	{
		float Radius = 0.0f;
		bool Handled = false;

		CollisionComponent(float radius)
			: Radius(radius) {}
	};

	struct LifespanComponent
	{
		int TotalTime, ActionTime = 0;

		enum class EffectTypes
		{
			Disappear = 0, Fade = 1, Blink = 2
		};

		EffectTypes Effect = EffectTypes::Disappear;

		LifespanComponent(int total, int action, LifespanComponent::EffectTypes effect)
			: TotalTime(total), ActionTime(action), Effect(effect) {}

	};

	struct TextComponent
	{
		sf::Text Text;
		sf::Font Font;

		TextComponent(const std::string& fontPath, const std::string& text, const Vec2& position, const Vec3& color, int size)
		{
			// Font
			Font.loadFromFile(fontPath);

			// Text
			Text.setFont(Font);
			Text.setString(text);
			Text.setPosition(sf::Vector2(position.x, position.y));
			Text.setFillColor(sf::Color(color.x, color.y, color.z));
			Text.setCharacterSize(size);
		}

		void SetText(const std::string& text)
		{
			Text.setString(text);
		}
	};

}
