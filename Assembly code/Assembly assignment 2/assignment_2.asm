TITLE CS2810 Assembler Template

; Student Name: Stephen Richardson
; Assignment Due Date: 11/05/17

INCLUDE Irvine32.inc
.data
	;--------- Enter Data Here
	;variableName whatDataTypeToSaveItAs "what you're saving",0(endWithZero)
	vSemester byte "CS2810 Fall Semester 2017",0
	vAssignment byte "Assembler Assignment #2",0
	vName byte "Stephen Richardson",0
	vRequest byte "Please enter a time in Hexidecimal: ",0
	vClosing byte "The time you entered, in hh:mm:ss format, is:  ",0
	vTime byte "--:--:--"

.code
main PROC
	;--------- Enter Code Below Here
	call clrscr

	;write semester
	mov dh, 15
	mov dl, 20
	call gotoxy

	mov edx, offset vSemester
	call WriteString

	;write assignment number
	mov dh, 16
	mov dl, 20
	call gotoxy

	mov edx, offset vAssignment
	call WriteString

	;write name
	mov dh, 17
	mov dl, 20
	call gotoxy

	mov edx, offset vName
	call WriteString

	;request hex
	mov dh, 19
	mov dl, 20
	call gotoxy

	mov edx, offset vRequest
	call WriteString

	;read the hex and prep it for interpretation
	call ReadHex

	;rotate 16 bit hex 8 bits, effectively performing little endian revers
	ror ax, 8

	;save an untouched copy in ecx to use in calculating the min and sec
	mov ecx, eax

	;get hour ascii values

	;isolate the first 5 bits to calculate the hour
	and ax, 1111100000000000b ;the b denotes the number as a binary to the computer

	;shift values to the right to give the correct binary number
	shr ax, 11 ;shift right the code in register ax by 11 bits fill in with trailing zeros

	;divide whats in ax in order to give us separate digits. 
	;we need separate digits so we can convert each digit seperately into an ascii value
	;what is being divided (dividend) needs to be in ax, and what it is being divided by(divisor)
	;can be any register. we only need a half register for this division

	;our dividend is already in ax so move 10 in bh
	mov bh, 10
	div bh ; divide what's in ax by what's in bh

	;the division will give us a tens place digit and a ones place digit value in ax
	;the hex value 30 needs to be added to both halves of ax in order to get the right binary
	;value that matches the ascii value for each digit
	add ax, 3030h

	;put our ascii values into the vTime variable, replacing what is already there.
	;we us a word ptr in order to get into the middle of a string. the + at the end 
	;is for the offset (how many characters into the string to go)
	mov word ptr [vTime+0], ax ; ...[theStringVariableName+offset], registerTheBinaryValuesAreIn

	;get minute ascii values. for descriptions as to whats going on, read the comments in the hour section

	;get untouched copy from ecx
	mov eax, ecx
	;isolate minute bits and shift to right
	and ax, 0000011111100000b ;DON'T FORGET THE b!!!
	shr ax, 5
	;divide and get ascii values for min. don't need to move 10 int bh, cuz it's already there
	div bh
	add ax, 3030h
	;finally move to vTime
	mov word ptr [vTime+3], ax

	;find the seconds ascii values

	mov eax, ecx
	and ax, 0000000000011111b
	;no need to shift right
	;seconds are saved as half the actual value, so need to be doubled before dividing
	;shifting the bits left 1, since it's in binary, effectively doubles the value
	shl ax, 1
	;now we can divide
	div bh
	add ax, 3030h
	mov word ptr [vTime+6], ax

	;display closing and calculated time
	mov dh, 21
	mov dl, 20
	call gotoxy

	mov edx, offset vClosing
	call WriteString

	mov edx, offset vTime
	call WriteString


	xor ecx, ecx ; pauses screen
	call ReadChar

	exit
main ENDP

END main