TITLE CS2810 Assembler Template

; Student Name: Stephen Richardson
; Assignment Due Date: 11/05/17

INCLUDE Irvine32.inc
.data
	;--------- Enter Data Here
	vSemester byte "CS2810 Fall Semester 2017",0
	vAssignment byte "Assembler Assignment #3",0
	vName byte "Stephen Richardson",0
	vPrompt byte "Please enter an MP3 frame header in a hexidecimal format:",0
	
	;name of mpeg types
	vMpeg25 byte "MPEG Version 2.5",0
	vMpeg20 byte "MPEG Version 2.0",0
	vMpeg10 byte "MPEG Version 1.0",0
	vMpegRE byte "MPEG Reserved",0

	;sampling rate variables
	vSampleHeader byte "Sampling Rate Frequency: ",0
	vMpeg10SR1 byte "44100 Hz",0
	vMpeg10SR2 byte "48000 Hz",0
	vMpeg10SR3 byte "32000 Hz",0
	vMpeg10SRRE byte "Reserved",0
	vMpeg20SR1 byte "22050 Hz",0
	vMpeg20SR2 byte "24000 Hz",0
	vMpeg20SR3 byte "16000 Hz",0
	vMpeg20SRRE byte "Reserved",0
	vMpeg25SR1 byte "11025 Hz",0
	vMpeg25SR2 byte "12000 Hz",0
	vMpeg25SR3 byte "8000 Hz",0
	vMpeg25SRRE byte "Reserved",0
	vMpegRESR byte "Information Unavailable",0

	;layer types
	vLayer1 byte "Layer Type 1",0
	vLayer2 byte "Layer Type 2",0
	vLayer3 byte "Layer Type 3",0
	vLayerRE byte "Layer Reserved",0

