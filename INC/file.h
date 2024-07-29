#ifndef _FILE_H_
#define _FILE_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<bios.h>
#define LOGMSGPATH "C:\\MEMO\\log.txt"
/**
 * @brief specific for login 
 * 
 * @param path 
 * @param lines 
 * @return int 
 */
int readfilelines(char* path,char lines[][8]);
/**
 * @brief add message in .\\logmsg.txt
 * 
 * @param msg 
 */
void logmessage(char *msg);

//int Registe_usr_file(char usr[],char pass[]);
#endif