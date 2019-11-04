;%include "io.inc"

section .bss
    x resq 1

section .data
    ln2 dq 0.69314718056
    one dq 1.0
    two dq 2.0
    e dq 2.71828182845904523536
    three dq 3.0
    four dq 4.0
    neight dq -8.0

section .rodata
    lf db "%lf", 0

section .text
EXTERN pow
EXTERN log
EXTERN printf
EXTERN scanf
global f1
global f2
global f3
global f1_diff
global f2_diff
global f3_diff
f1:
    push ebp
    mov ebp, esp
    and esp, -16
    sub esp, 16
    
    mov eax, dword[ebp + 8]
    mov edx, dword[ebp + 12]
    mov dword[x], eax
    mov dword[x + 4], edx
    fld qword[one]
    fld qword[four]
    fld qword[one]
    fld qword[x]
    fld qword[x]
    fmulp
    faddp
    fdivp
    faddp
    mov esp, ebp
    pop ebp
    ret
    

f2:
    push ebp
    mov ebp, esp
    and esp, -16
    sub esp, 16
    
    mov eax, dword[ebp + 8]
    mov dword[esp], eax
    mov edx, dword[ebp + 12]
    mov dword[esp + 4], edx
    mov edx, 0x40080000
    xor eax, eax
    ;mov eax, dword[three]
    ;mov edx, dword[three + 4]
    mov dword[esp + 8], eax
    mov dword[esp + 12], edx
    call pow
    mov esp, ebp
    pop ebp
    ret
    
f3:
    push ebp
    mov ebp, esp
    and esp, -16
    sub esp, 16
    
    mov eax, dword[ebp + 8]
    mov edx, dword[ebp + 12]
    mov dword[x], eax
    mov dword[x + 4], edx
    fld qword[x]
    fchs
    fst qword[x]
    mov eax, dword[x]
    mov edx, dword[x + 4]
    mov dword[esp + 8], eax
    mov dword[esp + 12], edx
    mov eax, dword[two]
    mov edx, dword[two + 4]
    mov dword[esp], eax
    mov dword[esp + 4], edx
    call pow
    mov esp, ebp
    pop ebp
    ret
    
f1_diff:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp + 8]
    mov edx, dword[ebp + 12]
    mov dword[x], eax
    mov dword[x + 4], edx
    fld qword[neight]
    fld qword[x]
    fmulp
    fld qword[x]
    fld qword[x]
    fmulp
    fld qword[one]
    faddp
    fld qword[x]
    fld qword[x]
    fmulp
    fld qword[one]
    faddp
    fmulp
    fdivp
    mov esp, ebp
    pop ebp
    ret

f2_diff:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp + 8]
    mov edx, dword[ebp + 12]
    mov dword[x], eax
    mov dword[x + 4], edx
    fld qword[three]
    fld qword[x]
    fmulp
    fld qword[x]
    fmulp
    mov esp, ebp
    pop ebp
    ret
    
f3_diff:
    push ebp
    mov ebp, esp
    and esp, -16
    sub esp, 16
    
    mov eax, dword[ebp + 8]
    mov edx, dword[ebp + 12]
    mov dword[esp], eax
    mov dword[esp + 4], edx
    call f3
    fld qword[ln2]
    fmulp
    fchs
    mov esp, ebp
    pop ebp
    ret
    
_start_2:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    and esp, -16
    sub esp, 16
    mov dword[esp], lf
    mov dword[esp + 4], x
    call scanf
    
    mov eax, dword[x]
    mov edx, dword[x + 4]
    mov dword[esp], eax
    mov dword[esp + 4], edx
    call f3_diff
    
    fst qword[x]
    mov eax, dword[x]
    mov edx, dword[x + 4]
    mov dword[esp + 4], eax
    mov dword[esp + 8], edx
    mov dword[esp], lf
    call printf
    
    mov esp, ebp
    pop ebp 
    
    xor eax, eax
    ret