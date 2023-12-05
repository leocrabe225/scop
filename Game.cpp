#include <classes/Game.hpp>

Game::Game() {}

void Game::SendKeys(u_char *keyState) {
	if(keyState[KEY_MOVE_FORWARD] & KEY_HOLD)
        objectPosition += glm::vec3(0, 0, -speed);
    if(keyState[KEY_MOVE_BACKWARD] & KEY_HOLD)
        objectPosition += glm::vec3(0, 0, speed);
    if(keyState[KEY_MOVE_RIGHTWARD] & KEY_HOLD)
        objectPosition += glm::vec3(speed, 0, 0);
    if(keyState[KEY_MOVE_LEFTWARD] & KEY_HOLD)
        objectPosition += glm::vec3(-speed, 0, 0);
    if(keyState[KEY_MOVE_UPWARD] & KEY_HOLD)
        objectPosition += glm::vec3(0, speed, 0);
    if(keyState[KEY_MOVE_DOWNWARD] & KEY_HOLD)
        objectPosition += glm::vec3(0, -speed, 0);

	if(keyState[KEY_ENTER] & KEY_PRESS) {
		isTextureApplied = !isTextureApplied;
    }   

	if(keyState[KEY_ROTATE_X_NEGATIVE] & KEY_HOLD) {
        objectQuaternion = glm::angleAxis(-rotationSpeed, glm::vec3(1.0f, 0.0f, 0.0f)) * objectQuaternion;
    }
    if(keyState[KEY_ROTATE_X_POSITIVE] & KEY_HOLD) {
        objectQuaternion = glm::angleAxis(rotationSpeed, glm::vec3(1.0f, 0.0f, 0.0f)) * objectQuaternion;
    }  
    if(keyState[KEY_ROTATE_Y_NEGATIVE] & KEY_HOLD) {
        objectQuaternion = glm::angleAxis(-rotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)) * objectQuaternion;
    }
    if(keyState[KEY_ROTATE_Y_POSITIVE] & KEY_HOLD) {
        objectQuaternion = glm::angleAxis(rotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)) * objectQuaternion;
    }
    if(keyState[KEY_ROTATE_Z_NEGATIVE] & KEY_HOLD) {
        objectQuaternion = glm::angleAxis(rotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)) * objectQuaternion;
    }
    if(keyState[KEY_ROTATE_Z_POSITIVE] & KEY_HOLD) {
        objectQuaternion = glm::angleAxis(-rotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)) * objectQuaternion;
    }
}

bool Game::getIsTextureApplied() const {
    return isTextureApplied;
}

glm::quat Game::getObjectQuaternion() const {
    return objectQuaternion;
}

glm::vec3 Game::getObjectPosition() const {
    return objectPosition;
}

Game::~Game() {}