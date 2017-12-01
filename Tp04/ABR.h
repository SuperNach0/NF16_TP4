#ifndef ABR_H_INCLUDED
#define ABR_H_INCLUDED

typedef struct feuille{
	char* mot;
	struct feuille *father;
	struct feuille *lptr;
	struct feuille *rptr;
} feuille;




#endif // ABR_H_INCLUDED
