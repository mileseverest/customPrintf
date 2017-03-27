.global main, mymain, Myprintf

main:    

	pushl	%ebp
	movl	%esp, %ebp

    pushl 16(%ebp) # env
    pushl 12(%ebp) # argv
    pushl 8(%ebp)  # argc    

	call	mymain
    addl $16, %esp # restore stack
	
    movl %ebp, %esp
    popl %ebp    

    ret

#   what is being stored        | env | argv | argc | ret | mymain |
    #   offset                  | 16  | 12   | 8    | 4   | 0      |
