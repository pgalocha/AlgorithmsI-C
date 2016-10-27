///
///  @file main.c
///  @brief main for AED1 project1
///
///  Created by José Manuel Torres on 28/09/15.
///  Copyright (c) 2015 ___JOSETORRES___. All rights reserved.
///

#include <stdio.h>

#include "pessoa.h"

/**
 *  Persons database global variable
 */
pessoa * personsDB;
int personDBSize; ///< personDB size

int main(int argc, const char * argv[]) {



int choice;
 printf("PROJETO AED1-Menu\n\n");
 printf("1. Abrir Base de Dados;\n");
 printf("2. Exit\n");
 scanf("%d",&choice);

 switch (choice)
 {
     case 1:
         personsDB = NULL;
         personDBSize = 0;
         clientReadFilePerson2();
         break;
   case  2: printf("Goodbye\n");
         break;
   default: printf("Wrong Choice. Enter again\n");
                    break;
 }


//
//    personsDB = NULL;
//    personDBSize = 0;
//    clientReadFilePerson2(); // simple test client for project
    return 0;
}


