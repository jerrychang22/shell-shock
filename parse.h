#ifndef PARSE_H
#define PARSE_H

void run();

void parseParams();

void commandSplit(char **command, char *commands);

void parsePipe(char *commands);

void parseRedir(char *commands);

char **semiBreak(char *str);

char *strip(char *str);



#endif
