#pragma once

#include "Interface.h"
#include "InterfaceSprite.h"
#include "InterfaceText.h"
#include "TextureId.h"

class PanelInterface : public Interface
{
public:
	PanelInterface(
		const sf::Vector2f &centerPosition,
		const sf::String &titleString,
		TextureId panelTextureId);

	virtual ~PanelInterface() = default;

	virtual void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override = 0;
protected:
	InterfaceText titleText_;
	InterfaceSprite panelSprite_;
};