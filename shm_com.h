//
// Created by lvusyy on 6/25/17.
//

#ifndef ITOP4412CODES_SHM_COM_H
#define ITOP4412CODES_SHM_COM_H

#endif //ITOP4412CODES_SHM_COM_H
#define TEXT_SZ 2048

struct shared_use_st {
    int written_by_you;
    char some_text[TEXT_SZ];
};