#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"
#include "Material.h"
#include "Point.h"
#include "Reflection.h"

struct Light {
	Point position;
	Color intensity;
};

constexpr Light pointLight(Point const & point, Color const & intensity) {
	return {point, intensity};
}

constexpr Color ambient(Color const & effectiveColor, Material const & material) {
	return effectiveColor * material.ambient;
}

constexpr Color diffuse(Color const & effectiveColor, Material const & material, Light const & light, Point const & position, Direction const & normal) {
	auto const lightDirection = normalize(light.position - position);
	auto const lightDotNormal = dot(lightDirection, normal);
	if (lightDotNormal < 0.0) {
		return Colors::black;
	}
	return effectiveColor * material.diffuse * lightDotNormal;
}

constexpr Color specular(Material const & material, Light const & light, Point const & position, Direction const & eye, Direction const & normal) {
	auto const lightDirection = normalize(light.position - position);
	auto const lightDotNormal = dot(lightDirection, normal);
	if (lightDotNormal < 0.0) {
		return Colors::black;
	}
	auto const reflectDirection = reflect(-lightDirection, normal);
	auto const reflectDotEye = dot(reflectDirection, eye);
	if (reflectDotEye <= 0.0) {
		return Colors::black;
	}
	auto const factor = std::pow(reflectDotEye, material.shininess);
	return light.intensity * material.specular * factor;
}

constexpr Color lighting(Material const & material, Light const & light, Point const & position, Direction const & eye, Direction const & normal) {
	auto const effectiveColor = material.color * light.intensity;
	auto const ambientColor = ambient(effectiveColor, material);
	auto const diffuseColor = diffuse(effectiveColor, material, light, position, normal);
	auto const specularColor = specular(material, light, position, eye, normal);
	return ambientColor + diffuseColor + specularColor;
}



#endif /* LIGHT_H_ */
