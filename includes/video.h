void k_swrite(char* str, int type);
void k_iwrite( int c, int dest);
void k_cls();
void init_con();

void set_font (void* font, int plane);

void scroll (int lines);

int printf(const char* template, ...);

#define VMEM_C(x,y)  (vmem+(((y)*maxcol_p+(x))*2))

#define maxcol_p	80
#define maxrow_p	25
#define maxcol		(maxcol_p - 1)
#define maxrow		(maxrow_p - 1)

