TITLE CS2810 Assembler Template

INCLUDE Irvine32.inc
.data
	;--------- Enter Data Here
	vSemester BYTE "CS2810 Summer Semester 2017",0
	vAssignment BYTE "Assembler Assignment #4",0
	vName BYTE "Stephen Richardson",0
	vPrompt BYTE "Please enter your FAT16 file date in hexadecimal: ",0

	;<------------Months Array------------->
	vMonthArray BYTE "January ",0,"  " ;holds space between month and day
				BYTE "February ",0," "
				BYTE "March ",0,"    "
				BYTE "April ",0,"    "
				BYTE "May ",0,"      "
				BYTE "June ",0,"     "
				BYTE "July ",0,"     "
				BYTE "August ",0,"   "
				BYTE "September ",0   
				BYTE "October ",0,"  "
				BYTE "November ",0," "
				BYTE "December ",0," "
	;<------------End Months Array---------->

	vDay BYTE "--",0
	vYear BYTE "----",0

	vPostSuffix BYTE ", ",0 ;holds comma and space for between day and year
	vSuffST BYTE "st",0
	vSuffND BYTE "nd",0
	vSuffRD BYTE "rd",0
	vSuffTH BYTE "th",0

.code
main PROC
	;--------- Enter Code Below Here
	call clrscr
	call displayHeader
	call retrieveData
	call displayMonth
	call displayDay
	call determineSuffix
	call displayYear

	;<--------------------Labels------------------->
	displayHeader:
		;write out semester, then assignment, then name
		mov dh, 4
		mov dl, 33
		call gotoxy
		mov edx, offset vSemester
		call WriteString

		mov dh, 5
		mov dl, 33
		call gotoxy
		mov edx, offset vAssignment
		call WriteString

		mov dh, 6
		mov dl, 33
		call gotoxy
		mov edx, offset vName
		call WriteString

		ret
	;-----end displayHeader-----

	retrieveData:
		;move cursor and display prompt
		mov dh, 8
		mov dl, 33
		call gotoxy
		mov edx, offset vPrompt
		call WriteString

		;read in data, endian reverse it, then save a copy to ecx
		call ReadHex
		ror ax, 8
		mov ecx, eax

		;move the cursor for displaying the answer
		mov dh, 10
		mov dl, 33
		call gotoxy

		ret
	;-----end retrieveData-----

	displayMonth:
		;isolate bits 7-10 to get month
		and ax, 0000000111100000b
		shr ax, 5

		;move the pointer to my array into edx
		mov edx, offset [vMonthArray] ;brackets designate it as an array

		;subtract 1 from eax to get the months index value, set bl to the length of
			;each index and multiply them together
		sub ax, 1
		mov bl, 11
		mul bl

		;add the result to  edx to move the offset to the right index value of
			;the array then print the month
		add edx, eax
		call WriteString

		ret
	;-----end displayMonth-----

	displayDay:
		;move in copy from ecx and isolote bits 11-15
		mov eax, ecx
		and ax, 0000000000011111b

		;perform 8 bit division to isolate the separate numbers then turn them into ascii values
		mov bh, 10
		div bh
		add ax, 3030h

		;move ax into the day variable
		mov word ptr [vDay+0], ax

		;seperate out the day again to determine if the day is past the 9th
		mov eax, ecx
		and ax, 0000000000011111b

		;compare the value to 9. if less than or =, jump to dOneDigit
		cmp ax, 9
		jle dOneDigit

		;otherwise, load vDay into edx and jump to writeDay
		mov edx, offset [vDay]
		jmp writeDay

		dOneDigit:
			;if this is reached, the day is from the 1st to the 9th
			;to avoid printing the extraneous zero, load [vDay+1]
			;(vDay with an offset of one) into edx then jmp to writeString
			mov edx, offset [vDay+1]
			jmp writeDay
		
		writeDay:
			call WriteString
		
		ret
	;-----end displayDay-----

	determineSuffix:
		;move in copy from ecx and isolote bits 11-15
		mov eax, ecx
		and ax, 0000000000011111b

		;compare ax to 1, 21 and 31. if it matches, suffix is st
		cmp ax, 1
		jz dSuffST

		cmp ax, 21
		jz dSuffST

		cmp ax, 31
		jz dSuffST

		;compare ax to 2 and 22. if it matches, suffix is nd
		cmp ax, 2
		jz dSuffND

		cmp ax, 22
		jz dSuffND

		;compare ax to 3 and 23. if it matches, suffix is rd
		cmp ax, 3
		jz dSuffRD

		cmp ax, 23
		jz dSuffRD

		;otherwise suffix is th
		;move the requisite suffix string into edx then jump to insertSuffix
		mov edx, offset [vSuffTH]
		jmp insertSuffix

		dSuffST:
			mov edx, offset [vSuffST]
			jmp insertSuffix
		
		dSuffND:
			mov edx, offset [vSuffND]
			jmp insertSuffix

		dSuffRD:
			mov edx, offset [vSuffRD]
			jmp insertSuffix

		insertSuffix:
			; print suffix and post suffix comma and space
			call WriteString
			mov edx, offset vPostSuffix
			call WriteString

		ret
	;-----end determineSuffix-----

	displayYear:
		;get a copy of the hex and isolate bits 0-6 for the year
		mov eax, ecx
		and eax, 1111111000000000b
		shr eax, 9

		;add 1980 to eax to get the year
		add eax, 1980

		;clear out dx to hold the remainder
		xor dx, dx

		;mov 1000 into dx then divide to get the thousands place value
		mov bx, 1000
		div bx

		;add a hex value of 30 to al (that's where one digit would be held),
			;move that digit into the string vYear, then move the remainder from dx to ax
		add al, 30h
		mov byte ptr [vYear], al
		mov ax, dx
		
		;clear out dx to hold the new remainder and repeat for the hundreds place.
		xor dx, dx
		mov bx, 100
		div bx
		add al, 30h
		mov byte ptr [vYear+1], al
		mov ax, dx

		;do 8 bit division for the 10s and 1s places
		mov bl, 10
		div bl
		add ax, 3030h
		mov word ptr [vYear+2], ax
		
		;finally, print the year and tada! all done!
		mov edx, offset [vYear]
		call WriteString

		ret
	;-----end displayYear-----


	xor ecx, ecx ; pauses screen
	call ReadChar

	exit
main ENDP

END main