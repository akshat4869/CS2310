@ARG
D=M
@1
A=D+A
D=A
D=M
@SP
AM=M+1
A=A-1
M=D
@3
D=A
@1
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@0
D=A
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@0
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@1
D=A
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@1
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M
@0
A=D+A
D=A
D=M
@SP
AM=M+1
A=A-1
M=D
@2
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M-D
@ARG
D=M
@0
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
(FibonacciSeries.vmMAIN_LOOP_START)
@ARG
D=M
@0
A=D+A
D=A
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@FibonacciSeries.vmCOMPUTE_ELEMENT
D;JNE
@FibonacciSeries.vmEND_PROGRAM
0;JMP
(FibonacciSeries.vmCOMPUTE_ELEMENT)
@THAT
D=M
@0
A=D+A
D=A
D=M
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@1
A=D+A
D=A
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=D+M
@THAT
D=M
@2
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@3
D=A
@1
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
@1
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=D+M
@3
D=A
@1
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M
@0
A=D+A
D=A
D=M
@SP
AM=M+1
A=A-1
M=D
@1
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M-D
@ARG
D=M
@0
D=A+D
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@FibonacciSeries.vmMAIN_LOOP_START
0;JMP
(FibonacciSeries.vmEND_PROGRAM)
