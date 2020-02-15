#pragma once
#include "Cappuccino/SceneManager.h"
#include "Cappuccino/ShaderProgram.h"
#include "Cappuccino/GameObject.h"
#include "Cappuccino/CappInput.h"

class PointLight {
public:
	PointLight(const glm::vec3& position, const glm::vec3& colour);

	glm::vec3 _pos;
	glm::vec3 _col;
	bool _isActive = true;
};

class Empty : public Cappuccino::GameObject {
public:
	Empty(Cappuccino::Shader& SHADER, const std::vector<Cappuccino::Texture*>& textures, const std::vector<Cappuccino::Mesh*>& meshes);

	void childUpdate(float dt) override;
};

class MainScene : public Cappuccino::Scene {
public:
	MainScene(bool yn);

	bool init() override;
	bool exit() override;

	void childUpdate(float dt) override;

	void mouseFunction(double xpos, double ypos) override;
private:
	Cappuccino::CappInput _in;
	Cappuccino::Camera c;
	std::vector<PointLight> _lights;
	Cappuccino::Shader* _pbr;
	Empty* _test;

};