.code
main PROC
	;--------- Enter Code Below Here
	call clrscr
	call DisplayHeader
	call ReadMP3Header

	;move cursor for version display
	mov dh, 15
	mov dl, 12
	call gotoxy

	call DisplayVersion

	;move cursor for layer display
	mov dh, 16
	mov dl, 12
	call gotoxy

	call DisplayLayer

	;move cursor for sampling rate
	mov dh, 17
	mov dl, 12
	call gotoxy

	mov edx, offset vSampleHeader
	call WriteString

	call DisplaySampleRate

	;creating our own label (method/function)
	;LabelName:
		;Label content
		;ret goes back to original address
	DisplayHeader:
		mov dh, 10
		mov dl, 12
		call gotoxy

		mov edx, offset vSemester
		call WriteString

		mov dh, 11
		mov dl, 12
		call gotoxy

		mov edx, offset vAssignment
		call WriteString

		mov dh, 12
		mov dl, 12
		call gotoxy

		mov edx, offset vName
		call WriteString

		ret;

	ReadMP3Header:
		;display prompt and read in hex value
		mov dh, 13
		mov dl, 12
		call gotoxy

		mov edx, offset vPrompt
		call WriteString

		mov dh, 14
		mov dl, 12
		call gotoxy

		call ReadHex

		;save a copy in ecx
		mov ecx, eax
	
		ret

	DisplayVersion: 
		;assembly header format
		;isolate B bits to get Version ID
				;AAAAAAAAAAABBCCDEEEEFFGHIIJJKLMM
		and eax, 00000000000110000000000000000000b
		shr eax, 19

		;compare isolated bits to what each format bit pattern would be
		;then do a jump to the correct label to print out that version.

		cmp eax, 00b ;compare what's in eax to the binary value 00
		jz dMpeg25 ;if true, jump to the label of the name dMpeg25

		cmp eax, 01b
		jz dMpegRE

		cmp eax, 10b
		jz dMpeg20

		;if none of the others match, get the offset prepped for the final option
		mov edx, offset vMpeg10
		jmp DisplayString

		;labels for DisplayVersion
		dMpeg25:
			mov edx, offset vMpeg25
			jmp DisplayString

		dMpegRE:
			mov edx, offset vMpegRE
			jmp DisplayString

		dMpeg20:
			mov edx, offset vMpeg20
			jmp DisplayString

		DisplayString:
			call WriteString

		;return for entire Display Version
		ret

	DisplayLayer:
		;copy untouched hex to eax
		mov eax, ecx
		
		;assembly header format
		;isolate C bits to get Version ID
				;AAAAAAAAAAABBCCDEEEEFFGHIIJJKLMM
		and eax, 00000000000001100000000000000000b
		shr eax, 17

		cmp eax, 00b
		jz dLayerRE

		cmp eax, 01b
		jz dLayer3

		cmp eax, 10b
		jz dLayer2

		;if not the others, assume its layer 1
		mov edx, offset vLayer1
		jmp DisplayString2

		;Labels for DisplayLayer
		dLayerRE:
			mov edx, offset vLayerRE
			jmp DisplayString2

		dLayer3:
			mov edx, offset vLayer3
			jmp DisplayString2

		dLayer2:
			mov edx, offset vLayer2
			jmp DisplayString2

		DisplayString2:
			call WriteString

		;return for Display Layer
		ret

	DisplaySampleRate:
		;copy untouched hex to eax
		mov eax, ecx
		
		;assembly header format
		;isolate B bits to get Version ID
				;AAAAAAAAAAABBCCDEEEEFFGHIIJJKLMM
		and eax, 00000000000110000000000000000000b
		shr eax, 19

		;get the version id, then jump to label that will parse that 

		cmp eax, 00
		jz mpeg25SR

		cmp eax, 10b
		jz mpeg20SR

		cmp eax, 11b
		jz mpeg10SR

		;otherwise it's a reserved version, which doesn't have sample rate info
		mov edx, offset vMpegRESR
		jmp DisplayString3

		mpeg25SR:
			;copy untouched hex to eax
			mov eax, ecx
		
			;assembly header format
			;isolate F bits to get Sample rate type
					;AAAAAAAAAAABBCCDEEEEFFGHIIJJKLMM
			and eax, 00000000000000000000110000000000b
			shr eax, 10

			cmp eax, 00b
			jz mpeg25SR1 ;jump to label that will print ver. 2.5 sample rate 1

			cmp eax, 01b
			jz mpeg25SR2 ;jump to label that will print ver. 2.5 sample rate 2

			cmp eax, 10b
			jz mpeg25SR3 ;jump to label that will print ver. 2.5 sample rate 3 

			;only other option is the reserved sample rate
			mov edx, offset vMpeg25SRRE
			jmp DisplayString3

			mpeg25SR1:
				mov edx, offset vMpeg25SR1
				jmp DisplayString3

			mpeg25SR2:
				mov edx, offset vMpeg25SR2
				jmp DisplayString3

			mpeg25SR3:
				mov edx, offset vMpeg25SR3
				jmp DisplayString3

		mpeg20SR:
			;copy untouched hex to eax
			mov eax, ecx
		
			;assembly header format
			;isolate F bits to get Sample rate type
					;AAAAAAAAAAABBCCDEEEEFFGHIIJJKLMM
			and eax, 00000000000000000000110000000000b
			shr eax, 10

			cmp eax, 00b
			jz mpeg20SR1 ;jump to label that will print ver. 2.5 sample rate 1

			cmp eax, 01b
			jz mpeg20SR2 ;jump to label that will print ver. 2.5 sample rate 2

			cmp eax, 10b
			jz mpeg20SR3 ;jump to label that will print ver. 2.5 sample rate 3 

			;only other option is the reserved sample rate
			mov edx, offset vMpeg20SRRE
			jmp DisplayString3

			mpeg20SR1:
				mov edx, offset vMpeg20SR1
				jmp DisplayString3

			mpeg20SR2:
				mov edx, offset vMpeg20SR2
				jmp DisplayString3

			mpeg20SR3:
				mov edx, offset vMpeg20SR3
				jmp DisplayString3

		mpeg10SR:
			;copy untouched hex to eax
			mov eax, ecx
		
			;assembly header format
			;isolate F bits to get Sample rate type
					;AAAAAAAAAAABBCCDEEEEFFGHIIJJKLMM
			and eax, 00000000000000000000110000000000b
			shr eax, 10

			cmp eax, 00b
			jz mpeg10SR1 ;jump to label that will print ver. 2.5 sample rate 1

			cmp eax, 01b
			jz mpeg10SR2 ;jump to label that will print ver. 2.5 sample rate 2

			cmp eax, 10b
			jz mpeg10SR3 ;jump to label that will print ver. 2.5 sample rate 3 

			;only other option is the reserved sample rate
			mov edx, offset vMpeg10SRRE
			jmp DisplayString3

			mpeg10SR1:
				mov edx, offset vMpeg10SR1
				jmp DisplayString3

			mpeg10SR2:
				mov edx, offset vMpeg10SR2
				jmp DisplayString3

			mpeg10SR3:
				mov edx, offset vMpeg10SR3
				jmp DisplayString3
		
		DisplayString3:
			call WriteString
		
		;return for Display Sample Rate
		ret

	call ReadChar
main ENDP

END main