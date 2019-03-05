#include "Sprite.h"
#include "../Game.h"

float floatvertices[] = {
	// first triangle
	 0.5f,  0.5f,   // top right
	 0.5f, -0.5f,   // bottom right
	-0.5f,  0.5f,   // top left 
	// second triangle
	 0.5f, -0.5f,   // bottom right
	-0.5f, -0.5f,   // bottom left
	-0.5f,  0.5f,   // top left
};


float texCoords[] = {
 1.0f, 1.0f,  
 1.0f, 0.0f,  
 0.0f, 1.0f,  
 1.0f, 0.0f,  
 0.0f, 0.0f,  
 0.0f, 1.0f   
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
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
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
	
	// Setting Up sprite moving with Box2D Body Position
	if (body) {
		//position = glm::vec2(Game::lerp(position.x, body->GetPosition().x * Game::kPixelsPerMeter, 0.016f), Game::lerp(position.y, body->GetPosition().y * Game::kPixelsPerMeter, 0.016f));
		position = glm::vec2(body->GetPosition().x * Game::kPixelsPerMeter, body->GetPosition().y * Game::kPixelsPerMeter);
	}

	if (tex)tex->Use();

	glBindVertexArray(VAO);


	unsigned int modelLoc = glGetUniformLocation(1, "model");;
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

	model = glm::scale(model, glm::vec3(scale, 1.0f));


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void Sprite::Draw(float dt)
{
	// Setting Up sprite moving with Box2D Body Position
	if (body) {
	//	position = glm::vec2(Game::lerp(position.x, body->GetPosition().x * Game::kPixelsPerMeter, dt), Game::lerp(position.y, body->GetPosition().y * Game::kPixelsPerMeter, dt));
	//position = glm::vec2(body->GetPosition().x * Game::kPixelsPerMeter, body->GetPosition().y * Game::kPixelsPerMeter);
		position = smoothedposition * Game::kPixelsPerMeter;
	}

	if (tex)tex->Use();

	glBindVertexArray(VAO);


	unsigned int modelLoc = glGetUniformLocation(1, "model");;
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
void Sprite::InitPhysics(bool movable)
{

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / Game::kPixelsPerMeter, position.y / Game::kPixelsPerMeter);
	bodyDef.fixedRotation = true;
	body = Game::GetWorld()->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(
		(scale.x / 2.f) / Game::kPixelsPerMeter,
		(scale.y / 2.f ) / Game::kPixelsPerMeter);
	b2FixtureDef fixtureDef;
	body->SetType(movable ? b2_dynamicBody : b2_staticBody);
	fixtureDef.shape = &shape;
	fixtureDef.density = 12.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = .4f;
	body->CreateFixture(&fixtureDef);
}
Sprite::~Sprite()
{

}
