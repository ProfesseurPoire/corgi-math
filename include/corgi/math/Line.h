#pragma once

#include <corgi/math/Vec3.h>

namespace corgi::math
{
	
	/// LineGeometry repr�sente une droite "math�matiquement" Pour rappel, l'�quation cart�sienne
	/// d'une droite est ax+by+c=0 
	/// 
	/// Quant � l'�quation param�trique, elle s'exprime de la mani�re suivante : 
	/// X = at + Xa
	/// Y = bt + Ya
	/// Z = ct + Za
	class Line
	{
	public:

	// Lifecycle

		// On d�finit les param�tres de la courbe � partir d'un point dans l'espace et de son vecteur directeur
		Line(Vec3 point, Vec3 directeur) 
		{
			m_point			= point;
			m_direction		= directeur.normalized();
		}

		// On d�finit directement les coefficients de l'�quation cart�sienne
		Line(float a, float b, float c) 
		{
			m_a = a;
			m_b = b;
			m_c = c;
			m_isCartesienne = true;
		}

	// Functions

		// Retourne le coefficient a de la droite ax+by+c=0
		float a() 
		{
			return m_a;
		}

		// Retourne le coefficent b de la droite ax+by+c=0
		float b() {
			return m_b;
		}

		// Retourne le coefficient c de la droite ax+by+c=0
		float c() {
			return m_c;
		}

		// Si la droite � �t� d�fini de mani�re param�trique, retourne le point P
		Vec3 point() {
			if (m_isCartesienne)
				return Vec3::zero;
			return m_point;
		}

		Vec3 direction() {
			if (m_isCartesienne)
				return Vec3::zero;
			return m_direction;
		}

	private:

		// Variables
				
		// Permet de savoir si la droite � �t� d�terminer de mani�re cart�sienne ou non
		bool m_isCartesienne;

		
		// Coefficients de l'�quation cart�sienne
		float m_a;
		float m_b;
		float m_c;

		Vec3 m_point;
		Vec3 m_direction;
	};

}