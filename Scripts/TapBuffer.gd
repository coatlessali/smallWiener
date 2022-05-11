extends Node

const size = 30
const buffer = []

enum inputs {UP, DOWN, LEFT, RIGHT, NONE}

func _ready():
	for i in range(size):
		buffer.append(0)

func _physics_process(delta):
	for i in range(size - 1, 0, -1):
		buffer[i] = buffer[i - 1]

	var keyData = 0
	for input in ["ui_up", "ui_down", "ui_left", "ui_right"]:
		if Input.is_action_just_pressed(input):
			keyData |= _string2bit(input)
	buffer[0] = keyData

func check(input, n):
	var index = -1
	for i in range(n):
		if buffer[i] & _string2bit(input) != 0:
			index = i
			break
	return index != -1

func _string2input(string):
	match string:
		"ui_up":
			return inputs.UP
		"ui_down":
			return inputs.DOWN
		"ui_left":
			return inputs.LEFT
		"ui_right":
			return inputs.RIGHT

func _input2bit(input):
	match input:
		inputs.UP:
			return 0b0001
		inputs.DOWN:
			return 0b0010
		inputs.LEFT:
			return 0b0100
		inputs.RIGHT:
			return 0b1000

func _string2bit(string):
	return _input2bit(_string2input(string))
