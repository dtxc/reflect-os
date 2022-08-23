[bits 32]
global _start

_start:
  [extern start_kernel]
  call start_kernel
  jmp $
