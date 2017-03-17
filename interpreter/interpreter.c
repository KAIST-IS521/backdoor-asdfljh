// This is where you put your VM code.
// I am trying to follow the coding style of the original.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minivm.h"

#define NUM_REGS   (256)
#define NUM_FUNCS  (256)
#define NUM_INSTR  (256)

#define DEBUG 1

// Global variable that indicates if the process is running.
static bool is_running = true;

uint8_t *ptr_m;

void usageExit() {
    // TODO: show usage
	printf("USAGE: interpreter [bytecode FILE]\n");
    exit(1);
}

void halt(struct VMContext* ctx, const uint32_t instr) {
	is_running = false;
}

void load(struct VMContext* ctx, const uint32_t instr) {
	const uint8_t dst = EXTRACT_B1(instr);
	const uint8_t src = EXTRACT_B2(instr);
	ctx->r[dst].value = ptr_m[src];
}

void store(struct VMContext* ctx, const uint32_t instr) {
	const uint8_t dst = EXTRACT_B1(instr);
	const uint8_t src = EXTRACT_B2(instr);
	ptr_m[dst] = EXTRACT_B0(ctx->r[src].value);
}

void move(struct VMContext* ctx, const uint32_t instr) {
	const uint8_t dst = EXTRACT_B1(instr);
	const uint8_t src = EXTRACT_B2(instr);
	ctx->r[dst].value = ctx->r[src].value;
}

void puti(struct VMContext* ctx, const uint32_t instr) {
	const uint8_t reg = EXTRACT_B1(instr);
	const uint8_t imm = EXTRACT_B2(instr);
	ctx->r[reg].value = imm;
}

void add(struct VMContext* ctx, const uint32_t instr) {
	const uint8_t result = EXTRACT_B1(instr);
	const uint8_t reg1 = EXTRACT_B2(instr);
	const uint8_t reg2 = EXTRACT_B3(instr);
	ctx->r[result].value = ctx->r[reg1].value + ctx->r[reg2].value;
}

void sub(struct VMContext* ctx, const uint32_t instr) {
	const uint8_t result = EXTRACT_B1(instr);
	const uint8_t reg1 = EXTRACT_B2(instr);
	const uint8_t reg2 = EXTRACT_B3(instr);
	ctx->r[result].value = ctx->r[reg1].value - ctx->r[reg2].value;
}

void initFuncs(FunPtr *f, uint32_t cnt) {
    uint32_t i;
    for (i = 0; i < cnt; i++) {
        f[i] = NULL;
    }

    // TODO: initialize function pointers
    // f[0x00] = halt;
    // f[0x10] = load;
	f[0x00] = halt;
	f[0x10] = load;
	f[0x20] = store;
	f[0x30] = move;
	f[0x40] = puti;
	f[0x50] = add;
	f[0x60] = sub;
}

void initRegs(Reg *r, uint32_t cnt)
{
    uint32_t i;
    for (i = 0; i < cnt; i++) {
        r[i].type = 0;
        r[i].value = 0;
    }
}

int main(int argc, char** argv) {
    VMContext vm;
    Reg r[NUM_REGS];
    FunPtr f[NUM_FUNCS];
    FILE* bytecode;
	uint8_t instr_buffer[NUM_INSTR*4];
    uint32_t* pc;
	int i, j;
	
	
    // There should be at least one argument.
    if (argc < 2) usageExit();
	
	//ptr_m = (uint8_t *)malloc(8192);
	
    // Initialize registers.
    initRegs(r, NUM_REGS);
    // Initialize interpretation functions.
    initFuncs(f, NUM_FUNCS);
    // Initialize VM context.
    initVMContext(&vm, NUM_REGS, NUM_FUNCS, r, f);

    // Load bytecode file
    bytecode = fopen(argv[1], "rb");
    if (bytecode == NULL) {
        perror("fopen");
        return 1;
    }
		
	i = 0;
	pc = (uint32_t*)&instr_buffer;
    while (is_running) {
        // TODO: Read 4-byte bytecode, and set the pc accordingly
		fread(&instr_buffer[i*4], 1, 4, bytecode);
		printf("Running instruction %d | ", i);
		for (j = 0; j < 4; ++j)
		{
			printf("%.2x ", instr_buffer[i*4+j]);
		}
		printf("\n");
		
        stepVMContext(&vm, &pc);
#ifdef DEBUG
		for (j = 0; j < 10; ++j)
		{
			printf("r%d: %d\n", j, r[j].value);
		}
#endif
		
		++i;
    }
	
	free(ptr_m);
    fclose(bytecode);

    // Zero indicates normal termination.
    return 0;
}
