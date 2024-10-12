extends AnimatableBody2D

var elapsed_time = 0
var period_seconds: float = 2
var position_offset: Vector2 = Vector2(0, 100)
var original_position: Vector2

func _ready() -> void:
	original_position = global_position

func _physics_process(delta: float) -> void:
	spin(delta)

func oscillate(delta: float):
	elapsed_time += delta
	var t : float = elapsed_time / period_seconds
	var sine_value : float = sin(t * PI * 2.0)
	global_position = original_position.lerp(
		original_position + position_offset,
		(sine_value + 1.0) / 2.0
	)

func spin(delta: float):
	global_rotation += (delta * PI * 2.0) / period_seconds
