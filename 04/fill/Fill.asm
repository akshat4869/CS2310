// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.


(loop)	
	@KBD
	D=M
	@black
	D;JNE
	@white
	D;JEQ

	(black)
	@16384
	D=A
	@i
	M=D
		(loop1)
		@i
		D=M
		@24576
		D=D-A
		@end1
		D;JGE
		@i
		D=M
		A=D
		M=-1
		@i
		M=M+1
		@loop1
		0;JMP
		(end1)
	@loop
	0;JMP
	
	
	(white)
	@16384
	D=A
	@i
	M=0
		(loop2)
		@16384
		D=A
		@i
		D=M+D
		@24576
		D=D-A
		@end2
		D;JGE
		M=0;
		@16384
		D=A
		@i
		A=D+M
		M=0
		@i
		M=M+1
		@loop2
		0;JMP
		(end2)
	@loop
	0;JMP