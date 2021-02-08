TITLE CS2810 Assembler Template

; Student Name: Stephen Richardson
; Assignment Due Date: 11/05/17

INCLUDE Irvine32.inc
.data
	;--------- Enter Data Here in this assignment, your strings
	
	;variableName whatDataTypeToSaveItAs "what you're saving",0(endWithZero)
	vSemester byte "CS2810 Fall Semester 2017",0
	vAssignment byte "Assembler Assignment #1",0
	vName byte "Stephen Richardson",0

.code
main PROC
	;--------- Enter Code Below Here
	call clrscr

	;write semester

	;enter coordinates for gotoxy
	mov dh, 2 ; move destination, source
	mov dl, 12
	call gotoxy

	write to where cursor is currently
	mov edx, offset vSemester ; move into edx the offset address of vSemester
	call WriteString

	;write assignment name

	mov dh, 3
	mov dl, 12
	call gotoxy

	mov edx, offset vAssignment
	call WriteString

	;write my name
	mov dh, 4
	mov dl, 12
	call gotoxy

	mov edx, offset vName
	call WriteString

	xor ecx, ecx ; pauses screen
	call ReadChar

	exit
main ENDP

END main