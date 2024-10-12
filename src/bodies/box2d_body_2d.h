#pragma once

#include "../shapes/box2d_shape_2d.h"
#include "../spaces/box2d_space_2d.h"
#include "box2d/box2d.h"
#include "box2d_direct_body_state_2d.h"
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/templates/local_vector.hpp>


class Box2DDirectBodyState2D;

class Box2DBody2D {
public:
	~Box2DBody2D();

	b2BodyId get_body_id();

	RID get_rid() const { return rid; }
	void set_rid(const RID &p_rid) { rid = p_rid; }

	void set_space(Box2DSpace2D *p_space);
	Box2DSpace2D *get_space();

	void set_mode(PhysicsServer2D::BodyMode p_mode);
	PhysicsServer2D::BodyMode get_mode();

	void set_transform(Transform2D p_transform);
	Transform2D get_transform();

	void set_linear_velocity(const Vector2 &p_velocity);
	Vector2 get_linear_velocity() const;
	void set_angular_velocity(float p_velocity);
	float get_angular_velocity() const;
	bool is_sleeping() { return sleeping; }

	void update_state(b2Transform p_transform, bool is_sleeping);

	void add_shape(Box2DShape2D *p_shape, Transform2D p_transform, bool p_disabled);
	void set_shape(int p_index, Box2DShape2D *p_shape);
	void remove_shape(int p_index);
	int32_t get_shape_count();
	void set_shape_transform(int p_index, Transform2D p_transform);
	Transform2D get_shape_transform(int p_index);
	RID get_shape_rid(int p_index);

	void set_instance_id(const ObjectID &p_instance_id) { instance_id = p_instance_id; }
	ObjectID get_instance_id() const { return instance_id; }

	void set_canvas_instance_id(const ObjectID &p_canvas_instance_id) { canvas_instance_id = p_canvas_instance_id; }
	ObjectID get_canvas_instance_id() const { return canvas_instance_id; }

	Box2DDirectBodyState2D *get_direct_state();
	void set_state_sync_callback(const Callable &p_callable);
	void call_queries();

private:
	struct Shape {
		Box2DShape2D *shape = nullptr;
		b2ShapeId shape_id = b2_nullShapeId;
		Transform2D transform;
		bool disabled = false;
		bool one_way_collision = false;
		real_t one_way_collision_margin = 0.0;
	};

	void update_shape(Shape &p_shape);
	void update_all_shapes();

	RID rid;
	b2BodyDef body_def = b2DefaultBodyDef();
	b2BodyId body_id = b2_nullBodyId;
	Box2DSpace2D *space = nullptr;
	LocalVector<Shape> shapes;
	PhysicsServer2D::BodyMode mode;
	ObjectID instance_id;
	ObjectID canvas_instance_id;
	Callable body_state_callback;
	Transform2D current_transform;
	bool sleeping;
	Box2DDirectBodyState2D *direct_state;
};
