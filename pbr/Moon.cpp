#include "Moon.h"

#include <string>

static const std::string s_TexRes = "2k";

static std::string fullTextureName(std::string textureName)
{
	return "textures/" + textureName + "_" + s_TexRes + ".jpg";
}

MoonMaterial::MoonMaterial()
{
	program->attach(new Shader{ ShaderType::VERTEX, "shaders/bumpmap_vert.glsl" });
	program->attach(new Shader{ ShaderType::FRAGMENT, "shaders/bumpmap_frag.glsl" });
	program->link();

	MoonTexture		= std::make_shared<Texture>(fullTextureName("moon"));
	MoonBumpTexture = std::make_shared<Texture>(fullTextureName("moon_bump"));
}

void MoonMaterial::bind()
{
	program->bind();

	glActiveTexture(GL_TEXTURE0);
	MoonTexture->bind();

	glActiveTexture(GL_TEXTURE1);
	MoonBumpTexture->bind();

	program->setUniform("DiffuseTexture", 0);
	program->setUniform("BumpMapTexture", 1);
}

Moon::Moon(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh)
{
	MoonMesh = mesh;
	MoonMat = std::make_shared<MoonMaterial>();
	Radius = radius;

	transform.scale = glm::vec3{ radius };
	transform.translation = position;
	transform.rotation = glm::vec3{ glm::radians(90.0f), 0.0f, 0.0f };
}

void Moon::draw()
{
	MoonMat->bind();
	MoonMat->bindParams(materialParams);
	MoonMesh->draw();
}