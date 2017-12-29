#include "Game Engine/Render Classes/RenderModel.h"
#include "Game Engine/Render Classes/Shader.h"

void RenderModel::Load(std::string& location, std::string& preferredShader, int& elementCount, std::vector<int>& elementOrder, std::vector<float>& elementColours, std::vector<float>& elementCoordPoints, std::vector<float>& elementUVs) {

	int currentElement = -1, elementOrderCount = 0;

	//Check to see if file exists.
	std::ifstream modelStream = std::ifstream(location);
	if (modelStream.is_open()) {
		while (!modelStream.eof()) {

			//Get current line.
			std::string currentLine = "";
			std::getline(modelStream, currentLine);

			//Interpret tag.
			if (currentLine[0] == '[') {
				std::string tag = currentLine.substr(1, 4);
				std::string data = currentLine.substr(6, currentLine.length());

				if (tag == "shdr") {
					preferredShader = data;
				}
				else if (tag == "ptln") {
					elementCount = std::stoi(data);
					if (elementCount < 0) {
						elementCount = 0;
					}

					//Initialise the arrays.
					elementColours.resize(elementCount * 4);
					elementCoordPoints.resize(elementCount * 3);
					elementUVs.resize(elementCount * 2);
				}
				else if (tag == "dtpt") {
					currentElement = std::stoi(data);
					if (currentElement < 0) {
						std::cout << "Warning! Set negative vertex point. This will cause errors!\nModel (" << location << ")\n\n";
					}
					if (currentElement >= elementCount) {
						currentElement = -1;
						std::cout << "Warning! Vertex point exceeds bounds. Action ignored.\nModel (" << location << ")\n\n";
					}
				}
				else if (tag == "uv--") {
					if (currentElement < 0 || currentElement >= elementCount) {
						std::cout << "Attempted to set vertex when point is out of bounds!\nModel (" << location << ")\n\n";
					}
					//Set vertex uvs.
					std::stringstream dataStream = std::stringstream(data);
					std::string rawScalar = "";
					int scalarCount = 0;
					while (std::getline(dataStream, rawScalar, ',')) {
						if (scalarCount < 2) {
							elementUVs.at((currentElement * 2) + scalarCount) = std::stof(rawScalar);
							scalarCount++;
						}
					}
				}
				else if (tag == "vert") {
					if (currentElement < 0 || currentElement >= elementCount) {
						std::cout << "Attempted to set vertex when point is out of bounds!\nModel (" << location << ")\n\n";
					}
					//Set vertex co-ordinates.
					std::stringstream dataStream = std::stringstream(data);
					std::string rawScalar = "";
					int scalarCount = 0;
					while (std::getline(dataStream, rawScalar, ',')) {
						if (scalarCount < 3) {
							elementCoordPoints.at((currentElement * 3) + scalarCount) = std::stof(rawScalar);
							scalarCount++;
						}
					}
				}
				else if (tag == "rgba") {
					if (currentElement < 0 || currentElement >= elementCount) {
						std::cout << "Attempted to set vertex when point is out of bounds!\nModel (" << location << ")\n\n";
					}

					//Set vertex colour.
					std::stringstream dataStream = std::stringstream(data);
					std::string rawScalar = "";
					int scalarCount = 0;
					while (std::getline(dataStream, rawScalar, ',')) {
						if (scalarCount < 4) {
							elementColours.at((currentElement * 4) + scalarCount) = std::stof(rawScalar);
							scalarCount++;
						}
					}
				}
				else if (tag == "orct") {
					elementOrderCount = std::stoi(data);
					if (elementOrderCount < 0) {
						elementOrderCount = 0;
					}
					elementOrder.resize(elementOrderCount);
				}
				else if (tag == "ordr") {
					//Set element order.
					std::stringstream dataStream = std::stringstream(data);
					std::string rawScalar = "";
					int scalarCount = 0;
					while (std::getline(dataStream, rawScalar, ',')) {
						if (scalarCount < elementOrderCount) {
							elementOrder.at(scalarCount) = std::stoi(rawScalar);
							scalarCount++;
						}
					}
				}
			}
		}
		modelStream.close();
	}
}

