#pragma once
#include "Cappuccino/SceneManager.h"

class MainScene : public Cappuccino::Scene {
public:
	MainScene(bool yn);

	bool init() override;
	bool exit() override;

	void childUpdate(float dt) override;

	void mouseFunction(double xpos, double ypos) override;

};