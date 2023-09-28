#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <numbers>

class Rocket : public olc::PixelGameEngine
{
public:
	Rocket()
	{
		sAppName = "Rocket";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	void HandleUserInput() 
	{
		if (GetKey(olc::UP).bHeld)
		{
			m_rocketVelocity = 40.;
		}
		else if (GetKey(olc::DOWN).bHeld)
		{
			m_rocketVelocity = -40.;
		}
		else
		{
			m_rocketVelocity = 0.;
		}

		if (GetKey(olc::LEFT).bHeld)
		{
			m_rocketAngleVelocity = -90. / 360. * 2. * std::numbers::pi;;
		}
		else if (GetKey(olc::RIGHT).bHeld)
		{
			m_rocketAngleVelocity = 90. / 360. * 2. * std::numbers::pi;;
		}
		else
		{
			m_rocketAngleVelocity = 0.;
		}
	}

	void DrawGame()
	{
		Clear(olc::BLACK);

		//Draw Rocket
		//
		//		       *   (0,0)
		//	          / \
		//  (-3,10)  /_*_\  (3,10)
		// 
		double lengthWing = std::sqrt(3 * 3 + 10 * 10);
		double angleWing = acos(10 / lengthWing);

		olc::vi2d pointTop( m_x, m_y );
		olc::vi2d pointLeft( m_x + lengthWing * cos(m_rocketAngle + angleWing), m_y + lengthWing * sin(m_rocketAngle + angleWing) );
		olc::vi2d pointRight(m_x + lengthWing * cos(m_rocketAngle - angleWing), m_y + lengthWing * sin(m_rocketAngle - angleWing) );
		olc::vi2d pointBottom(m_x + lengthWing * 0.8 * cos(m_rocketAngle), m_y + lengthWing * 0.8 * sin(m_rocketAngle));

		DrawLine(pointTop, pointLeft);
		DrawLine(pointTop, pointRight);
		DrawLine(pointBottom, pointLeft);
		DrawLine(pointBottom, pointRight);
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		HandleUserInput();

		m_rocketAngle += m_rocketAngleVelocity * fElapsedTime;

		m_x = m_x + m_rocketVelocity * fElapsedTime * -1 * cos(m_rocketAngle);
		m_y = m_y + m_rocketVelocity * fElapsedTime * -1 * sin(m_rocketAngle);
		DrawGame();
		return true;
	}


private:
	
	double m_x = 256 / 2;
	double m_y = 240 / 2;
	double m_rocketVelocity = 0.;

	double m_rocketAngle = 90. / 360. * 2. * std::numbers::pi;
	double m_rocketAngleVelocity = 0.;
};

int main()
{
	Rocket demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}
