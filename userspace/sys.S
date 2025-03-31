.intel_syntax noprefix

.global write
.global read
.global execve
.global fork
.global cool_waitid
.global _exit

# rax寄存器中存放的是系统调研编号，打开你的内核源码，参考: 
# linux/arch/x86/include/generated/asm/syscalls_64.h

write:
mov rax, 1
syscall
ret

read:
mov rax, 0
syscall
ret

execve:
mov rax, 59
syscall
ret

fork:
mov rax, 57
syscall
ret

cool_waitid:
mov rax, 247
mov r10, rcx # 英特尔把rcx寄存器给硬件级的系统调用的返回值了，这会导致冲突，所以Linux在
			# 内核中的是使用r10寄存器而非rcx,但调用时是传递进rcx,所以我们要把值送给r10
            # 参考https://en.wikipedia.org/wiki/X86_calling_conventions#cite_ref-AMD_28-9
syscall
ret

_exit:
mov rax, 60
syscall