RenderModel::RenderModel(std::string location) : preferredShaderTag(""), shaderRetrievalSuccessful(false) {

	int elementCount = -1;

	std::vector<int> elementOrder;

	std::vector<float> elementColours;
	std::vector<float> elementCoordPoints;
	std::vector<float> elementUVs;

	Load(location, this->preferredShaderTag, elementCount, elementOrder, elementColours, elementCoordPoints, elementUVs);	

	std::cout << "\nLoaded model. (" << location << ")\n";
	std::cout << "Preferred shader of model: " << preferredShaderTag << "\n";

	for (int i = 0; i < elementCount; i++) {
		std::cout << "-For point " << i + 1 << " of " << elementCount << ": \n";
		std::cout << "  X: " << elementCoordPoints[(i * 3) + 0] << ", Y: " << elementCoordPoints[(i * 3) + 1] << ", Z: " << elementCoordPoints[(i * 3) + 2] << "\n";
		std::cout << "  R: " << elementColours[(i * 4) + 0] << ", G: " << elementColours[(i * 4) + 1] << ", B: " << elementColours[(i * 4) + 2] << ", A: " << elementColours[(i * 4) + 3] << "\n";
		std::cout << "  U: " << elementUVs[(i * 2) + 0] << ", V: " << elementUVs[(i * 2) + 1] << "\n";
	}

	this->elementOrderCount = elementOrder.size();
	std::cout << "Through ElementBuffers, there are " << this->elementOrderCount << " total vertices.\n";


	//OPENGL CODE
	int totalSize = elementCoordPoints.size() + elementColours.size() + elementUVs.size();
	int strideLength = 9; //vec3 + vec4 + vec2
	this->data.clear();
	this->data.resize(totalSize);
	for (int i = 0; i < elementCount; i++) {
		this->data[(i * strideLength) + 0] = elementCoordPoints[(i * 3) + 0];
		this->data[(i * strideLength) + 1] = elementCoordPoints[(i * 3) + 1];
		this->data[(i * strideLength) + 2] = elementCoordPoints[(i * 3) + 2];
		this->data[(i * strideLength) + 3] = elementColours[(i * 4) + 0];
		this->data[(i * strideLength) + 4] = elementColours[(i * 4) + 1];
		this->data[(i * strideLength) + 5] = elementColours[(i * 4) + 2];
		this->data[(i * strideLength) + 6] = elementColours[(i * 4) + 3];
		this->data[(i * strideLength) + 7] = elementUVs[(i * 2) + 0];
		this->data[(i * strideLength) + 8] = elementUVs[(i * 2) + 1];
	}
	std::cout << "Finished translating data to accessable format for OpenGL.\n";

	GLuint VBO, EBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(float), &this->data[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementOrder.size() * sizeof(int), &elementOrder[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (strideLength * sizeof(float)), (void*)(sizeof(float) * 0));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, (strideLength * sizeof(float)), (void*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (strideLength * sizeof(float)), (void*)(sizeof(float) * 7));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

RenderModel::~RenderModel() {
}

GLuint RenderModel::getElementOrderCount() {
	return this->elementOrderCount;
}
GLuint RenderModel::getModelVAO() {
	return this->VAO;
}

GLuint RenderModel::getPreferredShader() {
	if (this->hasPreferredShader() && !this->shaderRetrievalSuccessful) {
		this->preferredShaderID = SHADER_REGISTER_EXTRN.at(this->preferredShaderTag)->getShaderProgramID();
		this->shaderRetrievalSuccessful = true;
	}
	if (this->shaderRetrievalSuccessful) {
		return this->preferredShaderID;
	}
	return NULL;
}

bool RenderModel::hasPreferredShader() {
	return (this->preferredShaderTag != "") && (!this->preferredShaderTag.empty());
}

void RenderModel::draw() {
	this->draw(this->getPreferredShader());
}

void RenderModel::draw(GLuint shaderID) {
	glUseProgram(shaderID);
	glBindVertexArray(this->getModelVAO());

	//glDrawElements(GL_TRIANGLES, this->getElementOrderCount(), GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, this->getElementOrderCount(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}