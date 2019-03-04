#include "Sprite.h"


float floatvertices[] = {
	// first triangle
	 0.5f,  0.5f,   // top right
	 0.5f, -0.5f,   // bottom right
	-0.5f,  0.5f,   // top left 
	// second tria
	 0.5f, -0.5f,   // bottom right
	-0.5f, -0.5f,   // bottom left
	-0.5f,  0.5f,   // top left
};


float texCoords[] = {
 1.0f, 1.0f,   // top right};
 1.0f, 0.0f,   // bottom right
 0.0f, 1.0f,    // top left 
 1.0f, 0.0f,   // bottom right
 0.0f, 0.0f,   // bottom left
 0.0f, 1.0f    // top left 
};
Sprite::Sprite()
{
	position = glm::vec2(0, 0);
	scale = glm::vec2(100.0f, 100.0f);
	rotation = 0.f;

	vertices[0].Position = Vector2D(0.5f, 0.5f);
	vertices[1].Position = Vector2D(0.5f, -0.5f);
	vertices[2].Position = Vector2D(-0.5f, 0.5f);
	vertices[3].Position = Vector2D(0.5f, -0.5f);
	vertices[4].Position = Vector2D(-0.5f, -0.5f);
	vertices[5].Position = Vector2D(-0.5f, 0.5f);

	vertices[0].TexCoord = Vector2D(1.0f, 1.0f);
	vertices[1].TexCoord = Vector2D(1.0f, 0.0f);
	vertices[2].TexCoord = Vector2D(0.0f, 1.0f);
	vertices[3].TexCoord = Vector2D(1.0f, 0.0f);
	vertices[4].TexCoord = Vector2D(0.0f, 0.0f);
	vertices[5].TexCoord = Vector2D(0.0f, 1.0f);
	tex = nullptr;
}
void Sprite::Init() {

	model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(100, 100, 100));
	view = glm::translate(view, glm::vec3(320.0f, 240.0f, 0.f));
	projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
	// retrieve the matrix uniform locations
	viewLoc = glGetUniformLocation(1, "view");
	projectionLoc = glGetUniformLocation(1, "projection");

	
	// pass them to the shaders (3 different ways)
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex,Vertex::Position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::TexCoord));
	
	glBindVertexArray(0);
}
void Sprite::Draw() {

	glBindVertexArray(VAO);
	unsigned int modelLoc = glGetUniformLocation(1, "model");;
	if (tex)tex->Use();

	//glm::mat4 localm = glm::mat4(1.0f);
	//localm = glm::scale(localm, glm::vec3(scale, 0.0f));
	//localm = glm::translate(localm, glm::vec3(position.x / scale.x , position.y / scale.y, 1.0f));
	//localm = glm::rotate(localm, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

	model = glm::scale(model, glm::vec3(scale, 1.0f));


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void Sprite::SetTexture(std::string path)
{
	tex = new Texture(path);
	tex->Init();
}
Sprite::~Sprite()
{

}
