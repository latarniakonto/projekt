#ifndef FILE_CONTROLLER

#define FILE_CONTROLLER
#include "standing_controller.h"


void Write_To_File(struct month*);
struct month* Write_From_File();
void Add_To_List(struct month*,struct list*);
void Add_To_Months(struct month*,struct month*);

#endif