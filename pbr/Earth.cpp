#include "Earth.h"

static const std::string s_TexRes = "2k";

static std::string fullTextureName(std::string textureName)
{
	return "textures/" + textureName + "_" + s_TexRes + ".jpg";
}

EarthMaterial::EarthMaterial()
{
	program->attach(new Shader{ ShaderType::VERTEX, "shaders/ground_vert.glsl" });
	program->attach(new Shader{ ShaderType::FRAGMENT, "shaders/ground_frag.glsl" });
	program->link("EarthGround");

	EarthTexture			= std::make_shared<Texture>(fullTextureName("earth"));
	OceanMaskTexture		= std::make_shared<Texture>(fullTextureName("ocean_mask"));
	OceanIceTexture			= std::make_shared<Texture>(fullTextureName("earth_ocean_color"));
	EarthNightTexture		= std::make_shared<Texture>(fullTextureName("earth_night"));
	// EarthTopographyTexture	= std::make_shared<Texture>(fullTextureName("topography"));
	CloudsTexture			= std::make_shared<Texture>(fullTextureName("earth_clouds"));
}

void EarthMaterial::bind()
{
	program->bind();

	glActiveTexture(GL_TEXTURE0);
	EarthTexture->bind();

	glActiveTexture(GL_TEXTURE1);
	OceanMaskTexture->bind();

	glActiveTexture(GL_TEXTURE2);
	EarthNightTexture->bind();

	glActiveTexture(GL_TEXTURE3);
	// EarthTopographyTexture->bind();

	glActiveTexture(GL_TEXTURE4);
	OceanIceTexture->bind();

	glActiveTexture(GL_TEXTURE5);	
	CloudsTexture->bind();

	program->setUniform("EarthTexture", 0);
	program->setUniform("OceanMaskTexture", 1);
	program->setUniform("NightTexture", 2);
	program->setUniform("TopographyTexture", 3);
	program->setUniform("OceanTexture", 4);
	program->setUniform("CloudsTexture", 5);
}

void EarthMaterial::unbind()
{
	program->unbind();
}

AtmosphereMaterial::AtmosphereMaterial()
{
	program->attach(new Shader{ ShaderType::VERTEX, "shaders/sky_vert.glsl" });
	program->attach(new Shader{ ShaderType::FRAGMENT, "shaders/sky_frag.glsl" });
	program->link("EarthSky");
}

void AtmosphereMaterial::bind()
{
	program->bind();
}

void AtmosphereMaterial::unbind()
{
	program->unbind();
}

Earth::Earth(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh) :
	Drawable(mesh)
{
	EarthMesh = mesh;
	EarthSurfaceMaterial = std::make_shared<EarthMaterial>();
	EarthAtmosphereMaterial = std::make_shared<AtmosphereMaterial>();

	transform.Translation = position;
	transform.Scale = glm::vec3{ radius };
	transform.Rotation = glm::vec3{ glm::radians(90.0f), 0.0f, 0.0f };

	InnerRadius = radius;
	OuterRadius = InnerRadius * 1.025f;

	const float fScale = 1.0f / (OuterRadius - InnerRadius);
	const float PI = glm::pi<float>();

	materialParams.set("fOuterRadius", OuterRadius);
	materialParams.set("fOuterRadius2", OuterRadius * OuterRadius);
	materialParams.set("fInnerRadius", InnerRadius);
	materialParams.set("fScale", fScale);
	materialParams.set("fScaleDepth", RayleighScaleDepth);
	materialParams.set("fScaleOverScaleDepth", fScale / RayleighScaleDepth);
	materialParams.set("fKrESun", Kr * ESun);
	materialParams.set("fKmESun", Km * ESun);
	materialParams.set("fKr4PI", Kr * 4.0f * PI);
	materialParams.set("fKm4PI", Km * 4.0f * PI);
	materialParams.set("v3InvWavelength", 1.0f / glm::pow(WaveLength, glm::vec3{ 4.0f }));
}

void Earth::draw()
{	
	// First pass - Draw earth's surface
	{
		glFrontFace(GL_CCW);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		EarthSurfaceMaterial->bind();
		EarthSurfaceMaterial->bindParams(materialParams);

		EarthMesh->draw();
	}

	// Second pass - Draw earth's atmosphere
	{
		glFrontFace(GL_CW);
		glBlendFunc(GL_ONE, GL_ONE);

		EarthAtmosphereMaterial->bind();
		EarthAtmosphereMaterial->bindParams(materialParams);

		EarthMesh->draw();
	}

	// Restore OpenGL state
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}