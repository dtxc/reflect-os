[GLOBAL read_disk]

read_disk:
    push ebp
    mov ebp, esp
    push edi
    push esi
    push edx
    push ebx

    mov ebx, [esp + 24]
    mov eax, [esp + 28]
    mov ecx, [esp + 32]

    mov esi, eax
    mov edi, ecx

    mov dx, 0x1F2
    mov al, cl
    out dx, al

    mov eax, esi

    mov dx, 0x1F3
    out dx, al

    shr eax, 8
    mov dx, 0x1F4
    out dx, al

    shr eax, 8
    mov dx, 0x1F5
    out dx, al
    
    shr eax, 8
    and al, 0x0F

    mov dx, 0x1F7
    mov al, 0x20
    out dx, al

.hd_not_ready:
    nop
    in al, dx
    and al, 0x88
    cmp al, 0x08
    jnz .hd_not_ready

    mov eax, edi
    mov edx, 256
    mul edx
    mov ecx, eax
    mov dx, 0x1F0

.go_on_read_data:
    in ax, dx
    mov [ebx], ax
    add ebx, 2
    loop .go_on_read_data

    pop ebx
    pop edx
    pop esi
    pop edi
    pop ebp
    ret
