#include "shell.h"

int logic_ops(char *cmd_array[], int num, char ops_ary[])
{
	
	int var;
	char *temporary = NULL;

	for (var = 0; cmd_array[num] != NULL  && cmd_array[num][var]; var++)
	{
		if (cmd_array[num][var] == '&' && cmd_array[num][var + 1] == '&')
		{
			temporary = cmd_array[num];
			cmd_array[num][var] = '\0';
			cmd_array[num] = string_repetitions(cmd_array[num]);
			cmd_array[num + 1] = string_repetitions(temporary + var + 2);
			num++;
			ops_ary[num] = '&';
			free(temporary);
			var = 0;
		}
		if (cmd_array[num][var] == '|' && cmd_array[num][var + 1] == '|')
		{
			temporary = cmd_array[num];
			cmd_array[num][var] = '\0';
			cmd_array[num] = string_repetitions(cmd_array[num]);
			cmd_array[num + 1] = string_repetitions(temporary + var + 2);
			num++;
			ops_ary[num] = '|';
			free(temporary);
			var = 0;
		}
	}
	return (num);
}