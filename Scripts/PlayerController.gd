extends KinematicBody2D

export (int) var base_speed = 120
export (int) var speed = 360
export (int) var jump_speed = -500
export (int) var gravity = 1000

var velocity = Vector2.ZERO

export (float,0,1.0) var friction = 0.3
export (float,0,1.0) var acceleration = 0.3
var fade = Sprite.new()

enum state {SPRINTING, WALKING, IDLE, JUMP, FALL, ROLLING, ATTACK, CROUCH, LONGJUMP, WALLSLIDE, WALLJUMP}
var landed : bool

var player_state = state.IDLE

func get_dir():
	var dir = Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left")
	return sign(dir)

func get_input():
	var dir = get_dir()
	if dir != 0:
		velocity.x = lerp(velocity.x, dir * speed, acceleration)
	else:
		velocity.x = lerp(velocity.x, 0, friction)

func update_animation():
	#print(get_dir())
	#print($Sprite.get_frame())
	var fadeCounter = 0
	$Trail.local_coords = false
	if velocity.x < -400 or velocity.x > 400:
		#fade.texture = $Sprite.texture
		#fade.hframes = $Sprite.hframes
		#fade.vframes = $Sprite.vframes
		#fade.frame = $Sprite.frame
		#fade.modulate = Color(0, 0, 0)
		$Trail.emitting = true
		if fadeCounter < 60:
			fadeCounter +=1
		else:
			fadeCounter = 0
		if fadeCounter == 1 or fadeCounter == 16 or fadeCounter == 31 or fadeCounter == 46:
			pass
	else:
		$Trail.emitting = false
		fadeCounter = 0
	if player_state != state.WALLJUMP:
		if velocity.x < 0.2 and Input.is_action_pressed("ui_left"):
			$Sprite.flip_h = true
		elif velocity.x > 0.2 and Input.is_action_pressed("ui_right"):
			$Sprite.flip_h = false
	else:
		$Sprite.flip_h = true if velocity.x < 0 else false
	match(player_state):
		state.IDLE:
			#print("IDLE")
			$Animation.play("Idle")
		state.WALKING:
			#print("WALKING")
			$Animation.play("Walking")
			yield($Animation,"animation_finished")
			if player_state == state.WALKING:
				player_state = state.IDLE
		state.ROLLING:
			#print("ROLLING")
			$Animation.play("Sliding")
		state.SPRINTING:
			#print("SPRINTING")
			$Animation.play("Sprinting")
		state.FALL:
			#print("FALLING")
			$Animation.play("Falling")
		state.JUMP:
			#print("JUMPING")
			$Animation.play("Falling")
		state.WALLSLIDE:
			#print("WALLSLIDE")
			$Animation.play("WALLSLIDE")
		state.WALLJUMP:
			#print("WALLJUMP")
			if velocity.x > 0:
				$Animation.play("Walljump")
			elif velocity.x < 0:
				$Animation.play("Walljump2")
			else:
				$Animation.play("WALLSLIDE")
			
	
func _process(delta):
	if player_state == state.ROLLING:
		$CollisionStanding.disabled = true
		$CollisionSliding.disabled = false
		if Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left") != 0:
			friction = 0.01
		else:
			friction = 0.035
	else:
		$CollisionSliding.disabled = true
		$CollisionStanding.disabled = false
		friction = 0.6
	if player_state == state.JUMP or player_state == state.FALL:
		# Put some code here to implement friction on turnaround
		if Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left") > 0 and velocity.x > 0:
			pass
		elif Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left") < 0 and velocity.x < 0:
			pass
		elif speed == 360*1.5:
			speed = 360
	elif player_state != state.SPRINTING and player_state != state.LONGJUMP:
		speed = 360
	else:
		speed = 360*1.5

func _physics_process(delta):
	#print(player_state)
	if player_state != state.ROLLING and player_state != state.ATTACK and player_state != state.WALLJUMP:
		get_input()
		#print(velocity)
		if -20 <= velocity.x and velocity.x <= 20:
			velocity.x = 0
			player_state = state.IDLE
		elif velocity.x != 0 and Input.is_action_just_pressed("ui_down"):
			velocity.x *= 1.25
			player_state = state.ROLLING
		elif -30 < velocity.x and velocity.x < 30 and Input.is_action_just_pressed("ui_down"):
			player_state = state.CROUCH
		elif velocity.x != 0 and player_state != state.SPRINTING:
			player_state = state.WALKING
		
		if is_on_floor(): #and player_state != state.ROLLING:
			if landed == false:
				landed = true
				if Input.is_action_pressed("ui_down"):
					if velocity.x == 0:
						if $Sprite.flip_h == false:
							velocity.x = 500
						elif $Sprite.flip_h == true:
							velocity.x = -500
					velocity.x *= 1.25
					player_state = state.ROLLING
			if Input.is_action_just_pressed("ui_up"):
				velocity.y = jump_speed
				player_state = state.JUMP
			if Input.is_action_just_pressed("ui_right"):
				if $TapBuffer.check("ui_right", 10):
					player_state = state.SPRINTING
			elif Input.is_action_just_pressed("ui_left"):
				if $TapBuffer.check("ui_left", 10):
					player_state = state.SPRINTING
	elif player_state == state.ROLLING: # What to do when we're sliding
		if -30 < velocity.x and velocity.x < 30: # What to do at the end of the slide
			if Input.is_action_pressed("ui_down"): # Check if we're still holding it down
				velocity.x = 0 # Stop
				player_state = state.CROUCH # change to crouch later
			else: # If we're not holding down
				velocity.x = 0 # Stop
				player_state = state.IDLE # Reset
		if Input.is_action_just_released("ui_down"): # If we let go mid-slide
			if velocity.x != 0: # Walk
				player_state = state.WALKING
			else: # Stand
				player_state = state.IDLE
		velocity.x = lerp(velocity.x, 0, friction)
		#print(velocity)
	elif player_state == state.WALLJUMP:
		velocity.x = lerp(velocity.x, 0, friction/32)
		pass
	if not is_on_floor():
		landed = false
		if is_on_wall():
			#if Input.get_action_strength("ui_left") + Input.get_action_strength("ui_right") != 0:
			player_state = state.WALLSLIDE
			if Input.is_action_just_pressed("ui_up"):
				velocity.y = jump_speed*0.8
				#var dir # We no longer require input left or right to enter WALLSLIDE
				#dir = Input.get_action_strength("ui_left") - Input.get_action_strength("ui_right")
				var uhh
				uhh = -1 if $Sprite.flip_h == false else 1 # New method to figure out which way we need to jump off a wall
				print(uhh)
				velocity.x = sign(uhh) * speed * 1.75
				#velocity.x = mult * (speed*2)
				player_state = state.WALLJUMP
		else:
			if velocity.y < 0:
				if player_state != state.WALLJUMP:
					player_state = state.JUMP
					if Input.is_action_just_released("ui_up"):
						velocity.y /= 2
			else:
				player_state = state.FALL
	print(is_on_wall())
	velocity.y += gravity * delta
	velocity = move_and_slide(velocity, Vector2.UP)
	update_animation()
