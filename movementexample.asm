;A sample program that makes the bot go to the position defined at the top.
.define TARGET_X 320
.define TARGET_Y 240

.define INT_MOVEMENT 0x2
.define MOVE_MOVE 0x0
.define MOVE_ROT_CW 0x1
.define MOVE_ROT_CCW 0x2
.define MOVE_QUERY 0x4

;First, we query our position.
call posquery

;See what direction we need to go in
cmp [x], TARGET_X
jge go_west

;Set dir to 0 (for rotating back later), rotate, and set [togo] to the distance to travel.
go_east:
mov [dir], 0
mov A, TARGET_X
sub A, [x]
mov [togo], A
mov A, MOVE_ROT_CW
int INT_MOVEMENT
jmp x_go

;Set dir to 1 (for rotating back later), rotate, and set [togo] to the distance to travel.
go_west:
mov [dir], 1
mov A, [x]
sub A, TARGET_X
mov [togo], A
mov A, MOVE_ROT_CCW
int INT_MOVEMENT

x_go:
;Go to the target X
mov A, MOVE_MOVE

go_x_loop:
;See if we have nowhere to go and if so, jmp out of the loop.
cmp [togo], 0
jz go_x_done
;Else, move and sub 1 from [togo].
sub [togo], 1
int INT_MOVEMENT
jmp go_x_loop

go_x_done:
;We're done. Rotate north first to make the Y rotation easier.
cmp [dir], 0
jnz rot_done_west

rot_done_east:
mov A, MOVE_ROT_CCW
jmp rot_done_do

rot_done_west:
mov A, MOVE_ROT_CW

rot_done_do:
int INT_MOVEMENT


;Do the same thing, but for Y.

;See what direction we need to go in
cmp [y], TARGET_Y
jge go_south

;Set [togo] to the distance to travel.
go_north:
mov A, TARGET_Y
sub A, [y]
mov [togo], A
jmp y_go

;Rotate south and set [togo] to the distance to travel.
go_south:
mov A, [y]
sub A, TARGET_Y
mov [togo], A
mov A, MOVE_ROT_CW
int INT_MOVEMENT
int INT_MOVEMENT

y_go:
;Go to the target Y
mov A, MOVE_MOVE

go_y_loop:
;See if we have nowhere to go and if so, jmp out of the loop.
cmp [togo], 0
jz go_y_done
;Else, move and sub 1 from [togo].
sub [togo], 1
int INT_MOVEMENT
jmp go_y_loop

go_y_done:

;We're done! Now we'll just store our x,y,rot in A,B,C just to verify.
mov A, MOVE_QUERY
int INT_MOVEMENT
pop C
pop B
pop A

hlt
    
;Queries position and stores it in the vars.
posquery:
    push B
    push A
    
    ;We'll query our position. It's pushed to the stack in the order of x,y,rot.
    ;rot is 0 for north, 1 for east, and so on.
    mov A, MOVE_QUERY
    int INT_MOVEMENT
    
    pop [rot] ;rot
    pop [y] ;y
    pop [x] ;x
    
    pop A
    pop B
    ret

;Data storage
x:
    .dw 0x0
y:
    .dw 0x0
rot:
    .dw 0x0
togo:
    .dw 0x0
dir:
    .dw 0x0
