#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../Object.h"
SpriteComponent::SpriteComponent()
{

	
}


SpriteComponent::~SpriteComponent()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void SpriteComponent::Init() {
	

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

	// Setting Up the Base of my MVP Matrix
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(320.0f, 240.0f, 0.f));
	projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
	
	//Setting Locations of Uniforms
	viewLoc = glGetUniformLocation(1, "view");
	projectionLoc = glGetUniformLocation(1, "projection");

	//Upload the view and projection matrix to the GPU
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//Generating the Vertex Arrays for the Sprite
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::Position));

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::TexCoord));

	glBindVertexArray(0);
}
void SpriteComponent::FixedUpdate(float dt) {

}
ComponentType SpriteComponent::GetType()
{
	return ComponentType::Renderer;
}
void SpriteComponent::Update(float dt) {
	Draw(dt);
	
}
void SpriteComponent::Draw(float dt) {

	if (tex) { tex->Use(); };

	glBindVertexArray(VAO);


	unsigned int modelLoc = glGetUniformLocation(1, "model");;
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(Owner->GetComponent<TransformComponent>(Transform)->position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * Owner->GetComponent<TransformComponent>(Transform)->scale.x, 0.5f * Owner->GetComponent<TransformComponent>(Transform)->scale.y, 0.0f));
	model = glm::rotate(model, Owner->GetComponent<TransformComponent>(Transform)->rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * Owner->GetComponent<TransformComponent>(Transform)->scale.x, -0.5f * Owner->GetComponent<TransformComponent>(Transform)->scale.y, 0.0f));

	model = glm::scale(model, glm::vec3(Owner->GetComponent<TransformComponent>(Transform)->scale, 1.0f));


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);

}