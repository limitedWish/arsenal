#include <stdio.h>

//stmfd sp!, {... fp, ip, lr, pc}
#define STMFD_SP_REGS           0xe92dd800

typedef struct {
    int *fp;
    int *ip;
    int *lr;
    int *pc;
} frame_t;

void
backtrace(void)
{
    frame_t *frame = (frame_t*)(&frame + 1);

    while (1) {
/*	if ((*(frame->pc - 3) >> 11) != (STMFD_SP_REGS >> 11)) {
	    printf("End of the stack. Backtrace stop.\n");
            return;
	    }*/
	printf("%p %p %p %p\n", frame->fp, frame->ip, frame->lr, frame->pc);

	frame = (frame_t*)(frame->fp - 3);
    }
}

static int
dummy(void)
{
    printf("hello world\n");
    backtrace();
    return 0;
}

int
main(void)
{
    dummy();

    return 0;
}
