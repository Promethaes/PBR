#include "MainScene.h"

MainScene::MainScene(bool yn)
	:Scene(yn), _in(true, std::nullopt)
{
}

bool MainScene::init()
{
	_lights.push_back({ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f) });
	_lights.push_back({ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) });

	_pbr = new Cappuccino::Shader(std::string("PBR"), "PutridButtRum.vert", "PutridButtRum.frag");
	_test = new Empty(*_pbr, { new Cappuccino::Texture("aAlb","marksmanRifle/marksmanRifle-Diffuse.png",Cappuccino::TextureType::PBRAlbedo),
		new Cappuccino::Texture("aEmis","marksmanRifle/marksmanRifle-Emission.png",Cappuccino::TextureType::EmissionMap),
		new Cappuccino::Texture("aNorm","marksmanRifle/marksmanRifle-Normal.png",Cappuccino::TextureType::NormalMap),
		new Cappuccino::Texture("aMetal","marksmanRifle/marksmanRifle-Metallic.png",Cappuccino::TextureType::PBRMetallic),
		new Cappuccino::Texture("aRough","marksmanRifle/work.png",Cappuccino::TextureType::PBRRoughness),
		new Cappuccino::Texture("aRoughe","marksmanRifle/marksmanRifle-AO.png",Cappuccino::TextureType::PBRAmbientOcc)
		}, { new Cappuccino::Mesh("marksmanRifle","marksmanRifle.obj") });
	_test->setActive(true);

	_pbr->use();
	_pbr->setUniform("material.albedo", (int)Cappuccino::TextureType::PBRAlbedo);
	_pbr->setUniform("material.normalMap", (int)Cappuccino::TextureType::NormalMap);
	_pbr->setUniform("material.metallic", (int)Cappuccino::TextureType::PBRMetallic);
	_pbr->setUniform("material.roughness", (int)Cappuccino::TextureType::PBRRoughness);
	_pbr->setUniform("material.ambientOcc", (int)Cappuccino::TextureType::PBRAmbientOcc);
	_pbr->setUniform("material.emission", (int)Cappuccino::TextureType::EmissionMap);
	_pbr->setUniform("numLights", (int)_lights.size());

	for (unsigned i = 0; i < _lights.size(); i++) {
		_lights[i]._isActive = true;
		_pbr->setUniform("lights[" + std::to_string(i) + "].position", _lights[i]._pos);
		_pbr->setUniform("lights[" + std::to_string(i) + "].colour", _lights[i]._col);
		_pbr->setUniform("lights[" + std::to_string(i) + "].active", (int)_lights[i]._isActive);

	}
	_pbr->loadProjectionMatrix(1600.0f, 1000.0f);
	_pbr->loadViewMatrix(c);

	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	return true;
}

bool MainScene::exit()
{
	return true;
}

void MainScene::childUpdate(float dt)
{
	//calculate camera movement
	auto moveForce = glm::vec3(0.0f, 0.0f, 0.0f);
	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::W))
		moveForce += glm::vec3(c.getFront().x, 0.0f, c.getFront().z);
	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::S))
		moveForce -= glm::vec3(c.getFront().x, 0.0f, c.getFront().z);

	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::A))
		moveForce -= glm::vec3(c.getRight().x, 0.0f, c.getRight().z);
	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::D))
		moveForce += glm::vec3(c.getRight().x, 0.0f, c.getRight().z);

	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::LEFT_CONTROL))
		moveForce -= glm::vec3(0.0f, 1.0f, 0.0f);
	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::SPACE))
		moveForce += glm::vec3(0.0f, 1.0f, 0.0f);


	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::LEFT_ARROW))
		_test->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90 * dt);
	else if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::RIGHT_ARROW))
		_test->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90 * -dt);
	else if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::RIGHT_CONTROL)) {

		if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::LEFT_ARROW))
			_test->_transform.rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90 * dt);
		if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::RIGHT_ARROW))
			_test->_transform.rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90 * -dt);
	}

	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::UP_ARROW))
		_test->_transform.rotate(glm::vec3(0.0f, 0.0f, 1.0f), 90 * dt);
	if (_in.keyboard->keyPressed(Cappuccino::KeyEvent::DOWN_ARROW))
		_test->_transform.rotate(glm::vec3(0.0f, 0.0f, 1.0f), 90 * -dt);


	float speed = 1.5f;
	moveForce *= speed;

	c.setPosition(c.getPosition() + moveForce * dt);

	_pbr->use();
	_pbr->loadViewMatrix(c);
	static float elapsedTime = 0.0f;
	elapsedTime += dt;
}

void MainScene::mouseFunction(double xpos, double ypos)
{
	static bool firstMouse = true;
	static float lastX = 400, lastY = 500;
	static float yaw = -90.0f;
	static float pitch = 0.0f;
	if (firstMouse)
	{
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	c.doMouseMovement(xOffset, yOffset);
}

Empty::Empty(Cappuccino::Shader& SHADER, const std::vector<Cappuccino::Texture*>& textures, const std::vector<Cappuccino::Mesh*>& meshes)
	:GameObject(SHADER, textures, meshes)
{
}

void Empty::childUpdate(float dt)
{
	//_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), dt);
}

PointLight::PointLight(const glm::vec3& position, const glm::vec3& colour)
	:_pos(position), _col(colour)
{
}
