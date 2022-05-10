extends Sprite


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	texture = $"KinematicBody2D/Sprite".texture
	hframes = $"KinematicBody2D/Sprite".hframes
	vframes = $"KinematicBody2D/Sprite".vframes
	frame = $"KinematicBody2D/Sprite".frame
	modulate = Color(0,0,0,1)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
