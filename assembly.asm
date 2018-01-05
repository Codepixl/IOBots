.define HWID_STORAGE 0x1
.define INT_HWQ 0x1
.define INT_HWI 0x3
.define WRITE_MANY 0x3
.define READ_MANY 0x2

;Hardware Query
int 0x1

;Find first StorageHardware
;Start with 0xFFFE because when 2 is added to it, it will be 0x0
mov C, 0xFFFE
loop:
add C, 2
mov D, [C]
mov A, D
;And D with 0xFF to get the hardware ID
and D, 0x00FF
;Compare with 0x1 (the HWID of StorageHardware)
cmp D, HWID_STORAGE
;If not StorageHardware, jmp to loop to keep searching
jnz loop

;We found it! Since we copied the hardware descriptor to A, we shift it 8 bits right to get the slot.
shr A, 8

;We're going to use the write many words function of the StorageHardware.
push data          ;Push location to read from
push 0x0           ;Push location in StorageHardware to write to
push 0x8           ;Push the number of WORDS (not bytes) to write.
mov B, WRITE_MANY  ;Use the write many function of the StorageHardware.
int INT_HWI        ;Call the hardware interrupt interrupt. The slot of the StorageHardware is already in A.

;Now we're going to read many words from it.
push data2       ;Push location to write to.
push 0x0         ;Push the location in StorageHardware to read from.
push 0x8         ;Push the number of words to read.
mov B, READ_MANY ;Use the read many function of the StorageHardware.
int INT_HWI      ;Same interrupt deal

;And now we mov part of the data into A to verify it worked.
mov A, [data21]
hlt

;Data storage
data:
.dw 0x1
.dw 0x2
.dw 0x4
.dw 0x8
.dw 0x10
.dw 0x20
.dw 0x40
.dw 0x80

;We're copying to here
data2:
.dw 0x0
.dw 0x0
data21:
.dw 0x0
.dw 0x0
.dw 0x0
.dw 0x0
.dw 0x0
.dw 0x0