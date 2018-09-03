/*
Author: Cristina Barreiro Rodriguez
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#include "MathFunctions.h"

#include <SFML/Graphics.hpp>

unsigned int kWindowX = 800, kWindowY = 600;

const double fPI = 3.1415927;

using namespace sf;

struct Ship {
	struct Vec3 points[5];
	struct Vec3 points_transformed[5];
	struct Vec3 cannons_points[2];
	struct Vec3 cannons_points_transformed[4];
	struct Vec2 position;
	struct Vec2 velocity;
	struct Vec2 dimension;
	float cos, sin;
};
Ship player_ship;

struct MotherShip {
	struct Vec3 points[11];
	struct Vec3 points_transformed[11];
	//struct Vec3 wings_points[5];
	//struct Vec3 wings_points_transformed[5];
	struct Vec2 position;
	struct Vec2 dimension;
	float cos, sin;
};
MotherShip mother_ship;
struct Ring {
	int segments;
	int number_of_points;
	struct Vec2 *current_point;
	struct Vec2 *next_point;
};
Ring ring;

void InitShip() {
	/*
		Local points
	*/
	player_ship.points[0].x = 0;
	player_ship.points[0].y = 0;
	player_ship.points[0].z = 1;

	player_ship.points[1].x = -1;
	player_ship.points[1].y = 1;
	player_ship.points[1].z = 1;

	player_ship.points[2].x = 0;
	player_ship.points[2].y = -1;
	player_ship.points[2].z = 1;

	player_ship.points[3].x = 1;
	player_ship.points[3].y = 1;
	player_ship.points[3].z = 1;

	player_ship.points[4].x = player_ship.points[0].x;
	player_ship.points[4].y = player_ship.points[0].y;
	player_ship.points[4].z = player_ship.points[0].z;

	player_ship.cannons_points[0].x = 0.5f;
	player_ship.cannons_points[0].y = 1;
	player_ship.cannons_points[0].z = 1;

	player_ship.cannons_points[1].x = 0.5f;
	player_ship.cannons_points[1].y = -1;
	player_ship.cannons_points[1].z = 1;

	player_ship.position.x = 500;
	player_ship.position.y = 300;

	player_ship.dimension.x = 30;
	player_ship.dimension.y = 30;

	player_ship.cos = 1;
	player_ship.sin = 0;
}
void InitMotherShip() {
	/*
		Local points
	*/
	mother_ship.points[0].x = -0.5f;
	mother_ship.points[0].y = 0;
	mother_ship.points[0].z = 1;

	mother_ship.points[1].x = -1;
	mother_ship.points[1].y = -1;
	mother_ship.points[1].z = 1;

	mother_ship.points[2].x = -0.2f;
	mother_ship.points[2].y = -0.7f;
	mother_ship.points[2].z = 1;

	mother_ship.points[3].x = 0;
	mother_ship.points[3].y = -0.2f;
	mother_ship.points[3].z = 1;

	mother_ship.points[4].x = 0.8f;
	mother_ship.points[4].y = -0.2f;
	mother_ship.points[4].z = 1;

	mother_ship.points[5].x = 1;
	mother_ship.points[5].y = 0;
	mother_ship.points[5].z = 1;

	mother_ship.points[6].x = 0.8f;
	mother_ship.points[6].y = 0.2f;
	mother_ship.points[6].z = 1;

	mother_ship.points[7].x = 0;
	mother_ship.points[7].y = 0.2f;
	mother_ship.points[7].z = 1;

	mother_ship.points[8].x = -0.2f;
	mother_ship.points[8].y = 0.7f;
	mother_ship.points[8].z = 1;

	mother_ship.points[9].x = -1;
	mother_ship.points[9].y = 1;
	mother_ship.points[9].z = 1;

	mother_ship.points[10].x = mother_ship.points[0].x;
	mother_ship.points[10].y = mother_ship.points[0].y;
	mother_ship.points[10].z = mother_ship.points[0].z;

	/*mother_ship.wings_points[0].x = -1;
	mother_ship.wings_points[0].y = -1;
	mother_ship.wings_points[0].z = 1;

	mother_ship.wings_points[1].x = 0.6f;
	mother_ship.wings_points[1].y = -0.8f;
	mother_ship.wings_points[1].z = 1;

	mother_ship.wings_points[2].x = 1;
	mother_ship.wings_points[2].y = 1;
	mother_ship.wings_points[2].z = 1;

	mother_ship.wings_points[3].x = -0.6f;
	mother_ship.wings_points[3].y = 1;
	mother_ship.wings_points[3].z = 1;

	mother_ship.wings_points[4].x = mother_ship.wings_points[0].x;
	mother_ship.wings_points[4].y = mother_ship.wings_points[0].y;
	mother_ship.wings_points[4].z = mother_ship.wings_points[0].z;
	*/
	mother_ship.position.x = 400;
	mother_ship.position.y = 300;

	mother_ship.dimension.x = 30;
	mother_ship.dimension.y = 30;

	mother_ship.cos = 1;
	mother_ship.sin = 0;

}
void InitRing() {
	ring.segments = 12;
	ring.number_of_points = 4;
	ring.current_point = (Vec2*)malloc(ring.segments * ring.number_of_points * sizeof(Vec2));
	ring.next_point = (Vec2*)malloc(ring.segments * ring.number_of_points * sizeof(Vec2));

}
void Input() {
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		const float a = (fPI * 2) / 30;
		const float sa = sin(a);
		const float ca = cos(a);

		float s_next = player_ship.sin * ca + player_ship.cos * sa;
		float c_next = player_ship.cos * ca - player_ship.sin * sa;

		player_ship.sin = s_next;
		player_ship.cos = c_next;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		const float a = (fPI * 2) / 30;
		const float ca = cos(a);
		const float sa = sin(a);

		float s_next = player_ship.sin * ca - player_ship.cos * sa;
		float c_next = player_ship.cos * ca + player_ship.sin * sa;

		player_ship.sin = s_next;
		player_ship.cos = c_next;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		player_ship.velocity.x += player_ship.sin;
		player_ship.velocity.y += -player_ship.cos;
	}
}
void JoinLimits() {
	int coordinates_origin = 0;
	bool has_reach_right_border = player_ship.position.x >= kWindowX + player_ship.dimension.x;
	bool has_reach_left_border = player_ship.position.x <= coordinates_origin - player_ship.dimension.x;
	bool has_reach_top_border = player_ship.position.y >= kWindowY + player_ship.dimension.y;
	bool has_reach_bottom_border = player_ship.position.y <= coordinates_origin - player_ship.dimension.y;

	//Limit X
	if (has_reach_right_border) {
		player_ship.position.x = coordinates_origin - player_ship.dimension.x;
	}
	else if (has_reach_left_border) {
		player_ship.position.x = kWindowX + player_ship.dimension.x;
	}
	//Limit Y
	if (has_reach_top_border) {
		player_ship.position.y = coordinates_origin - player_ship.dimension.y;
	}
	else if (has_reach_bottom_border) {
		player_ship.position.y = kWindowY + player_ship.dimension.y;
	}

}
void MoveShipPlayer() {
	player_ship.position.x += player_ship.velocity.x;
	player_ship.position.y += player_ship.velocity.y;
}
void TransformShipPlayerPoints() {
	int number_of_ship_points = 5, number_of_cannon_points = 4, number_of_right_cannon_points = 2;

	Mat3 aux_points = Mat3Identity();
	aux_points = Mat3MultiplyMat3(Mat3Scale(player_ship.dimension.x, player_ship.dimension.y), aux_points);
	aux_points = Mat3MultiplyMat3(Mat3Rotate(player_ship.sin, player_ship.cos), aux_points);
	aux_points = Mat3MultiplyMat3(Mat3Translate(player_ship.position.x, player_ship.position.y), aux_points);

	for (int i = 0; i < number_of_ship_points; ++i) {
		player_ship.points_transformed[i] = Mat3MultiplyVec3(aux_points, player_ship.points[i]);
	}

	Mat3 aux_cannon_right = Mat3Identity();
	aux_cannon_right = Mat3MultiplyMat3(Mat3Translate(0.25f, 0), aux_cannon_right);
	aux_cannon_right = Mat3MultiplyMat3(aux_points, aux_cannon_right);

	Mat3 aux_cannon_left = Mat3Identity();
	aux_cannon_left = Mat3MultiplyMat3(Mat3Translate(-1.5f, 0), aux_cannon_left);
	aux_cannon_left = Mat3MultiplyMat3(aux_cannon_right, aux_cannon_left);

	for (int i = 0; i < number_of_cannon_points; ++i) {
		if (i < number_of_right_cannon_points) {
			player_ship.cannons_points_transformed[i] = Mat3MultiplyVec3(aux_cannon_right, player_ship.cannons_points[i]);
		}
		else {
			player_ship.cannons_points_transformed[i] = Mat3MultiplyVec3(aux_cannon_left, player_ship.cannons_points[i % 2]);
		}
	}
}
void TransformMotherShipPoints() {
	int number_of_mothership_points = 11;

	Mat3 aux_points = Mat3Identity();
	aux_points = Mat3MultiplyMat3(Mat3Scale(mother_ship.dimension.x, mother_ship.dimension.y), aux_points);
	aux_points = Mat3MultiplyMat3(Mat3Rotate(mother_ship.sin, mother_ship.cos), aux_points);
	aux_points = Mat3MultiplyMat3(Mat3Translate(mother_ship.position.x, mother_ship.position.y), aux_points);

	for (int i = 0; i < number_of_mothership_points; ++i) {
		mother_ship.points_transformed[i] = Mat3MultiplyVec3(aux_points, mother_ship.points[i]);
	}
	/*
	Mat3 aux_wing_right = Mat3Identity();
	aux_wing_right = Mat3MultiplyMat3(Mat3Rotate((esat::fPI / 3),0),aux_wing_right);
	aux_wing_right = Mat3MultiplyMat3(Mat3Scale(0.5f,0.7f),aux_wing_right);
	aux_wing_right = Mat3MultiplyMat3(Mat3Translate(0.4f,-0.8f),aux_wing_right);
	aux_wing_right = Mat3MultiplyMat3(aux_points,aux_wing_right);

	for(int i = 0; i < 5; ++i){
		mother_ship.wings_points_transformed[i] = Mat3MultiplyVec3(aux_wing_right, mother_ship.wings_points[i]);
	}
	*/
}
void TransformRingsPoints(int dimension_x, int dimension_y) {

	const float a = (fPI * 2) / ring.number_of_points;
	const float radio = 1.0f;
	const float sa = sin(a);
	const float ca = cos(a);

	float s = 0;
	float c = 1;

	for (int current_segment = 0; current_segment < ring.segments; ++current_segment) {
		Mat3 m = Mat3Identity();
		m = Mat3MultiplyMat3(Mat3Translate(0.0f, 3.5f), m);
		m = Mat3MultiplyMat3(Mat3Scale(dimension_x, dimension_y), m);
		m = Mat3MultiplyMat3(Mat3Rotate(clock()/ 1000.0f), m);
		m = Mat3MultiplyMat3(Mat3Rotate((fPI * 2.0f) / ring.segments * current_segment), m);
		m = Mat3MultiplyMat3(Mat3Translate(kWindowX * 0.5f, kWindowY * 0.5f), m);

		for (int i = 0; i < ring.number_of_points; ++i) {
			float s_next = s * ca + c * sa;
			float c_next = c * ca - s * sa;

			Vec2 p;
			p.x = c * radio;
			p.y = s * radio;
			*(ring.current_point + current_segment) = Mat3MultiplyVec2(m, p);

			Vec2 p_next;
			p_next.x = c_next * radio;
			p_next.y = s_next * radio;
			*(ring.next_point + current_segment) = Mat3MultiplyVec2(m, p_next);

			s = s_next;
			c = c_next;
		}
	}
}
void DrawShipPlayer() {
	int number_of_ship_lines = 4;


	for (int i = 0; i < number_of_ship_lines; ++i) {
		Vertex ship_lines[2];
		ship_lines[0].position = sf::Vector2f(player_ship.points_transformed[i].x, player_ship.points_transformed[i].y);
		ship_lines[0].color = sf::Color::Red;
		ship_lines[1].position = sf::Vector2f(player_ship.points_transformed[i + 1].x, player_ship.points_transformed[i + 1].y);
		ship_lines[1].color = sf::Color::Red;
		//window.draw(ship_lines, 2, Lines);
	}
	//right cannon
	Vertex right_cannon[2];
	right_cannon[0].position = sf::Vector2f(player_ship.cannons_points_transformed[0].x, player_ship.cannons_points_transformed[0].y);
	right_cannon[0].color = sf::Color::Red;
	right_cannon[1].position = sf::Vector2f(player_ship.cannons_points_transformed[1].x, player_ship.cannons_points_transformed[1].y);
	right_cannon[1].color = sf::Color::Red;
	//window.draw(right_cannon, 2, Lines);

	//left cannon
	Vertex left_cannon[2];
	left_cannon[0].position = sf::Vector2f(player_ship.cannons_points_transformed[2].x, player_ship.cannons_points_transformed[2].y);
	left_cannon[0].color = sf::Color::Red;
	left_cannon[1].position = sf::Vector2f(player_ship.cannons_points_transformed[3].x, player_ship.cannons_points_transformed[3].y);
	left_cannon[1].color = sf::Color::Red;
	//window.draw(left_cannon, 2, Lines);

}

void Inits() {
	InitShip();
	InitMotherShip();
	InitRing();
}
void Updates() {
	Input();
	JoinLimits();
	MoveShipPlayer();
	TransformShipPlayerPoints();
	TransformMotherShipPoints();
	TransformRingsPoints(20, 20);
	TransformRingsPoints(40, 40);
}
void Draws() {
	DrawShipPlayer();
	/*DrawMotherShip();
	DrawRing();*/
}
void GameController() {
	Updates();
	Draws();
}
int main(int argc, char **argv) {

	clock_t current_time, last_time;
	unsigned char fps = 25;

	RenderWindow window(sf::VideoMode(kWindowX, kWindowY), "Start Castle");
	window.setMouseCursorVisible(true);
	srand(time(NULL));

	Inits();

	while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
	{
		Event event;
		last_time = clock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		GameController();
		
		window.display();
		do {
			current_time = clock();
		} while ((current_time - last_time) <= 1000.0 / fps);
		
	}
	free(ring.current_point);
	free(ring.next_point);
		return 0;
}