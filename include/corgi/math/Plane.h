#pragma once

#include <corgi/math/vec3.h>
#include <corgi/math/Line.h>

namespace  corgi::math
{
	// Represents a plane in mathematics. A plane is defined by a point P and 2 direction vector u,v. Or by a point P and
	// the normal to the plane.
	class Plane 
	{

	public:

		// Construction d'un plan � partir d'un point dans l'espace et de 2 vecteurs directeurs.
		// La normale du plan sera construite � partir d'un produit vectoriel des 2 vecteurs directeurs
		Plane(vec3 point, vec3 tangent, vec3 bitangent) 
		{
			m_point		= point;
			m_tangent	= tangent.normalized();
			m_bitangent = bitangent.normalized();
			m_normal	= m_tangent.cross(m_bitangent).normalized();
			compute_coefficients();
		}

		// Construction d'un plan � partir d'un point dans l'espace et de sa normale
		Plane(vec3 point, vec3 normal) 
		{
			m_point = point;
			m_normal = normal;
			compute_coefficients();
		}

	// Functions

		// Calcul le point d'intersection entre la droite et le plan. Pour se faire, 
		// On prend l'�quation ax+by+cz+d = 0 du plan, et on remplace x,y,z par les valeurs 
		// diff�rentes composantes de l'�quation param�trique de la droite 
		vec3 line_intersection(Line line) {

			float denom = line.direction().x * m_a + line.direction().y * m_b + line.direction().z * m_c;

			// non Colinarit�
			if (denom != 0)
			{
				float t = -line.point().x * m_a - line.point().y * m_b - line.point().z * m_c - m_d;
				t = t / denom;

				return vec3(
					line.point().x + t * line.direction().x,
					line.point().y + t * line.direction().y,
					line.point().z + t * line.direction().z
				);
			}

			// Dans le cas assez improbable ou la droite et le plan serait colin�aire, on renvoit le point 
			// d�finit dans la droite
			return line.point();
		}

	private:

	// Functions

		void compute_coefficients() 
		{
			m_a		= m_normal.x;
			m_b		= m_normal.y;
			m_c		= m_normal.z;
			m_d		= -(m_point.x * m_a + m_point.y * m_b + m_point.z * m_c);
		}

	// Variables

		// Coefficients de l'�quation du plan ax+by+cz+d=0

		float m_a;
		float m_b;
		float m_c;
		float m_d;

		vec3 m_point;
		vec3 m_normal;
		vec3 m_tangent;
		vec3 m_bitangent;

		// On recherche l'�quation du plan du triangle, on a besoin de la normale pour se faire
		// Rappel, �quation du plan : ax+by+cz+d=0
	};
}