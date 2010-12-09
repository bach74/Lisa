#ifndef	NXU_COLLADA_IMPORT_H

#define	NXU_COLLADA_IMPORT_H


namespace	NXU
{

class	NxuPhysicsCollection;

NxuPhysicsCollection *colladaImport(const	char *fname,void *mem,int len);

};

// addded by bach
#define MY_AF_PRESSURE_SENSOR (1<<10)
// end-bach


#endif
