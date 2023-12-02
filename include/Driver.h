#pragma once

class DriverState;
class EventQueue;

#include "DriverInterface.h"
#include "DriverStateType.h"
#include "SoundPool.h"

class Driver :
	public DriverInterface,
	public Listener
{
public:
	Driver();

	~Driver();

	void onEvent(const Event &ev) override;

	void update(float deltaTime) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMouseWheelScroll(float delta) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnMouseButtonRelease(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;

	bool isDone() const;

	void draw(
		sf::RenderTarget &target,
		sf::RenderStates states) const override;
private:
	EventQueue &eventQueue_;

	DriverState *state_;

	SoundPool soundPool_;

	bool isDone_;

	void changeState_(DriverStateType stateType);
};