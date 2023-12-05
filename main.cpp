#include <main.hpp>

int main(int argc, char **argv) {
	if (argc < 2) {
		return (1);
	}
	Parser *parser = new Parser();
	std::vector<DotObj*> objectList = parser->parseFile(argv[1]);
	if (objectList.size() == 0) {
		return (1);
	}

	Window *window = new Window(objectList[0]->getName().c_str(), DrawMode::FILL);

	InputHandler *inputHandler = new InputHandler(window->getWindow());
	Game *game = new Game();
	inputHandler->addCallback((I_Input*)game);
	inputHandler->addCallback((I_Input*)window);

	Texture texture = TextureLoader::loadTexture("../resources/wall.jpg");

	Shader *shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
	shader->use();

	VertexArrayObjectHandler *vertexArrayObjectHandler = new VertexArrayObjectHandler();

	VertexArrayObject *vertexArrayObject = new VertexArrayObject(objectList[0]->getVertices(VertexType::TEXTURED), objectList[0]->getIndexes());
	vertexArrayObject->addVertexAttribute(0,3,GL_FLOAT);
	vertexArrayObject->addVertexAttribute(1,2,GL_FLOAT);
	u_int texturedVAO = vertexArrayObjectHandler->AddVAO(vertexArrayObject);

	vertexArrayObject = new VertexArrayObject(vertexArrayObjectHandler->GetVAO(texturedVAO)->GetEBO(), objectList[0]->getVertices(VertexType::DEFAULT));
	vertexArrayObject->addVertexAttribute(0,3,GL_FLOAT);
	u_int defaultVAO = vertexArrayObjectHandler->AddVAO(vertexArrayObject);

	while(window->ShouldContinue())
	{
		inputHandler->handleInput();
		window->Clear();
		if (game->getIsTextureApplied()) {
			vertexArrayObjectHandler->Bind(texturedVAO);
		}
		else {
			vertexArrayObjectHandler->Bind(defaultVAO);
		}

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)DEFAULT_WINDOW_WIDTH/(float)DEFAULT_WINDOW_HEIGHT, 0.1f, 100.0f);
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = proj * glm::translate(matrix, game->getObjectPosition()) * glm::toMat4(game->getObjectQuaternion()) * objectList[0]->getCenterMatrix();
		shader->setmat4("proj", matrix);

		vertexArrayObjectHandler->Draw();
		window->SwapBuffersAndPollEvents();
	}
	return 0;
}