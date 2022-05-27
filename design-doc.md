# SMALL WIENER
short, but hard af

## Overview
SW is planned to be a 2D Sidescrolling Metroidvania with a deep and intricate combat system that aims to be intuitive without being limiting. The idea is to maximize the distance between the skill ceiling and the skill floor, without compromising on either.

### CONTROLS

The essential control scheme is limited to the PS1 standard controller (not the DualShock), while trying to *aim* to be playable on a SNES/SFC controller. This limitation has a few reasons:
* Hardware Accessibility - Making sure this game is comfortably playable on as many input devices as possible.
* Gameplay Accessibility - Smartly allocating buttons to actions in an intuitive way and simplifying mechanics from two buttons to one button where pheasible.
* Limiting Feature Creep - If you gave me analog sticks, this project would never be finished.

(NOTE: If we can add Native GameCube Controller support later that would be epico tipico.)

For the sake of avoiding confusion, we will be using the PlayStation button names, as Microsoft and Nintendo can't agree on whether or not A is on right or bottom, so Sony took LSD instead.

(NOTE: Add the ability to swap Cross or Circle as confirm in menus pls.)

| Button       | Result                                                           |
| ------------ | ---------------------------------------------------------------- |
| Up           | Look Up / Angle Attacks Upward / Climb Ladders / Enter Rooms (?) |
| Down         | Crouch / Slide / Drop Through Platforms / Fast Fall              |
| Left / Right | Run                                                              |
| Cross        | Jump / Recover / Walljump                                        |
| Square       | Attack / Recover / Parry (Press Forward)                         |
| Triangle     | Special Action / Grab / Grappling Hook (?)                       |
| Circle       | Interact                                                         |
| R1           | Lock Onto Opponent                                               |
| L1           | Time Cancel (Cancels any attack on hit, and any other anim.)     |

While Locked On:

* ! = Does nothing

| Button       | Result                                                           |
| ------------ | ---------------------------------------------------------------- |
| Down         | Crouch                                                           |
| Left / Right | Walk / Run (Double Tap)                                          |
| Cross        | Dodge (Hold Forward) / Backflip (Hold Back) / Jump               |

While In Air:

* ! = Does Nothing

| Button       | Result                                                           |
| ------------ | ---------------------------------------------------------------- |
| Down         | Fast Fall / Angle Attack Downwards                               |
| Cross        | Double Jump (IF UNLOCKED) (CANDIDATE FOR REMOVAL)                |
| Square       | Attack / Parry (IF UNLOCKED)                                     |
| Circle       | Air Dash (IF UNLOCKED)                                           |

(TODO: Simplify these mechanical ideas.)

### UNLOCKABLE ABILITIES

| Upgrade         | Description                                                                       |
| --------------- | --------------------------------------------------------------------------------- |
| Air Parry       | Allows parrying in the air.                                                       |
| Reflector Blade | Allows reflecting light projectiles with a sword swing.                           |
| Thrust Boots    | Allows dashing in the air by either double tapping a direction or tapping Circle. |
| Magnetic Boots  | Lets certain mid-air actions snap the player to the ground or edges.              |

### LEVELING UP

When Art defeats enemies, they drop EXP. After gaining a certain amount of EXP, the player can allocate 1 point to any of the following stats, which begin at 1 and end at 5:
CANDIDATE FOR REMOVAL.

Agility (AGI) - Increases movement speed.
Dexterity (DEX) - Increases attack speed.
Strength (STR) - Increases attack strength.
Vitality (VIT) - Increases available HP.
Defense (DEF) - Decreases damage taken.

## MECHANICS IN-DEPTH

### ATTACKING

When the player attacks, there are a few phases to an attack:

* The startup.
* The moment the hitbox comes out.
* Optionally the connection. -> Start of another attack. / Blockstun.
* The recovery.

In the startup phase, the player is kept still and options are limited heavily. At the very beginning, in the case of an accidental input, the player can cancel the attack with a jump/roll/backflip.

In the hitbox phase, the hitbox appears and if it connects with something, a few things can happen:

* If the opponent blocks, the player is knocked back slightly and they enter the blockstun phase, where they can either wait out the recovery period, parry, or roll.

* Alternatively (not sure), the block simply does its job and the stun phase only happens if the opponent counter attacks as to not break pacing. This means on block, the player can still use gatling options.

* If the hit connects, the player can cancel it into another attack, which is called a gatling option.

In the recovery phase, the player cannot act during the cooldown outside of cancelling into a gatling option, and will receive more damage than normal if hit.

All of these phases can be Time Cancelled for a certain amount of meter. (Yes, even the startup phase, there's a reason that comes later.)

WIP:

| Phase    | Meter | Extra Effect |
| -------- | ----- | ------------ |
| Startup  | 25%   | None         |
| Hitbox   | 50%   | None         |
| Connect  | 50%   | None         |
| Recovery | 25%   | None         |

### DEFENSIVE OPTIONS

When the player is attacked, there are a few options to allow the player to avoid taking damage:
* Parry - Press forward and attack together to block the oncoming attack.
* Perfect Parry - Parry with perfect timing to gain 50% meter instantly.
* Counterattack - Press attack again after parrying to use a counterattack at the cost of 50% meter.
* Roll - While targeting an enemy, press jump while holding left or right to move out of the way.

If the player gets hit, they will enter hitstun, where their only options are to parry or time cancel. This is a special type of TC that requires 100% meter.

### PHYSICAL ATTACKS

WIP

# PROJECTILE ATTACKS

There are two types of projectiles:

* Light Projectiles
* Heavy Projectiles

Light projectiles:
* Can be run through or slid through.
* Cannot harm the player while in blockstun or hitbox phase.
* Cannot be parried.
* Will be interrupted by physical attacks.

Heavy projectiles:
* Cannot be run through or slid through.
* Harms the player unless they parry or reflect.
* Can be interrupted by a parry.
