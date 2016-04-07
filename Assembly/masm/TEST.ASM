.386
DATA    SEGMENT USE16
BUF     DB      50
        DB      0
        DB      51      DUP(0)
CRLF    DB      0DH,0AH,'$'
DATA    ENDS
STACK   SEGMENT USE16   STACK
