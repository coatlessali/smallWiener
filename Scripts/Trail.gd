extends Particles2D

func _ready():
    pass

func _process(delta):
    texture = get_node("/root/Node2D/KinematicBody2D/Sprite").texture # TODO: de-hardcode this
    pass
