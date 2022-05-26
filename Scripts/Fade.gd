extends Sprite

func _ready():
    # TODO: de-hardcode this
    texture  = $"KinematicBody2D/Sprite".texture
    hframes  = $"KinematicBody2D/Sprite".hframes
    vframes  = $"KinematicBody2D/Sprite".vframes
    frame    = $"KinematicBody2D/Sprite".frame
    modulate = Color(0,0,0,1)

func _process(delta):
    pass
