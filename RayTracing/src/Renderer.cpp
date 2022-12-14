#include "Renderer.h"
#include "Walnut/Random.h"

void Renderer::Render()
{
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			glm::vec2 coord = {(float) x /(float) m_FinalImage->GetWidth() , (float)y/(float) m_FinalImage->GetHeight()};
			coord = coord * 2.0f - 1.0f; // 0 -> 1 --> -1 -> 1 
			m_ImageData[ x + y * m_FinalImage->GetWidth() ]  =  PerPixel(coord);
			
		}
	}
	m_FinalImage->SetData(m_ImageData);
}

uint32_t Renderer::PerPixel(glm::vec2 coord)
{
	uint8_t r = (uint8_t)(coord.x * 255.0f);
	uint8_t g = (uint8_t)(coord.y * 255.0f);
	float radius = 0.5f;

	glm::vec3 RayOrigin(0.0f,0.0f,2.0f);
	glm::vec3 RayDirection(coord.x, coord.y, -1.0f);

	//RayDirection = glm::normalize(RayDirection);

	// a = Ray origin 
	// b = Ray direction 
	// r = rudius
	// t = hit distance 

	float a = glm::dot(RayDirection, RayDirection); //RayDirection.x * RayDirection.x + RayDirection.y * RayDirection.y + RayDirection.z * RayDirection.z;
	float b = 2.0f * glm::dot(RayOrigin, RayDirection);
	float c = glm::dot(RayOrigin, RayOrigin) - radius * radius;
	float discriminant = b * b - 4.0f * a * c;

	if (discriminant >= 0.0f)
	{
		return 0xffff00ff;
	}
	else
	{
		return 0xff000000;
	}
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{	
	if (m_FinalImage)
	{	// no resize necessery
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;
		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}
	
	delete[]m_ImageData;
	m_ImageData = new uint32_t[width * height];



}
