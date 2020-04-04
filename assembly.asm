;A sample program that moves with the arrow keys on the keyboard.
.define INT_MOVEMENT 0x2
.define INT_KEYBOARD 0x3

.define MOVE         0x0
.define ROTATE       0x3

.define NORTH        0x0
.define EAST         0x1
.define SOUTH        0x2
.define WEST         0x3

.define KEY_RIGHT    0x4F
.define KEY_LEFT     0x50
.define KEY_UP       0x51
.define KEY_DOWN     0x52

loop:
int INT_KEYBOARD ;Query the keyboard for a keypress
cmp B, 0
jz loop          ;Go back to the beginning of the loop if it's 0 (no keypress)

mov A, ROTATE

down:
cmp B, KEY_DOWN
jnz up
mov B, SOUTH
jmp move

up:
cmp B, KEY_UP
jnz left
mov B, NORTH
jmp move

left:
cmp B, KEY_LEFT
jnz right
mov B, WEST
jmp move

right:
cmp B, KEY_RIGHT
jnz loop
mov B, EAST
jmp move

move:
mov A, ROTATE
int INT_MOVEMENT
mov A, MOVE
int INT_MOVEMENT

jmp loop