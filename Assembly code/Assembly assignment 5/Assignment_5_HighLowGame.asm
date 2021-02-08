TITLE CS2810 Assembler Template

; Student Name: Stephen Richardson
; Assignment Due Date: 12/03/17

INCLUDE Irvine32.inc
.data
	;--------- Enter Data Here
	vSemester byte "CS2810 Fall Semester 2017",0
	vAssignment byte "Assembler #5",0
	vName byte "Stephen Richardson",0

	vCarriageReturn byte 13,10,0

	vStartGame byte "Guess a number between 1 and 100: ",0
	vHigh byte " is too high",0
	vLow byte " is too low",0
	vGuessAgain byte "Guess again: ",0
	vCorrect byte " is correct!",0
	vPlayAgain byte "Would you like to play again? Press 1 for yes and 0 for no: ",0
	vGracefulClose byte "Thank you for playing!",0

.code
main PROC
	;--------- Enter Code Below Here
	call clrscr
	call Randomize
	call displayHeader
	call startRound
	;start round jumps directly to game loop, which jumps directly to endRound,
	;which either jumps back to startRound or terminates the program

	xor ecx, ecx ; pauses screen
	call ReadChar

	;<--------------------Labels---------------->
	displayHeader:
		mov dh, 4
		mov dl, 0
		call gotoxy
		mov edx, offset vSemester
		call WriteString

		mov edx, offset vCarriageReturn
		call WriteString
		mov edx, offset vAssignment
		call WriteString

		mov edx, offset vCarriageReturn
		call WriteString
		mov edx, offset vName
		call WriteString

		ret
	;-----end writeHeading-----

	startRound:
		;put a space between games
		mov edx, offset vCarriageReturn
		call WriteString
		call WriteString
		
		;create random number. need to put upper limit +1 in eax
		mov eax, 101
		call RandomRange

		;random number should be in eax. save a copy in ecx
		mov ecx, eax

		;display opening statement
		mov edx, offset vStartGame
		call WriteString

		jmp gameLoop
	;-----end startRound-----

	gameLoop:
		call ReadDec

		;if greater than
		cmp eax, ecx
		jg dGreater

		;if less than
		cmp eax, ecx
		jl dLess
		
		;otherwise, must be equal to
		call WriteDec
		mov edx, offset vCorrect
		call WriteString
		mov edx, offset vCarriageReturn
		call WriteString

		jmp exitLoop

		dGreater:
			call WriteDec
			mov edx, offset vHigh
			call WriteString

			mov edx, offset vCarriageReturn
			call WriteString
			mov edx, offset vGuessAgain
			call WriteString

			jmp gameLoop

		dLess:
			call WriteDec
			mov edx, offset vLow
			call WriteString

			mov edx, offset vCarriageReturn
			call WriteString
			mov edx, offset vGuessAgain
			call WriteString

			jmp gameLoop

		exitLoop:
			jmp endRound

	;-----end gameLoop-----

	endRound:
		;ask if they want to play again
		mov edx, offset vPlayAgain
		call WriteString
		call ReadDec

		;if number is 1, jump to startRound
		cmp eax, 1
		jz startRound

		;otherwise, end the program
		mov edx, offset vCarriageReturn
		call WriteString
		mov edx, offset vGracefulClose
		call WriteString

		ret
	;-----end endRound-----


	

	exit
main ENDP

END main